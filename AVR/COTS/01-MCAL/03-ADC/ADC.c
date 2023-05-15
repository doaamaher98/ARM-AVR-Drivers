/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 16 FEB 2023                              */
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

// Global Pointer to function to be used twice in this file
// Global pointer to function to hold the ADC ISR Address
void (*ptf)(void) = NULL_PTR;

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


/* Synchronous Function to Read the Analog Value & Convert it to digital one */
ADC_tenuErrorStatus ADC_ReadADC_Channel10_Bit (u16 *Add_pu16Value)
{
    ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
   
    u8 LocalCounter=0;
    u16 TIMEOUT=10000;
	
    /* Validation for the Analog Value on Channel */
    if (Add_pu16Value != NULL_PTR)
    {
	    /* Waiting for the Conversion to be done, waiting for the raising of the flag */
// 	    while ((GET_BIT(ADCSRA,ADC_enuADIF)==0) && (TIMEOUT > LocalCounter))
// 	    {
// 		    LocalCounter++;
// 	    }
	    if (TIMEOUT > LocalCounter)
	    {
			*Add_pu16Value = ADCL_RESULT;
	    }
		
		/* Clearing Interrupt Flag bit */
		SET_BIT(ADCSRA,ADC_enuADIF);
    }
    else
    {
	    LocalErrorStatus = ADC_enuNullPointerException;
    }
    return LocalErrorStatus;
}

/*******************************************************/
/* Synchronous Function to Read the Analog Value & Convert it to digital one */
ADC_tenuErrorStatus ADC_ReadADC_Channel8_Bit (u8 *Add_pu8Value)
{
	ADC_tenuErrorStatus LocalErrorStatus = ADC_enuOK;
    
	u16 LocalCounter=0;
	u16 TIMEOUT=10000;

    /* Validation for the Analog Value on Channel */
    if (Add_pu8Value != NULL_PTR)
    {
        /* Waiting for the Conversion to be done, waiting for the raising of the flag */
// 		while ( (GET_BIT(ADCSRA,ADC_enuADSC) == 0) && (TIMEOUT > LocalCounter) )
// 		{
// 			LocalCounter ++;
// 		}
		if (TIMEOUT > LocalCounter)
		{
			*Add_pu8Value = ADCH;	
		}
		
		/* Clearing Interrupt Flag bit */
		SET_BIT(ADCSRA,ADC_enuADIF);
	}
			
	else
	{
		LocalErrorStatus = ADC_enuNullPointerException;
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
		ptf = Cpy_ptf;
	}
	/* Clearing Interrupt Flag bit */
	SET_BIT(ADCSRA,ADC_enuADIF);

	return LocalErrorStatus;
}
/*******************************************************/
ADC_ISR_Func(ADC_ISR)
{
	if (ptf != NULL_PTR)
	{
		ptf();
	}
	else
	{
		// nothing
	}
	
}
/*******************************************************/
