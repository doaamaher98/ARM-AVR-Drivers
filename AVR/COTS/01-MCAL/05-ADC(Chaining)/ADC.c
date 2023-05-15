/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 7 MARCH 2023                            */
/* Version   : V.03									   */
/*			   Post-Build Config                       */
/* Target    : AVR32								   */
/* Descrip.   : C File with the Driver Functions	   */
/*				for Checking their Saftey.			   */
/*******************************************************/
/* Note :
  ------
  Made post-build as we can re-configure in runtime
  & Multiple channels can be used.
*/
/********************** Includes ***********************/
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"

#include "ADC.h"

#define				TIMEOUT			100000UL
/********************** Chaining ***********************/
// To allow multiple Conversions to occur without overwriting each other
// Works Asynchronous with chain of conversions
/********************************************************/
static ADC_tenuChainStatus ADC_ChainState = ADC_enuChainReady;

static u8* ADC_ChainChannelsArray = NULL;
static u8 ADC_ChainSize;
static u16* ADC_ChainResultArray = NULL;
/* Global variable to carry EOJ function */
static void (*Notification)(void) = NULL_PTR;

/* Flag to diffrentiate between the cause of ISR */
static u8 ADC_ISRSource;

/* Global variable to carry current conversion index to indicate if it reached the total size or not [finished] */
static u8 ADC_ChainChannelCurrentIndex =0; 

// Global Pointer to function to be used twice in this file
// Global pointer to function to hold the ADC ISR Address
static void (*ptf)(void) = NULL_PTR;
// Global Variable
static u32* ADC_pu32Result = NULL;

// Flag To indicate ADC State
u8 ADC_State = ADC_IDLE;

/********************** Defines ***********************/
// Static Global Flag to detect ENABLE/DISABLE ADC
static u8 Global_ADCEnable_Flag;

ADC_tenuErrorStatus ADC_EnableADC   (void)
{
    ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
    /* Enabling ADC */
    SET_BIT(ADCSRA,ADC_enuADEN);
	// Raise the flag
	Global_ADCEnable_Flag =1;
    return LocalErrorStatus;
}
/*******************************************************/

ADC_tenuErrorStatus ADC_DisableADC   (void)
{
    ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
    /* Disabling ADC */
    CLR_BIT(ADCSRA,ADC_enuADEN);
	// Lower the flag
	Global_ADCEnable_Flag =0;
    return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_StartADCConversion (void)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuNOK;
	
	if (Global_ADCEnable_Flag == 1)
	{
		/* Starting the Conversion */
		SET_BIT(ADCSRA,ADC_enuADSC);
		/* CLR the Interrupt Flag bit */
		CLR_BIT(ADCSRA,ADC_enuADIF);
	}
	
	return LocalErrorStatus;
}

/*******************************************************/
ADC_tenuErrorStatus ADC_SetDataAdjustment (ADC_tenuAdjustment ADC_Adjustment)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	if (ADC_Adjustment == ADC_enuADLAR_LeftAdjust)
	{
		SET_BIT(ADMUX,ADC_enuADLAR);
	}
	else if (ADC_Adjustment == ADC_enuADLAR_RightAdjust)
	{
		CLR_BIT(ADMUX,ADC_enuADLAR);
	} 
	else
	{
		LocalErrorStatus = ADC_enuInvalidAdjustment;
	}
	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_SetChannelNumber (ADC_tenuADCChannels ADC_Channel)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	/**************** Validation ****************/
	if (ADC_Channel >= ADC_enuChannel0 && ADC_Channel < ADC_enuNumberOfChannels)
	{
		/* Getting the ADC Channel Number */
        /**********************************/
        /* First : Clear the last 3 bits in ADMUX Register to be able to read
           these channel bits with Mask = [0b11100000]                      */
        ADMUX &= 0b11111000;

        /* Then Assign the Value taken from the input into these 3 bits */
        ADMUX |= (ADC_Channel & 00000111);
	}
	else
	{
		LocalErrorStatus = ADC_enuInvalidChannel;
	}
	return LocalErrorStatus;
}

