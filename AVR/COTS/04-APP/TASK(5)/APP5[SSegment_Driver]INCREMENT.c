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

#include "../../02-HAL/02-SSEG/SSEGMENT_Cfg.h"

int main (void)
{
	// DIO Init Function
	DIO_enuInit();
	
	u8 LocalCounter1=0;
	u8 LocalCounter2=0;
	
	while(1)
	{
		
		if (LocalCounter1 < 10)
		{
			HAL_SSEG_Display(DIO_enuPORTA,LocalCounter1);
			HAL_SSEG_Display(DIO_enuPORTB,LocalCounter2);
			
			LocalCounter1++;
		}
		
		if (LocalCounter1 == 10)
		{
			LocalCounter1 = 0;
			LocalCounter2 ++;
		}
		
		if (LocalCounter2 == 10)
		{
			LocalCounter2 =0;
		}
		
		Delay_MS(500);
		
	}
}