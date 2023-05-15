/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the delay functions		  */
/*			   definitions & configurations to halt the system*/
/*			   for milli & micro second 	  				  */   	 
/**************************************************************/
#ifndef 	DELAY_H
#define 	DELAY_H


#include "Std_Types.h"

/****************** Important definitions ***********************/
#define		   F_CPU					8000000UL

#define			MHz						1000000.0
#define			GHz						1000000000.0


#define Amplification			91.7

/****************** Delay Error Status Enum ***********************/
typedef enum {
	DELAY_enuOK  = 0 		  ,		// To Make sure Compiler will start from zero
	DELAY_enuNOK     
}Delay_tenuErrorStatus;


/****************************************************************/
/*    Delay for milli seconds function							*/
/*	  Input  : Time passed to halt system with [MILLIS]			*/
/*	  Output : Delay_tenuErrorStatus to Report Errors			*/
/****************************************************************/
Delay_tenuErrorStatus Delay_MS(u32 time);


/****************************************************************/
/*    Delay for micro seconds function										*/
/*	  Input  : Time passed to halt system with 	[MICROS]		*/
/*	  Output : Delay_tenuErrorStatus to Report Errors				*/
/****************************************************************/
Delay_tenuErrorStatus Delay_US(u32 time);

#endif				/* DELAY_H */