/*******************************************************/
ADC_tenuErrorStatus ADC_SetVoltageReference (ADC_tenuVoltageReference ADC_VoltageRef)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	if (ADC_VoltageRef == ADC_enuExternalAREF)
	{
		CLR_BIT(ADMUX,ADC_enuREFS0);
		CLR_BIT(ADMUX,ADC_enuREFS1);
	}
	else if (ADC_VoltageRef == ADC_enuExternalAVCC)
	{
		SET_BIT(ADMUX,ADC_enuREFS0);
		CLR_BIT(ADMUX,ADC_enuREFS1);
	}
	else if (ADC_VoltageRef == ADC_enuInternalAREF)
	{
		SET_BIT(ADMUX,ADC_enuREFS0);
		SET_BIT(ADMUX,ADC_enuREFS1);
	}
	else
	{
		LocalErrorStatus = ADC_enuInvalidReference;
	}
	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_SetPrescaler (ADC_tenuPrescalerValue ADC_Prescaler)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	/**************** Validation ****************/
	if (ADC_Prescaler > ADC_enuNumberOfPrescalerValues)
	{
		LocalErrorStatus = ADC_enuInvalidPrescaler;
	}
	else
	{
		switch (ADC_Prescaler)
		{
			case ADC_enuPrescalerDiv2 :
			CLR_BIT(ADCSRA,ADC_enuADPS0);
			CLR_BIT(ADCSRA,ADC_enuADPS1);
			CLR_BIT(ADCSRA,ADC_enuADPS2);
			break;
			
			case ADC_enuPrescalerDiv4 :
			CLR_BIT(ADCSRA,ADC_enuADPS0);
			SET_BIT(ADCSRA,ADC_enuADPS1);
			CLR_BIT(ADCSRA,ADC_enuADPS2);
			break;
			
			case ADC_enuPrescalerDiv8 :
			SET_BIT(ADCSRA,ADC_enuADPS0);
			SET_BIT(ADCSRA,ADC_enuADPS1);
			CLR_BIT(ADCSRA,ADC_enuADPS2);
			break;
			
			case ADC_enuPrescalerDiv16 :
			CLR_BIT(ADCSRA,ADC_enuADPS0);
			CLR_BIT(ADCSRA,ADC_enuADPS1);
			SET_BIT(ADCSRA,ADC_enuADPS2);
			break;
			
			case ADC_enuPrescalerDiv32 :
			SET_BIT(ADCSRA,ADC_enuADPS0);
			CLR_BIT(ADCSRA,ADC_enuADPS1);
			SET_BIT(ADCSRA,ADC_enuADPS2);
			break;
			
			case ADC_enuPrescalerDiv64 :
			CLR_BIT(ADCSRA,ADC_enuADPS0);
			SET_BIT(ADCSRA,ADC_enuADPS1);
			SET_BIT(ADCSRA,ADC_enuADPS2);
			break;
			
			case ADC_enuPrescalerDiv128 :
			SET_BIT(ADCSRA,ADC_enuADPS0);
			SET_BIT(ADCSRA,ADC_enuADPS1);
			SET_BIT(ADCSRA,ADC_enuADPS2);
			break;
		}
	}
	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_SetTriggerSource (ADC_tenuTriggerSource ADC_TriggerSrc)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	if (ADC_TriggerSrc == ADC_enuSingleConversion)
	{
		CLR_BIT(ADCSRA,ADC_enuADATE);
	}
	else if (ADC_TriggerSrc == ADC_enuAutoTrigger)
	{
		SET_BIT(ADCSRA,ADC_enuADATE);
	}
	else
	{
		LocalErrorStatus = ADC_enuInvalidTriggerSrc;
	}
	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_SetTriggerMode (ADC_tenuAutoTriggerModes ADC_AutoTriggerMode)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	/**************** Validation ****************/
	if (ADC_AutoTriggerMode > ADC_enuAutoTrigNumberOfSources)
	{
		LocalErrorStatus = ADC_enuInvalidAutoTriggerMode;
	}
	else
	{
		switch (ADC_AutoTriggerMode)
		{
			case ADC_enuAutoTrigAnalog_Comparator:
				SET_BIT(SFIOR,ADC_enuADTS0);
				CLR_BIT(SFIOR,ADC_enuADTS1);
				CLR_BIT(SFIOR,ADC_enuADTS2);
				break;
			
			case ADC_enuAutoTrigCounter0_Compare:
				SET_BIT(SFIOR,ADC_enuADTS0);
				SET_BIT(SFIOR,ADC_enuADTS1);
				CLR_BIT(SFIOR,ADC_enuADTS2);
			
			case ADC_enuAutoTrigCounter0_Overflow:
				CLR_BIT(SFIOR,ADC_enuADTS0);
				CLR_BIT(SFIOR,ADC_enuADTS1);
				SET_BIT(SFIOR,ADC_enuADTS2);
				break;
			
			case ADC_enuAutoTrigCounter1_CapEvent:
				SET_BIT(SFIOR,ADC_enuADTS0);
				SET_BIT(SFIOR,ADC_enuADTS1);
				SET_BIT(SFIOR,ADC_enuADTS2);
				break;
			
			case ADC_enuAutoTrigCounter1_Compare:
				SET_BIT(SFIOR,ADC_enuADTS0);
				CLR_BIT(SFIOR,ADC_enuADTS1);
				SET_BIT(SFIOR,ADC_enuADTS2);
				break;
			
			case ADC_enuAutoTrigCounter1_Overflow:
				CLR_BIT(SFIOR,ADC_enuADTS0);
				SET_BIT(SFIOR,ADC_enuADTS1);
				SET_BIT(SFIOR,ADC_enuADTS2);
				break;
			
			case ADC_enuAutoTrigEXT_INT_0:
				CLR_BIT(SFIOR,ADC_enuADTS0);
				SET_BIT(SFIOR,ADC_enuADTS1);
				CLR_BIT(SFIOR,ADC_enuADTS2);
				break;
			
			case ADC_enuAutoTrigFree_Running:
				CLR_BIT(SFIOR,ADC_enuADTS0);
				CLR_BIT(SFIOR,ADC_enuADTS1);
				CLR_BIT(SFIOR,ADC_enuADTS2);
				break;
		}
	}
	return LocalErrorStatus;
}

