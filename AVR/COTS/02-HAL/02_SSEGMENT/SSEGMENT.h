/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 18 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : An interface file that includes the functions  */
/*			   definitions along with the other useful enums  */   	 
/**************************************************************/
#ifndef SSEG_H
#define SSEG_H

#include "SSEGMENT_Cfg.h"
/********************* Enum with the Error Status *********************/
typedef enum
{
	SSEG_enuNOK = 0,
	SSEG_enuOK,
	SSEG_enuNullPtr,
	SSEG_enuInvalidPortNum,
	SSEG_enuInvalidValue
}SSEG_tenuErrorStatus;

/********************* for interfacing with the LED				*********************/
typedef enum
{
	SSEG_enuA = 0,
	SSEG_enuB,
	SSEG_enuC,
	SSEG_enuD,
	SSEG_enuE,
	SSEG_enuF,
	SSEG_enuG,
	SSEG_enuCom1,
	SSEG_enuCom2,
	SSEG_enuDot,
	SSEG_enuNumbersofPins
}SSEG_tenuPins;

/****************************************************************/
/*    7-Segment State Function									*/
/*	  Input  : Port number & value that needs to be set			*/
/*	  Output : SSEG_tenuPins to Report Errors				*/
/****************************************************************/
SSEG_tenuErrorStatus HAL_SSEG_Display(DIO_tenuPort Cpy7SEGMENT_u8Port ,u8 Cpy7SEGMENT_u8Value);


#endif /*SSEG */