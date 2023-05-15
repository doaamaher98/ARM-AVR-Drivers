/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 24 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : The main file that includes the SSEG  		  */
/**************************************************************/
#include "../../00-LIB/Std_Types.h"
#include "../../00-LIB/Delay.h"

#include "../../01-MCAL/00-DIO/DIO.h"
#include "../../02-HAL/01-PUSH_BUTTON/PUSH_BUTTON.h"
#include "../../02-HAL/02-SSEG/SSEGMENT_Cfg.h"

int main (void)
{
	// DIO Init Function
	DIO_enuInit();
	
	u8 LocalCounter1=0;
	u8 LocalCounter2=0;
	
	u8 Push_Button1 = DIO_enuPin16;
	u8 Push_Button2 = DIO_enuPin17;
	
	u8 State;
	
	while(1)
	{
		Get_PUSH_BUTTON_State(Push_Button1, &State);
		if (State ==  PUSH_BUTTON_enuPressed)
		{
			Delay_MS(50);
			Get_PUSH_BUTTON_State(Push_Button1, &State);
			if (State ==  PUSH_BUTTON_enuPressed)
			{
				LocalCounter1++;	
				if (LocalCounter1 == 10)
				{
					LocalCounter1=0;
					LocalCounter2++;
				}
			}	
		}
		
		Get_PUSH_BUTTON_State(Push_Button2, &State);
		if (State ==  PUSH_BUTTON_enuPressed)
		{
			Delay_MS(50);
			Get_PUSH_BUTTON_State(Push_Button2, &State);
			if (State ==  PUSH_BUTTON_enuPressed)
			{
				LocalCounter1--;
				
				if (LocalCounter1 == 0)
				{
					LocalCounter1=9;
					LocalCounter2--;
				}
			}
		}
		
		HAL_SSEG_Display(DIO_enuPORTA,LocalCounter1);	
		HAL_SSEG_Display(DIO_enuPORTB,LocalCounter2);	
	}
}