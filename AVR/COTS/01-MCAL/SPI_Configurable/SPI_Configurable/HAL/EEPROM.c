/*
 * EEPROM.c
 *
 * Created: 4/15/2023 5:50:52 AM
 *  Author: Doaa
 */ 
#include "SPI_Interface.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Config.h"

#include <avr/io.h>
#include <util/delay.h>

#define			F_CPU			(1000000UL)

#define			DUMMY			(0x00)

// Static Functions
static void SPI_void_CS_Control (u8 State);

/* ======================================================================= */
static void SPI_void_CS_Control (u8 State)
{
	switch(State)
	{
		case LOW_STATE:
		CS_PORT &= ~(1<<CS_PIN);
		break;
		
		case HIGH_STATE:
		CS_PORT |= (1<<CS_PIN);
		break;
		
		default:
		break;
	}
}

void EEPROM_voidInit(void)
{
	
	SPI_USED.EnableControl = SPI_Enable;
	SPI_USED.Mode = SPI_MASTER;
	
	// In Mode 3 or Mode 2 , Clock is IDLE HIGH
	SPI_USED.ClockMode = SPI_CLKMode3;
	
	SPI_USED.DataOrder =  SPI_MSB;
	SPI_USED.Freq =  SPI_FCPU_BY_8;
	
	SPI_USED.InterruptState =  SPI_InterruptDisable;
	
	/* Config PB0 to OUTPUT [CS] & HIGH */
	CS_DIRECTION |= (1 << CS_PIN);
	CS_PORT |= (1 << CS_PIN);
	
	SPI_Init();
}

EEPROM_tenuErrorStatus EEPROM_enuWriteByte(u8 Data , u8 Address)
{
	EEPROM_tenuErrorStatus LocalErrorStatus = EEPROM_enuOK;
	
	/* Making the CS Pin Have LOW Value => Active Low */
	SPI_void_CS_Control(LOW_STATE);
	/* Write Latch Enable Instruction */
	SPI_ReadWrite_Blocking(WRITE_EN_OPCODE);
	/* Apply HIGH to CS Pin to make write latch enable instruction executed */
	SPI_void_CS_Control(HIGH_STATE);
	// Delay
	_delay_ms(50);
	/* Applying LOW to CS Pin */
	SPI_void_CS_Control(LOW_STATE);
	/* Write Latch Enable Instruction */
	SPI_ReadWrite_Blocking(WRITE_INSTRUCTION_OPCODE);
	/* Send your address */
	SPI_ReadWrite_Blocking(Address);
	/* Send your Data */
	SPI_ReadWrite_Blocking(Data);
	/* Apply HIGH to CS Pin to make write latch enable instruction executed */
	SPI_void_CS_Control(HIGH_STATE);
	return LocalErrorStatus;
}

/********************************************************************/
u8 EEPROM_u8ReadByte (u8 Address)
{
	u8 ReadData = 0;
	
	// Low
	SPI_void_CS_Control (LOW_STATE);
	// Read Instruction
	SPI_ReadWrite_Blocking(READ_INSTRUCTION_OPCODE);
	// Address
	SPI_ReadWrite_Blocking(Address);
	// Send Dummy to read_data to enable the clock
	ReadData = SPI_ReadWrite_Blocking(DUMMY);
	SPI_void_CS_Control (HIGH_STATE);
	
	return ReadData;
}