/*******************************************************/
ADC_tenuErrorStatus ADC_EnableADCInterrupt (void)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	GIE_enuInit_EnableGIE();
	
	SET_BIT(ADCSRA,ADC_enuADIE);
	
	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_DisableADCInterrupt (void)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	GIE_enuInit_DisbaleGIE();
	
	CLR_BIT(ADCSRA,ADC_enuADIE);
	
	return LocalErrorStatus;
}
/*******************************************************/

ADC_tenuErrorStatus ADC_EnablePolling (void)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	
	CLR_BIT(ADCSRA,ADC_enuADIE);
	
	return LocalErrorStatus;
}
/*******************************************************/

/* Synchronous	: Timeout Mechanism */
/* Asynchronous : EOJ Notification	*/


/* Synchronous Function to Read the Analog Value & Convert it to digital one */
ADC_tenuErrorStatus ADC_SynchReadADC_Channel10_Bit (u16 *Add_pu16Value)
{
    ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	ADC_tenuAdjustment ADC_Adjustment = ADC_enuADLAR_LeftAdjust;
    u8 LocalCounter=0;
	
    /* Validation for the Analog Value on Channel */
    if (Add_pu16Value != NULL_PTR)
    {
		/* Start Conversion */
//		ADC_StartADCConversion(); Done in this function
		if (ADC_State == ADC_IDLE)
		{
			ADC_State = ADC_BUSY;
			/* Waiting for the Conversion to be done, waiting for the raising of the flag */
			while ((GET_BIT(ADCSRA,ADC_enuADIF)==0) && (TIMEOUT > LocalCounter))
			{
				LocalCounter++;
			}
			if (LocalCounter == TIMEOUT)
			{
				/* Loop is broken */
				LocalErrorStatus = ADC_enuTIMEOUT;
			}
			else {
				/* Closing the Interrupt Flag bit */
				SET_BIT(ADCSRA,ADC_enuADIF);
				*Add_pu16Value = ADCH;
				
				ADC_State = ADC_IDLE;
			}
			}else
			{
				LocalErrorStatus = ADC_BUSY;
			}
		}else
		{
			LocalErrorStatus = ADC_enuNullPointerException;
		}
		
    return LocalErrorStatus;
}

