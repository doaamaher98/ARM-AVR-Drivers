/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 18 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : The main file that includes the PUSH_BUTTON of */
/*			   A LEDs in sequence, with a specific delay 	  */   	 
/**************************************************************/
#include "../../00-LIB/Std_Types.h"
#include "../../00-LIB/Delay.h"

#include "../../01-MCAL/00-DIO/DIO.h"
#include "../../01-MCAL/00-DIO/LED.h"

#include "../../02-HAL/01-PUSH_BUTTON/PUSH_BUTTON.h"

int main (void)
{
	// DIO Init Function
	DIO_enuInit();
	
	s8 LocalCounter			= LED_enuPin0;
	
	u8 Up_PushButton_Pin    = PUSH_BUTTON_enuPin8;
	u8 Down_PushButton_Pin  = PUSH_BUTTON_enuPin9;
	
	u8 PushButton_State     = PUSH_BUTTON_enuPin0;
	
	
	while(1)
	{
		Delay_MS(100);
		
		// Increment LEDs using Button
		Get_PUSH_BUTTON_State(Up_PushButton_Pin, &PushButton_State);
		if (PushButton_State == PUSH_BUTTON_enuPressed)
		{
			if (LocalCounter <= LED_enuPin8)
			{
				LocalCounter++;
				HAL_LED_ON(LocalCounter);
				
			}
		}
		
		// Decrement LEDs using Button
		Get_PUSH_BUTTON_State(Down_PushButton_Pin, &PushButton_State);
		if (PushButton_State == PUSH_BUTTON_enuPressed)
		{
			if (LocalCounter >= LED_enuPin0)
			{
				HAL_LED_OFF(LocalCounter);
				LocalCounter--;
				
			}
		}
	}
}