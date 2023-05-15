/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A c file that includes the delay functions	  */
/*			   to halt the system for milli & micro second 	  */   	 
/**************************************************************/
#include "Delay.h"

/****************************************************************/
/*    Delay PIN Function										*/
/*	  Input  : Time passed to halt system with [MILLIS]			*/
/*	  Output : Delay_tenuErrorStatus to Report Errors			*/
/****************************************************************/
Delay_tenuErrorStatus Delay_MS(u32 time)
{
	Delay_tenuErrorStatus Local_ErrorStatus = DELAY_enuOK;      	// Assuming the current status is OK
	//u32 TIME=0;
	
	u32 Counter = 0 ;
	time = (u32)((f32)time* Amplification *((f32)F_CPU/MHz));
	
	/*
	if (TIME != (time/1000))
	{
		Local_ErrorStatus = DELAY_enuNOK;
	}
	else
	{
		*/
		while(Counter < time)
		//while(time)
		{
			asm("NOP"); // processor do nothing
			Counter++;
			//time--;
		}
	//}	
	return Local_ErrorStatus;
}


/****************************************************************/
/*    Delay Set PIN Function									*/
/*	  Input  : Time passed to halt system with 	[MICROS]		*/
/*	  Output : Delay_tenuErrorStatus to Report Errors			*/
/****************************************************************/
Delay_tenuErrorStatus Delay_US(u32 time)
{
	Delay_tenuErrorStatus Local_ErrorStatus = DELAY_enuOK;      	// Assuming the current status is OK
	u32 TIME=0;
	
	u32 Counter = 0 ;
	TIME = (u32)((f32)time* Amplification *((f32)F_CPU/GHz));

	if (TIME != (time/100000))
	{
		Local_ErrorStatus = DELAY_enuNOK;
	}
	
	while(Counter < TIME)
	//while(time)
	{
		asm("NOP"); // processor do nothing
		Counter++;
		//time--;
	}	

	return Local_ErrorStatus;
}