/*******************************************************/
/* Synchronous Function to Read the Analog Value & Convert it to digital one */
ADC_tenuErrorStatus ADC_SynchReadADC_Channel8_Bit (u8 *Add_pu8Value)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
    ADC_tenuAdjustment ADC_Adjustment = ADC_enuADLAR_RightAdjust;
	u16 LocalCounter=0;

    /* Validation for the Analog Value on Channel */
    if (Add_pu8Value != NULL_PTR)
    {
		if (ADC_State == ADC_IDLE)
		{
			/* Waiting for the Conversion to be done, waiting for the raising of the flag */
			while ((GET_BIT(ADCSRA,ADC_enuADIF)==0) && (TIMEOUT > LocalCounter))
			{
				LocalCounter++;
			}
			
			if (LocalCounter == TIMEOUT)
			{
				/* Loop is broken */
				LocalErrorStatus = ADC_enuTIMEOUT;
			}
			else {
				/* Closing the Interrupt Flag bit */
				SET_BIT(ADCSRA,ADC_enuADIF);
				*Add_pu8Value = ADCL_RESULT;
			}
		}
		else
			{
				LocalErrorStatus = ADC_enuNullPointerException;
			}
	}
		else
			{
				LocalErrorStatus = ADC_BUSY;
			}
			
	return LocalErrorStatus;
}
/*******************************************************/
// Asynchronous Function for reading the ADC Value
ADC_tenuErrorStatus ADC_AsynchReadADC_Channel10_Bit (u16 *Add_pu16Value, void (*Cpy_ptf)(void))
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	ADC_ISRSource = ADC_AsynchSingleChannelISR;
	/************* Validation ****************/
	if (Add_pu16Value == NULL_PTR || Cpy_ptf == NULL_PTR)
	{
		LocalErrorStatus = ADC_enuNullPointerException;
	}
	else
	{
		if (ADC_State == ADC_IDLE)
		{
			ADC_State = ADC_BUSY;
			
			ADC_pu8Result = Add_pu16Value;		// Reading Variable Initialization (Globally)
			ptf = Cpy_ptf;						// Callback Function Initialization
			
			/* Enabling the Interrupt */
			SET_BIT(ADCSRA,ADC_enuADIE);
			
			ADC_State = ADC_IDLE;
			
		}
		else
		{
			LocalErrorStatus = ADC_enuBusy;	
	}
	}
	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_AsynchReadADC_Channel8_Bit (u16 *Add_pu16Value, void (*Cpy_ptf)(void))
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	/************* Validation ****************/
	if (Add_pu16Value == NULL_PTR || Cpy_ptf == NULL_PTR)
	{
		LocalErrorStatus = ADC_enuNullPointerException;
	}
	else
	{
		if (ADC_State == ADC_IDLE)
		{
			ADC_State = ADC_BUSY;
		
			ADC_pu8Result = Add_pu16Value;		// Reading Variable Initialization (Globally)
			ptf = Cpy_ptf;						// Callback Function Initialization
		
			/* Enabling the Interrupt */
			SET_BIT(ADCSRA,ADC_enuADIE);
		}
		else
		{
			LocalErrorStatus = ADC_enuBusy;
		}
	}
	return LocalErrorStatus;
}
/*******************************************************/

