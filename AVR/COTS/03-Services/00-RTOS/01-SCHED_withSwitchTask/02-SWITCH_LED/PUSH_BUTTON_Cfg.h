/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 18 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A config file For the PUSH_BUTTON			  */	 
/**************************************************************/
#ifndef PUSH_BUTTON_CFG_H
#define PUSH_BUTTON_CFG_H

#include "PUSH_BUTTON.h"
#include "../00-LIB/Std_Types.h"

/********************* Enum with the PINS NO. That can be used  *********************/
/********************* for interfacing with the LED				*********************/
typedef enum
{
	PUSH_BUTTON_enuPin0 = 0,
	PUSH_BUTTON_enuPin1,
	PUSH_BUTTON_enuNumberOfPins
}PUSH_BUTTON_tenuPins;

/**************** enum with Button Modes *********************/
typedef enum{
	PUSH_BUTTON_enuPullUp= 0,
	PUSH_BUTTON_enuPullDown
}PUSH_BUTTON_tstrPinCfg_Modes;


/********************* Enum with the PORTS NO. *********************/
typedef enum
{
	PUSH_BUTTON_enuPORTA,
	PUSH_BUTTON_enuPORTB,
	PUSH_BUTTON_enuPORTC,
	PUSH_BUTTON_enuPORTD,
	PUSH_BUTTON_enuNumberOfPorts
}PUSH_BUTTON_enuPORT;


/********************* Enum with the LED 2 Statuses *********************/
typedef enum{
	PUSH_BUTTON_enuPressed= 0,
	PUSH_BUTTON_enuReleased
}PUSH_BUTTON_enuStatus;


/**************** Struct with the Button Status *********************/
typedef struct{
	PUSH_BUTTON_tenuPins PUSH_BUTTON_Pin;
	PUSH_BUTTON_tstrPinCfg_Modes PUSH_BUTTON_Mode;
}PUSH_BUTTON_tstrPinCfg_t;



extern PUSH_BUTTON_tstrPinCfg_t PUSH_BUTTON_strPinCfg[PUSH_BUTTON_enuNumberOfPins];

#endif         /* PUSH_BUTTON */
