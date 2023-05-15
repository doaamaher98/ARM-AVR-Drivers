/*
 * ADC_Driver.c
 *
 * Created: 2/5/2023 11:13:56 PM
 * Author : Doaa Maher
 * With Callback 
 */ 

#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/GIE.h"
#include "../01-MCAL/ADC.h"

#include "../02-HAL/SSEGMENT.h"

// ISR Function
void ADC_Interrupt_Function (void);

int main(void)
{
	DIO_enuInit();
	
	/* Enable ADC */
	ADC_EnableADC();
	
	/* Enable GIE */
	//GIE_enuInit_EnableGIE();
	 
	/* Set Channel Number */
	ADC_SetChannelNumber(ADC_enuChannel0);
	/* Set Voltage Reference */
	ADC_SetVoltageReference(ADC_enuExternalAVCC);
	/* Set Triggering Source */
	ADC_SetTriggerSource(ADC_enuAutoTrigger);
	/* Set Auto Trigger Mode */
	 ADC_SetTriggerMode(ADC_enuAutoTrigFree_Running);
	/* Set Data Adjustment */
	ADC_SetDataAdjustment(ADC_enuADLAR_RightAdjust);
	/* Set Prescaler */
	ADC_SetPrescaler(ADC_enuPrescalerDiv64);
	/***********************************/
	
	// ADC Channel Reading
	u16 ADCReading;
	
	u16 Voltage_Value=0;
	
	u8 Reminder1=0;
	u8 Reminder2=0;
	
    while (1) 
    {
		/* Starting Conversion */
		ADC_StartADCConversion();
		// Reading the ADC Value on Channel 0
		//ADC_ReadADC_Channel10_Bit(&ADCReading);
		
		
		/**************** Callback *******************/
		ADC_AsynchReadADC_Channel10_Bit(&ADCReading,&ADC_Interrupt_Function);
		
		/***********************************/
		/*
		Voltage_Value = ADCReading/10;
		
		Reminder1 = Voltage_Value %10;
		Reminder2 = Voltage_Value /10;
		
		HAL_SSEG_Display(DIO_enuPORTC,Reminder1);
		HAL_SSEG_Display(DIO_enuPORTB,Reminder2);
		*/
		
// 		Delay_MS(100);
    }
}

// ISR Function
void ADC_Interrupt_Function (void)
{
	// ADC Channel Reading
	u16 ADCReading;
	
	u16 Voltage_Value=0;
	
	u8 Reminder1=0;
	u8 Reminder2=0;
	
	Voltage_Value = ADCReading/10;
	
	Reminder1 = Voltage_Value %10;
	Reminder2 = Voltage_Value /10;
	
	HAL_SSEG_Display(DIO_enuPORTC,Reminder1);
	HAL_SSEG_Display(DIO_enuPORTB,Reminder2);
	
}

