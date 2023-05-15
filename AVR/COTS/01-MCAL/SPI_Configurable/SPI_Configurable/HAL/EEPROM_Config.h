/*
 * EEPROM_Config.h
 *
 * Created: 4/15/2023 8:38:53 PM
 *  Author: Doaa
 */ 


#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

#define			LOW_STATE				0
#define			HIGH_STATE				1

#define			CS_DIRECTION			DDRB
#define			CS_PORT					PORTB
#define			CS_PIN					PB0

#define			SPI_USED				SPI0

#define			WRITE_EN_OPCODE				(0x06)
#define			WRITE_INSTRUCTION_OPCODE	(0x02)
#define			READ_INSTRUCTION_OPCODE		(0x03)


#endif /* EEPROM_CONFIG_H_ */