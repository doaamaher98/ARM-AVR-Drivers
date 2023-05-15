#include "../00-LIB/Std_Types.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/ADC.h"

#include "../02-HAL/LED.h"
#include "../02-HAL/LDR.h"


LDR_tenuErrorStatus Read_LDRValue (u8 Cpy_u8Channel, u16 *Add_u16LDRVal)
{
	LDR_tenuErrorStatus LocalErrorStatus = LDR_enuOK;
	
	ADC_SetChannelNumber(Cpy_u8Channel);
	
	ADC_ReadADC_Channel10_Bit(Add_u16LDRVal);

	return LocalErrorStatus;
}