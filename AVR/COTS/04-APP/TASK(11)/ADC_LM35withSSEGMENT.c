#include "../00-LIB/Std_Types.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/ADC.h"

#include "../02-HAL/SSEGMENT.h"
#include "../02-HAL/LM35TempSensor.h"

int main(void)
{
	DIO_enuInit();
	
	ADC_EnableADC();
	ADC_SetVoltageReference(ADC_enuExternalAVCC);
	ADC_SetDataAdjustment(ADC_enuADLAR_RightAdjust);
	ADC_SetPrescaler(ADC_enuPrescalerDiv128);
	
	u16 TempSensorReading=0;
	
	u8 Val1=0;
	u8 Val2=0;
	u8 Voltage_Val;

    /* Replace with your application code */
    while (1) 
    {
		ADC_StartADCConversion();
		LM35_ReadSensorValue(ADC_enuChannel0,&TempSensorReading);
		
		Voltage_Val = (TempSensorReading /10);
		
		Val1= (Voltage_Val /10);
		Val2 = (Voltage_Val %10);
		
		HAL_SSEG_Display(DIO_enuPORTB,Val1);
		HAL_SSEG_Display(DIO_enuPORTC,Val2);
    }
}

