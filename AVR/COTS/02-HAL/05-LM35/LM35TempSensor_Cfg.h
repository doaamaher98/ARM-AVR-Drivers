

#ifndef LM35TEMPSENSOR_CFG_H_
#define LM35TEMPSENSOR_CFG_H_

/* Sensor Pin
   Options :
   --------
   DIO_enuPin0
   DIO_enuPin1
   ....
   DIO_enuPin31 
*/
#define		LM35_Sensor_Pin		DIO_enuPin0

/* Choosing the Resolution :
   ------------------------
	LM35_ADCResolution8Bits
	LM35_ADCResolution10Bits
*/
#define		LM35_Resolution		LM35_ADCResolution10Bits

/*
	Reference Voltage :
	--------------------
	LM35_ADCRefVoltage
*/
#define		LM35_ADCRefVoltage	LM35_ADCRef5V





#endif /* LM35TEMPSENSOR_CFG_H_ */