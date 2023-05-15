/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A config file that includes the modes of led	  */	 
/**************************************************************/
#ifndef LED_CFG_H
#define LED_CFG_H

/********************* Enum with the LED 2 Statuses *********************/
typedef enum{
	LED_enuOFF = 0,
	LED_enuON	
}LED_enuStatus;

/********************* Enum with the LED 2 Modes *********************/
typedef enum{
	LED_ActiveHigh = 0,
	LED_ActiveLow
}LED_enuMode;

/********************* Enum with the PORTS NO. *********************/
typedef enum
{
	LED_enuPORTA =0,
	LED_enuPORTB,
	LED_enuPORTC,
	LED_enuPORTD,
	LED_enuNumberOfPorts
}LED_enuPORT;

/********************* Enum with the PINS NO. That can be used  *********************/
/********************* for interfacing with the LED				*********************/
typedef enum
{
	LED_enuPin0 = 0,
	LED_enuPin1,
	LED_enuPin2,
	LED_enuPin3,
	LED_enuPin4,
	LED_enuPin5,
	LED_enuPin6,
	LED_enuPin7,
	LED_enuNumberOfPins
}LED_tenuPins;


/********************* Struct with the LED Configurations  *********************/
typedef struct {
	DIO_tenuPins LED_Pin;
	LED_enuMode LED_Mode;
	}LED_strCfg_t;


/********************* Array having the LED Configurations *********************/
extern LED_strCfg_t LED_strCfg [LED_enuNumberOfPins];

 
#endif