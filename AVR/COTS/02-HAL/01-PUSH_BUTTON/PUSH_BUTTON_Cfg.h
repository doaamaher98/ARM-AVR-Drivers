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
#include "../../00-LIB/Std_Types.h"

/********************* Enum with the PINS NO. That can be used  *********************/
/********************* for interfacing with the LED				*********************/
typedef enum
{
	PUSH_BUTTON_enuPin0 = 0,
	PUSH_BUTTON_enuPin1,
	PUSH_BUTTON_enuPin2,
	PUSH_BUTTON_enuPin3,
	PUSH_BUTTON_enuPin4,
	PUSH_BUTTON_enuPin5,
	PUSH_BUTTON_enuPin6,
	PUSH_BUTTON_enuPin7,
	PUSH_BUTTON_enuPin8,
	PUSH_BUTTON_enuPin9,
	PUSH_BUTTON_enuPin10,
	PUSH_BUTTON_enuPin11,
	PUSH_BUTTON_enuPin12,
	PUSH_BUTTON_enuPin13,
	PUSH_BUTTON_enuPin14,
	PUSH_BUTTON_enuPin15,
	PUSH_BUTTON_enuPin16,
	PUSH_BUTTON_enuPin17,
	PUSH_BUTTON_enuPin18,
	PUSH_BUTTON_enuPin19,
	PUSH_BUTTON_enuPin20,
	PUSH_BUTTON_enuPin21,
	PUSH_BUTTON_enuPin22,
	PUSH_BUTTON_enuPin23,
	PUSH_BUTTON_enuPin24,
	PUSH_BUTTON_enuPin25,
	PUSH_BUTTON_enuPin26,
	PUSH_BUTTON_enuPin27,
	PUSH_BUTTON_enuPin28,
	PUSH_BUTTON_enuPin29,
	PUSH_BUTTON_enuPin30,
	PUSH_BUTTON_enuPin31,
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