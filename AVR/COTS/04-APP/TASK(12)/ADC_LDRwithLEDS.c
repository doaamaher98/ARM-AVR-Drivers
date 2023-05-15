#include "../00-LIB/Std_Types.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/ADC.h"

#include "../02-HAL/LED.h"
#include "../02-HAL/LDR.h"

int main(void)
{
	DIO_enuInit();
	
	ADC_EnableADC();
	ADC_SetVoltageReference(ADC_enuExternalAVCC);
	ADC_SetDataAdjustment(ADC_enuADLAR_RightAdjust);
	// 	ADC_SetChannelNumber(ADC_enuChannel0);
	ADC_SetTriggerSource(ADC_enuAutoTrigger);
	ADC_SetTriggerMode(ADC_enuAutoTrigFree_Running);
	ADC_SetPrescaler(ADC_enuPrescalerDiv128);
	
	u16 LDR_Reading;
	
	u8 Voltage_Val;

    /* Replace with your application code */
    while (1) 
    {
		ADC_StartADCConversion();
		Read_LDRValue(ADC_enuChannel0,&LDR_Reading);
		
		Voltage_Val = LDR_Reading/10;
		
		if (Voltage_Val < 0 || Voltage_Val < 10)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_ON(LED_enuPin10);
			HAL_LED_ON(LED_enuPin11);
			HAL_LED_ON(LED_enuPin12);
			HAL_LED_ON(LED_enuPin13);
			HAL_LED_ON(LED_enuPin14);
			HAL_LED_ON(LED_enuPin15);
		}
		
		if (Voltage_Val > 10 && Voltage_Val < 25)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_ON(LED_enuPin10);
			HAL_LED_ON(LED_enuPin11);
			HAL_LED_ON(LED_enuPin12);
			HAL_LED_ON(LED_enuPin13);
			HAL_LED_ON(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 25 && Voltage_Val < 35)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_ON(LED_enuPin10);
			HAL_LED_ON(LED_enuPin11);
			HAL_LED_ON(LED_enuPin12);
			HAL_LED_ON(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 35 && Voltage_Val < 45)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_ON(LED_enuPin10);
			HAL_LED_ON(LED_enuPin11);
			HAL_LED_ON(LED_enuPin12);
			HAL_LED_OFF(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 45 && Voltage_Val < 55)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_ON(LED_enuPin10);
			HAL_LED_ON(LED_enuPin11);
			HAL_LED_OFF(LED_enuPin12);
			HAL_LED_OFF(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 55 && Voltage_Val < 65)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_ON(LED_enuPin10);
			HAL_LED_OFF(LED_enuPin11);
			HAL_LED_OFF(LED_enuPin12);
			HAL_LED_OFF(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 65 && Voltage_Val < 80)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_ON(LED_enuPin9);
			HAL_LED_OFF(LED_enuPin10);
			HAL_LED_OFF(LED_enuPin11);
			HAL_LED_OFF(LED_enuPin12);
			HAL_LED_OFF(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 80 && Voltage_Val < 90)
		{
			HAL_LED_ON(LED_enuPin8);
			HAL_LED_OFF(LED_enuPin9);
			HAL_LED_OFF(LED_enuPin10);
			HAL_LED_OFF(LED_enuPin11);
			HAL_LED_OFF(LED_enuPin12);
			HAL_LED_OFF(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
		if (Voltage_Val > 90)
		{
			HAL_LED_OFF(LED_enuPin8);
			HAL_LED_OFF(LED_enuPin9);
			HAL_LED_OFF(LED_enuPin10);
			HAL_LED_OFF(LED_enuPin11);
			HAL_LED_OFF(LED_enuPin12);
			HAL_LED_OFF(LED_enuPin13);
			HAL_LED_OFF(LED_enuPin14);
			HAL_LED_OFF(LED_enuPin15);
		}
		
    }
}

