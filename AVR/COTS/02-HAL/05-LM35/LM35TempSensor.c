/*
 * LM35TempSensor.c
 *
 * Created: 2/11/2023 1:12:33 AM
 *  Author: Doaa Maher
 */ 

#include "LM35TempSensor.h"
#include "LM35TempSensor_Cfg.h"

#include "../01-MCAL/ADC.h"

LM35_tenuErrorStatus LM35_ReadSensorValue (u8 Cpy_u8Channel, u16 *Add_u16SensorVal)
{
	LM35_tenuErrorStatus LocalErrorStatus = LM35_enuOK;
	u32 ADC_u32Reading=0;
		
	u8 LocalChannelNumber = ADC_SetChannelNumber (Cpy_u8Channel);
	
	if (LocalChannelNumber >= DIO_enuPin0 && LocalChannelNumber <= DIO_enuPin31)
	{
		/* Reading the Analog Value from the Temp Sensor */
		/* If resolution was 10-bits  */
		#if (LM35_Resolution == LM35_ADCResolution10Bits)
		{
			ADC_ReadADC_Channel10_Bit(&ADC_u32Reading);
			/* Converting the mV to Volts */
			/* 10mV = 1 Celisus */
			*Add_u16SensorVal = (u16)((ADC_u32Reading * LM35_ADCRef5V) /LM35_ADCResolution10Bits) /10;
			
		}
		/* If resolution was 8-bits  */
		
		#elif (LM35_Resolution == LM35_ADCResolution8Bits)
		{
			ADC_ReadADC_Channel8_Bit(&ADC_u32Reading);
			/* Converting the mV to Volts */
			/* 10mV = 1 Celisus */
			*Add_u16SensorVal = (u16)((ADC_u32Reading * LM35_ADCRef5V) /LM35_ADCResolution8Bits) /10;
		}
		#else 
			LocalErrorStatus = LM35_InvalidADCResolution;
		
		#endif
	}
	
	else
	{
		LocalErrorStatus = LM35_enuInvalidPin;
	}

	return LocalErrorStatus;
}