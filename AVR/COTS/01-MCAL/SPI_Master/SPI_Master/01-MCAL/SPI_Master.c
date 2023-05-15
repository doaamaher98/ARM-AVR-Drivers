/*
 * SPI_Master.c
 *
 * Created: 4/14/2023 7:51:07 AM
 *  Author: engdo
 */ 

/* 
 * Master 
 * Freq = 250KHZ
 * SPI Mode 0
 * MSB First
 */
#include "SPI_Master_Interface.h"

#include <avr/io.h>

void SPI_voidInit(void)
{
	SPCR = (1<<SPE) | (1<<MSTR) ;
	/* In Master Mode User is Required to Set Direction of MOSI,SS and SCK pins */
	DDRB |= (1<< MOSI) | (1<<SS) | (1<<SCK);
}


void SPI_voidSendByte(u8 Data)
{
	/* Assign Data to SPDR To Start Sending Process */
	 SPDR = Data;
	/* Wait Till The Process End < Tx & Rx > */
	while ( (SPSR  & (1<<SPIF) ) == 0) {}
	
}

u8 SPI_u8ReadByte(void)
{
	unsigned char Dummy = 0x00;
	SPDR = Dummy;
	/* Wait Till The Process End < Tx & Rx > */
	while ( (SPSR  & (1<<SPIF) )  == 0) {}
	return SPDR;
}

u8 SPI_u8TransceiveData(u8 Data)
{
		SPDR = Data;
		/* Wait Till The Process End < Tx & Rx > */
		while ( (SPSR  & (1<<SPIF) )  == 0) {}
		return SPDR;
}
