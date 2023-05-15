/*
 * EXT_INT_MAIN.c
 *
 * Created: 1/27/2023 11:00:46 AM
 * Author : engdo
 */ 

#include <avr/interrupt.h>

#include "Delay.h"
#include "DIO.h"
#include "LED.h"
#include "EXT_INT.h"

int main(void)
{	
	DIO_enuInit();
	
	HAL_LED_ON(DIO_enuPin0);
	
	
	GIE_enuInit_EnableGIE();
	EXT_INT_Enable(EXT_INT_0);
	EXT_INT_INIT();
	
	while (1) 
	{}
}

// Macro like function
ISR(INT0_vect)
{
			HAL_LED_ON(DIO_enuPin1);
 			Delay_MS(2000);
}
