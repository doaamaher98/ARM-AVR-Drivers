/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 5 FEB 2023                              */
/* Version   : V.01                                    */
/* Target    : AVR32								   */
/* Descrip.   : Header file for Interfaces      	   */
/*******************************************************/
/* Header Guard */
#ifndef ADC_H
#define ADC_H

/************************************ Includes *******************************************/
/* To allow the inclusion of only this file in the Module.c file */
#include "ADC_Config.h"
#include "ADC_Prv.h"
#include "../00-LIB/Std_Types.h"

/***************************************** Types *****************************************/
/************************************* Error Status Options ******************************/
typedef enum 
{
    ADC_enuOK=0,
    ADC_enuNOK,
    ADC_enuTIMEOUT,
    ADC_enuInvalidChannel,
    ADC_enuInvalidInputChannelType,
    ADC_enuInvalidReference,
	ADC_enuInvalidAdjustment,
    ADC_enuInvalidPrescaler,
    ADC_enuInvalidResolution,
    ADC_enuInvalidAutoTriggerMode,
    ADC_enuInvalidTriggerSrc,
    ADC_enuNullPointerException,
    ADC_enuInvalidInterruptStatus,
	ADC_enuBusy
}ADC_tenuErrorStatus;

typedef enum
{
	ADC_enuChainReady=0,
	ADC_enuChainBusy
}ADC_tenuChainStatus;
/************************************ Defines *******************************************/
/* Options :
   ---------
    ADC_SingleEnded_Input
    ADC_PositiveDiff_Input
    ADC_NegativeDiff_Input
*/
// #define ADC_INPUT_ChannelType   ADC_SingleEnded_Input


/* Options :
   ---------
    ADC_ExternalAREF       
    ADC_ExternalAVCC       
    ADC_InternalREF
*/
// #define ADC_REF					ADC_enuExternalAVCC     

/* Options : 
   -----------
   ADC_enuChannel0
   ADC_enuChannel1
   ADC_enuChannel2
   ADC_enuChannel3
   ADC_enuChannel4
   ADC_enuChannel5
   ADC_enuChannel6
   ADC_enuChannel7
*/
// #define ADC_Channel					ADC_enuChannel0


/* Options :
   ----------
   ADC_ADLAR_LeftAdjust
   ADC_ADLAR_RightAdjust
*/

// #define ADC_Adjustment				ADC_enuADLAR_LeftAdjust

/* Options : 
   -----------
    ADC_PrescalerDiv2 
    ADC_PrescalerDiv4  
    ADC_PrescalerDiv8  
    ADC_PrescalerDiv16 
    ADC_PrescalerDiv32 
    ADC_PrescalerDiv64 
    ADC_PrescalerDiv128 
*/
// #define ADC_Prescaler               ADC_enuPrescalerDiv2    

/* Options :
   --------
   ADC_Bits_8
   ADC_Bits_10
*/
// #define ADC_Resolution              ADC_Bits_8

/* Options :
   --------
   ADC_InterruptEnable
   ADC_Polling    
*/
// #define ADC_InterruptOrPolling       ADC_Polling

/* Options :
   --------
   ADC_AutoTriggerEnable
   ADC_AutoTriggerDisable
*/
// #define ADC_AutoTrigger             ADC_enuAutoTrigger

/* Options :
   --------
    ADC_enuAutoTrigFree_Running     
    ADC_enuAutoTrigAnalog_Comparator
    ADC_enuAutoTrigEXT_INT_0        
    ADC_enuAutoTrigCounter0_Compare 
    ADC_enuAutoTrigCounter0_Overflow
    ADC_enuAutoTrigCounter1_Compare 
    ADC_enuAutoTrigCounter1_Overflow
    ADC_enuAutoTrigCounter1_CapEvent
*/

// #if (ADC_AutoTrigger == ADC_enuAutoTrigger)
//     #define ADC_AutoTriggerSrc  ADC_enuAutoTrigFree_Running
// #else
// #endif


