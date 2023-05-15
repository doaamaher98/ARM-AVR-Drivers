/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 5 FEB 2023                              */
/* Version   : V.01                                    */
/* Target    : AVR32								   */
/* Descrip.   : Configurations file for the user	   */
/*******************************************************/
/* Header Guard */
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/************************************ Includes *******************************************/
                                    /* None */

/************************************ Defines *******************************************/
// Enable & Disable ADC [Bit #7]
#define             ADC_DisableADC_Perph           0
#define             ADC_EnableADC_Perph            1

// Starting Conversion (Bit #6)
/* After ADSC has been written & ADC is enabled*/
/* Or at the same time as the ADC is enabled */
#define             ADC_StartConversion         0b01000000
#define             ADC_EndConversion           0b00000000

// ADC Interrupt Flag [ADIF] (Bit #4)
#define             ADC_InterruptFlag           1

// ADC Interrupt Enable (Bit #3) with GIE Enable (I-bit in SREG is set too)
#define             ADC_InterruptEnable          1
#define             ADC_Polling                  0


// Input Channels Types
#define         ADC_SingleEnded_Input   0       // 1 Channel
#define         ADC_PositiveDiff_Input  1       // > 1 Channel +Diffrential
#define         ADC_NegativeDiff_Input  2       // > 1 Channel -Diffrential

// Gains Modes [Selections]
#define         ADC1xGain               0
#define         ADC_10xGain             1
#define         ADC_200xGain            2


/***************** Interrupt *****************/
#define		ADC_ISR			16


#define		ADC_ISR_Func(ISR_NUMBER) void __vector_##ISR_NUMBER(void) __attribute__((signal));\
												void __vector_##ISR_NUMBER(void)

/************************************ Types *******************************************/
// ADC Channels
typedef enum
{
	ADC_enuChannel0=0,
	ADC_enuChannel1,
	ADC_enuChannel2,
	ADC_enuChannel3,
	ADC_enuChannel4,
	ADC_enuChannel5,
	ADC_enuChannel6,
	ADC_enuChannel7,
	ADC_enuNumberOfChannels
}ADC_tenuADCChannels;


// Voltage Reference
typedef enum
{
	ADC_enuExternalAREF=0,
	ADC_enuExternalAVCC,
	ADC_enuInternalAREF,
	ADC_enuNumberOfVoltageRef
	}ADC_tenuVoltageReference;

// Auto Trigger Sources Selections
typedef enum
{
	ADC_enuAutoTrigFree_Running   =0,
	ADC_enuAutoTrigAnalog_Comparator,
	ADC_enuAutoTrigEXT_INT_0        ,
	ADC_enuAutoTrigCounter0_Compare ,
	ADC_enuAutoTrigCounter0_Overflow,
	ADC_enuAutoTrigCounter1_Compare ,
	ADC_enuAutoTrigCounter1_Overflow,
	ADC_enuAutoTrigCounter1_CapEvent,
	ADC_enuAutoTrigNumberOfSources
}ADC_tenuAutoTriggerModes;

// ADC Triggering Source
// The trigger source is selected by setting the ADC Trigger Select bits, ADTS in SFIOR
typedef enum 
{
	ADC_enuSingleConversion=0,
	ADC_enuAutoTrigger,
	ADC_enuNumberOfTriggerSources
	}ADC_tenuTriggerSource; 

// ADC Prescaler Selections (Bits 2:0)
typedef enum
{
	#if (ADC_enuADPS0 == 0)
		ADC_enuPrescalerDiv2=0,
	#elif (ADC_enuADPS0 == 1)
		ADC_enuPrescalerDiv2=1,
	#else
	#endif
	ADC_enuPrescalerDiv4=2,
	ADC_enuPrescalerDiv8,
	ADC_enuPrescalerDiv16,
	ADC_enuPrescalerDiv32,
	ADC_enuPrescalerDiv64,
	ADC_enuPrescalerDiv128,
	ADC_enuNumberOfPrescalerValues
	}ADC_tenuPrescalerValue;


// ADLAR Left Adjust Result (Bit #5), Otherwise, it's right adjusted
typedef enum 
{
	ADC_enuADLAR_RightAdjust=0,
	ADC_enuADLAR_LeftAdjust,
	ADC_enuNumberOfAdjustments
	}ADC_tenuAdjustment;


#endif /* ADC_CONFIG_H */