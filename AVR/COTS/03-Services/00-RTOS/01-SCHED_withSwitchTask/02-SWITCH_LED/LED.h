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


/********************* Enum with the Error Status *********************/
typedef enum
{
	LED_enuOk = 0,
	LED_enuNotOk,
	LED_enuNullPtr,
	LED_enuInvalidPortNum,
	LED_enuInvalidPinNum
}LED_tenuErrorStatus;

/********************* Enum with the PORTS NO. *********************/
typedef enum
{
	LED_enuPORTA,
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
	LED_enuPin8,
	LED_enuPin9,
	LED_enuPin10,
	LED_enuPin11,
	LED_enuPin12,
	LED_enuPin13,
	LED_enuPin14,
	LED_enuPin15,
	LED_enuPin16,
	LED_enuPin17,
	LED_enuPin18,
	LED_enuPin19,
	LED_enuPin20,
	LED_enuPin21,
	LED_enuPin22,
	LED_enuPin23,
	LED_enuPin24,
	LED_enuPin25,
	LED_enuPin26,
	LED_enuPin27,
	LED_enuPin28,
	LED_enuPin29,
	LED_enuPin30,
	LED_enuPin31,
	LED_enuNumberOfPins
}LED_tenuPins;

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