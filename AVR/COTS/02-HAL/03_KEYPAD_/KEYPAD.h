/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 2 FEB 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : An interface file that includes the functions  */
/*			   definitions along with the other useful enums  */   	 
/**************************************************************/
#ifndef KEYPAD_H
#define KEYPAD_H

#include "Std_Types.h"
#include "KEYPAD_Cfg.h"
#include "KEYPAD_Prv.h"

/********************* Enum with the Error Status *********************/
typedef enum
{
	KEYPAD_enuNOK = 0,
	KEYPAD_enuOK,
	KEYPAD_enuNullPtr,
	KEYPAD_enuInvalidPortNum,
	KEYPAD_enuInvalidValue
}KEYPAD_tenuErrorStatus;

/***************** INIT Function **********************/
void HAL_KEYPAD_INIT (void);

/*************** Getting Pressed key Function ***********/
KEYPAD_tenuErrorStatus HAL_GET_KEYPAD_KEY (u8 * Cpy_Addu8PinValue);

#endif /* KEYPAD */