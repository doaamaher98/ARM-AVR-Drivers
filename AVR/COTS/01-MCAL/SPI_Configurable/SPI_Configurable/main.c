/*
 * SPI_Configurable.c
 *
 * Created: 4/15/2023 2:41:10 AM
 * Author : Doaa Maher
 */ 
#include "SPI_Interface.h"
#include "EEPROM_Interface.h"
#include <util/delay.h>

int main(void)
{
	EEPROM_voidInit();
	_delay_ms(10);
	
    /* Replace with your application code */
    while (1) 
    {
		EEPROM_u8ReadByte(0x00);
		_delay_ms(1);
		EEPROM_u8ReadByte(0x01);
		_delay_ms(1);
		EEPROM_u8ReadByte(0x02);
		
    }
}//

