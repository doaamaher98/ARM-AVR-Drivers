/*
 * HALT_LED_BLINKING
 * TASK [1]
 * Created: 1/16/2023 11:57:53 PM
 * Author : DOAA MAHER
 * Status : On-Progress
 */ 
#include "../01-MCAL/00-DIO/DIO.h"
#include "../../00-LIB/Delay.h""

//#include <avr/io.h>
//#include <util/delay.h>

int main(void)
{
    /* DIO INITIALIZATION */
	DIO_enuInit();
		
    while (1) 
    {
		DIO_enuSetPin(DIO_enuPin0);
		Delay_MS(1000);
		DIO_enuClearPin(DIO_enuPin0);
		Delay_MS(1000);
    }
}

