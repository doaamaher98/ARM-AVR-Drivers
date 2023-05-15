
#ifndef LM35TEMPSENSOR_H_
#define LM35TEMPSENSOR_H_

#include "../01-MCAL/DIO.h"


/*************************** Defines ********************************/
#define		LM35_ADCResolution8Bits			255
#define		LM35_ADCResolution10Bits		1023

#define		LM35_ADCRef5V					5000					
	



/****************** Error Status User Defined Enum *******************/
typedef enum
{
	LM35_enuOK=0,
	LM35_enuNOK,
	LM35_enuInvalidPin,
	LM35_InvalidADCResolution
	}LM35_tenuErrorStatus;

/************************ API *************************/
LM35_tenuErrorStatus LM35_ReadSensorValue (u8 Cpy_u8Channel, u16 *Add_u16SensorVal);


#endif /* LM35TEMPSENSOR_H_ */