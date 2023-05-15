/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 5 FEB 2023                              */
/* Version   : V.02									   */
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

// Global Pointer to function to be used twice in this file
// Global pointer to function to hold the ADC ISR Address
static void (*ptf)(void) = NULL_PTR;
// Global Variable
static u32* ADC_pu8Result = NULL;

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
		}
		else
		{
			LocalErrorStatus = ADC_enuNullPointerException;
		}
		else
		{
			LocalErrorStatus = ADC_BUSY;
		}
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
			else
			{
				LocalErrorStatus = ADC_enuNullPointerException;
			}
			else
			{
				LocalErrorStatus = ADC_BUSY;
			}
		}
	}
	return LocalErrorStatus;
}


/*******************************************************/
// Asynchronous Function for reading the ADC Value
ADC_tenuErrorStatus ADC_AsynchReadADC_Channel10_Bit (u16 *Add_pu16Value, void (*Cpy_ptf)(void))
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

//void __vector_16 (void) __attribute__((signal,used));
//void __vector_16 (void)

ADC_ISR_Func(ADC_ISR)
{
	if (ptf != NULL_PTR)
	{
		*ADC_pu8Result = ADCH;
		ptf();
		
		// Make ADC State IDLE as it finished
		ADC_State = ADC_IDLE;
		
		// Disable ADC Conversion Complete Interrupt
		CLR_BIT(ADCSRA,ADC_enuADIF);
		
	}
	else
	{
		// do nothing
	}
}
/*******************************************************/
