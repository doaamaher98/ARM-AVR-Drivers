/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : An interface file that includes the functions  */
/*			   definitions along with the other useful enums  */   	 
/**************************************************************/

#ifndef LED_H
#define LED_H

#include "LED_Cfg.h"

/********************* Enum with the Error Status *********************/
typedef enum
{
	LED_enuOk = 0,
	LED_enuNotOk,
	LED_enuNullPtr,
	LED_enuInvalidPortNum,
	LED_enuInvalidPinNum
}LED_tenuErrorStatus;


/****************************************************************/
/*    LED ON Function											*/
/*	  Input  : Pin number that needs to be set					*/
/*	  Output : LED_tenuErrorStatus to Report Errors				*/
/****************************************************************/
LED_tenuErrorStatus HAL_LED_ON(LED_tenuPins Cpy_u8PinNumber);


/****************************************************************/
/*    LED OFF Function											*/
/*	  Input  : Pin number that needs to be cleared				*/
/*	  Output : LED_tenuErrorStatus to Report Errors				*/
/****************************************************************/
LED_tenuErrorStatus HAL_LED_OFF(LED_tenuPins Cpy_u8PinNumber);


#endif /*LED_H*/