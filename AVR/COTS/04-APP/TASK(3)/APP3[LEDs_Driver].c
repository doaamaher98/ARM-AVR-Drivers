/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : The main file that includes the blinking of    */
/*			   A LEDs in sequence, with a specific delay 	  */   	 
/**************************************************************/
#include "../../00-LIB/Std_Types.h"
#include "../../00-LIB/Delay.h"

#include "../../01-MCAL/00-DIO/DIO.h"

#include "../../02-HAL/00-LED/LED.h"

#define			LEDS_COUNT					8
int main (void)
{
	// DIO Init Function
	DIO_enuInit();
	
	u8 LocalCounter=0;
		
	while (1)
	{
		for (LocalCounter=0; LocalCounter<LEDS_COUNT; LocalCounter++)
		{
			HAL_LED_ON(LocalCounter);
			Delay_MS(500);
			HAL_LED_OFF(LocalCounter);
		}
		
		for (LocalCounter=LEDS_COUNT-1; LocalCounter>0; LocalCounter--)
		{
			HAL_LED_ON(LocalCounter);
			Delay_MS(500);
			HAL_LED_OFF(LocalCounter);
		}	
	}
}

