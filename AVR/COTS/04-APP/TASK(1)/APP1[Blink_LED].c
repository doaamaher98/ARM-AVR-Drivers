/*
 * BLINK_LED
 * LAB [1]
 * Created: 1/16/2023 11:57:53 PM
 * Author : DOAA MAHER
 */ 
#include "../01-MCAL/00-DIO/DIO.h"
#include <avr/io.h>

#define F_CPU			1000000UL
#include <util/delay.h>

int main(void)
{
    /* DIO INITIALIZATION */
	DIO_enuInit();
		
    while (1) 
    {
		DIO_enuSetPin(DIO_enuPin0);
		_delay_ms(1000);
		DIO_enuClearPin(DIO_enuPin0);
		_delay_ms(1000);
    }
}