/********************** CHAINING *********************************/
/*****************************************************************/
ADC_tenuErrorStatus ADC_StartChainingAsynchConversion(ADC_tstrChain_t *Cpy_Chain)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	/* Make ISR Source to be for chaining */
	ADC_ISRSource = ADC_AysnchChainingISR;
	
	/* Check NULL Pointer */
	if (Cpy_Chain == NULL_PTR)
	{
		LocalErrorStatus = ADC_enuNullPointerException;
	}
	else
	{
		if (ADC_State == ADC_enuChainReady)
		{
			/* Make Chain Busy */
			ADC_ChainState = ADC_enuChainBusy;
		
			/* Initialize Global Chain Channel Array */
			ADC_ChainChannelsArray = Cpy_Chain->Chain_Channel;
		
			/* Initialize Global Chain Result Array */
			ADC_ChainResultArray = Cpy_Chain->Chain_ResultArray;
		
			/* Initialize  Global chain size */
			ADC_ChainSize = Cpy_Chain->Chain_Length;
		
			/* Initialize Global Pointer to Function [EOJ] */
			Notification = Cpy_Chain->EOJ;
		
			/* Reset Index of channels */
			ADC_ChainChannelCurrentIndex = 0;  
		
			// Start Conversion of 1st channel in chain
			ADC_SetChannelNumber(ADC_ChainChannelsArray[ADC_ChainChannelCurrentIndex]);
			ADC_StartADCConversion();
			// ADC Interrupt Enable
			ADC_EnableADCInterrupt();
			}
			else
			{
				LocalErrorStatus = ADC_enuChainBusy;
			}
	}

	return LocalErrorStatus;
}
/*******************************************************/
ADC_tenuErrorStatus ADC_ChainCallBack (void (*Notification)(void))
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
	if (Notification != NULL)
	{
		ADC_ChainChannelCurrentIndex = 0;
		ADC_ChainCallBack = Notification;
	}
	else
	{
		LocalErrorStatus = ADC_enuNullPointerException;
	}
	return LocalErrorStatus;
}
/*******************************************************/
//void __vector_16 (void) __attribute__((signal,used));
//void __vector_16 (void)

/* Single Channel Aysnch & Chaining Async
   Make flag to diffrentiate between the 2 causes
*/
ADC_ISR_Func(ADC_ISR)
{
	if (ADC_ISRSource == ADC_AsynchSingleChannelISR)
	{
		/* Read Result */
		*ADC_pu32Result = ADCH;
		/* Set Status to be idle */
		ADC_State = ADC_IDLE;
		ADC_ChainCallBack();
		ADC_DisableADCInterrupt();
		
	}
	else if (ADC_ISRSource == ADC_AysnchChainingISR)
	{
		/* Read the current conversion */
		ADC_ChainResultArray[ADC_ChainChannelCurrentIndex] = ADCL_RESULT;	// if 10 bits
		/* Increment the index & check if it reached the size */
		ADC_ChainChannelCurrentIndex++;
		if (ADC_ChainChannelCurrentIndex == ADC_ChainSize)
		{
			/* Make state IDLE */
			ADC_State = ADC_IDLE;
			/* Chain is done Call it back */
			Notification();
			/* Disable interrupt */
			ADC_DisableADCInterrupt();
			
		}
		else
		{
			/* Chain is not done */
			// Set new channel to be converted
			ADC_SetChannelNumber(ADC_ChainChannelsArray[ADC_ChainChannelCurrentIndex]);
			/* Start Conversion */
			ADC_StartADCConversion();
		}
	}
	 
		
}
/*******************************************************/