/*********************************** APIs used by User **************************************/
/********************************************************************************************/
/* Inputs        : void                                                                     */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Enabling the ADC                                                       */
/********************************************************************************************/ 
ADC_tenuErrorStatus ADC_EnableADC   (void);

/********************************************************************************************/
/* Inputs        : void                                                                     */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Disable the ADC                                                        */
/********************************************************************************************/ 
ADC_tenuErrorStatus ADC_DisableADC   (void);

/********************************************************************************************/
/* Inputs        : void                                                                     */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Starting the conversion                                                */
/********************************************************************************************/
ADC_tenuErrorStatus ADC_StartADCConversion (void);

/********************************************************************************************/
/* Inputs        : Type of Adjustment                                                       */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Adjustment Type : Left or Right                           */
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SetDataAdjustment (ADC_tenuAdjustment ADC_Adjustment);

/********************************************************************************************/
/* Inputs        : Channel Number														    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Wanted Channel											*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SetChannelNumber (ADC_tenuADCChannels ADC_Channel);

/********************************************************************************************/
/* Inputs        : Voltage Reference													    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Wanted Volt Reference										*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SetVoltageReference (ADC_tenuVoltageReference ADC_VoltageRef);

/********************************************************************************************/
/* Inputs        : Prescaler Value													    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Wanted Prescaler Value										*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SetPrescaler (ADC_tenuPrescalerValue ADC_Prescaler);

/********************************************************************************************/
/* Inputs        : Trigger Source													    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Wanted Triggering Source										*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SetTriggerSource (ADC_tenuTriggerSource ADC_TriggerSrc);

/********************************************************************************************/
/* Inputs        : Auto Trigger Mode													    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Wanted Auto Triggering  Mode										*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SetTriggerMode (ADC_tenuAutoTriggerModes ADC_AutoTriggerMode);


/********************************************************************************************/
/* Inputs        : Add_pu8Value                                                             */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choose :                                                               */
/*                        i] Channel to Read                                  [ADMUX]       */
/*                        ii] Starts Conversion                               [ADCSRA]      */
/*                        iii] Waiting the Flag for Conversion to be done     [ADCSRA]      */
/*                        iv] Reading the Digital value                       [ADCH or ADCL]*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SynchReadADC_Channel8_Bit (u8 *Add_pu8Value);

/********************************************************************************************/
/* Inputs        : Add_pu16Value                                                             */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choose :                                                               */
/*                        i] Channel to Read                                  [ADMUX]       */
/*                        ii] Starts Conversion                               [ADCSRA]      */
/*                        iii] Waiting the Flag for Conversion to be done     [ADCSRA]      */
/*                        iv] Reading the Digital value                       [ADCH or ADCL]*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_SynchReadADC_Channel10_Bit (u16 *Add_pu16Value);

/********************************************************************************************/
/* Inputs        : void			                                                            */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Enabling The ADC InterruptL											*/
/********************************************************************************************/
ADC_tenuErrorStatus ADC_EnableADCInterrupt (void);

/*********************************************************************************************/
/* Inputs        : Add_pu16Value                                                             */
/* Return        : Error Status (To ensure function Safety)                                  */
/* Functionality :  Enable Polling															 */
/*********************************************************************************************/
ADC_tenuErrorStatus ADC_EnablePolling (void);

/*********************** Interrupt ********************/
// Pointer to function
void (*ptf)(void);


ADC_tenuErrorStatus ADC_AsynchReadADC_Channel10_Bit (u16 *Add_pu16Value, void (*Cpy_ptf)(void));

ADC_tenuErrorStatus ADC_AsynchReadADC_Channel8_Bit (u16 *Add_pu16Value, void (*Cpy_ptf)(void));

ADC_tenuErrorStatus ADC_StartChainingConversion(ADC_tstrChain_t Cpy_Chain);

typedef struct
{
	u8 Chain_Length;
	u8 *Chain_Channel;
	u8 *Chain_Array;
	void (*EOJ)(void);
}ADC_tstrChain_t;

#endif /* ADC_H */