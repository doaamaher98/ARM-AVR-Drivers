/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A config file that includes the modes of led	  */	 
/**************************************************************/
#ifndef LED_CFG_H
#define LED_CFG_H

#include "LED.h"

/********************* Enum with the LED 2 Statuses *********************/
typedef enum{
	LED_enuOFF = 0,
	LED_enuON	
}LED_enuStatus;



#endif