/*
 * EEPROM_Interface.h
 *
 * Created: 4/15/2023 5:51:14 AM
 *  Author: Doaa
 */ 
#include "Std_Types.h"

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


// Error Status
typedef enum
{
	EEPROM_enuOK=0,
	EEPROM_enuNOK,
}EEPROM_tenuErrorStatus;






/* ================================== APIs ======================== */
void EEPROM_voidInit(void);

EEPROM_tenuErrorStatus EEPROM_enuWriteByte(u8 Data , u8 Address);

u8 EEPROM_u8ReadByte (u8 Address);


#endif /* EEPROM_INTERFACE_H_ */