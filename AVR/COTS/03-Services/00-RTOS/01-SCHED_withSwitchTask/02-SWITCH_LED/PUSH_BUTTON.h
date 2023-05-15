/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 18 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : An interface file that includes the functions  */
/*			   definitions along with the other useful enums  */   	 
/**************************************************************/

#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include "PUSH_BUTTON_Cfg.h"
#include "../00-LIB/Std_Types.h"
/********************* Enum with the Error Status *********************/
typedef enum
{
	PUSH_BUTTON_enuNOK = 0,
	PUSH_BUTTON_enuOK,
	PUSH_BUTTON_enuNullPtr,
	PUSH_BUTTON_enuInvalidPortNum,
	PUSH_BUTTON_enuInvalidPinNum
}PUSH_BUTTON_tenuErrorStatus;

/****************************************************************/
/*    PUSH_BUTTON State Function								*/
/*	  Input  : Pin number that needs to be set					*/
/*	  Output : PUSH_BUTTON_tenuErrorStatus to Report Errors		*/
/****************************************************************/
PUSH_BUTTON_tenuErrorStatus Get_PUSH_BUTTON_State(PUSH_BUTTON_tenuPins Cpy_u8PinNumber, u8 *Addpu8PUSH_BUTTON_State);



#endif /*PUSH_BUTTON*/
