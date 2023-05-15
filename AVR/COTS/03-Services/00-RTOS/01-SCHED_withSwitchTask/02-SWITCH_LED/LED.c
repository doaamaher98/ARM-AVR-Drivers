/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 17 JAN 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A c file that includes the LED functions		  */
/*			   to be turned ON & OFF 					 	  */   	 
/**************************************************************/
#include "../00-LIB/Std_Types.h"

#include "../01-MCAL/DIO.h"
#include "LED.h"

#define 			REG_BITS					8				// For not using Magic Numbers

/****************************************************************/
/*    LED ON Function											*/
/*	  Input  : Pin number that needs to be set					*/
/*	  Output : LED_tenuErrorStatus to Report Errors				*/
/****************************************************************/

LED_tenuErrorStatus HAL_LED_ON(LED_tenuPins Cpy_u8PinNumber)
{
	LED_tenuErrorStatus Local_ErrorStatus = LED_enuOk;      	// Assuming the current status is OK
	
	u8 Loc_u8PortNumber = Cpy_u8PinNumber /REG_BITS;
	u8 Loc_u8PinNumber  = Cpy_u8PinNumber %REG_BITS;
	
	/**************************** VALIDATION ***************************/
	if(Loc_u8PortNumber > LED_enuNumberOfPorts)
	{
		Local_ErrorStatus = LED_enuInvalidPortNum;
	}
	else if (Loc_u8PinNumber > LED_enuNumberOfPins)
	{
		Local_ErrorStatus = LED_enuInvalidPinNum;
	}
	
	else if (Local_ErrorStatus == LED_enuOk)
	{
		DIO_enuSetPin(Cpy_u8PinNumber);
	}
	else
	{
		Local_ErrorStatus = LED_enuOk;
	}
	return Local_ErrorStatus;
}

/****************************************************************/
/*    LED OFF Function											*/
/*	  Input  : Pin number that needs to be cleared				*/
/*	  Output : LED_tenuErrorStatus to Report Errors				*/
/****************************************************************/
LED_tenuErrorStatus HAL_LED_OFF(LED_tenuPins Cpy_u8PinNumber)
{
	LED_tenuErrorStatus Local_ErrorStatus = LED_enuOk;      	// Assuming the current status is OK
	
	u8 Loc_u8PortNumber = Cpy_u8PinNumber /REG_BITS;
	u8 Loc_u8PinNumber  = Cpy_u8PinNumber %REG_BITS;
	
	/**************************** VALIDATION ***************************/
	if(Loc_u8PortNumber > LED_enuNumberOfPorts)
	{
		Local_ErrorStatus = LED_enuInvalidPortNum;
	}
	else if (Loc_u8PinNumber > LED_enuNumberOfPins)
	{
		Local_ErrorStatus = LED_enuInvalidPinNum;
	}
	
	else if (Local_ErrorStatus == LED_enuOk)
	{
		DIO_enuClearPin(Cpy_u8PinNumber);
	}
	else
	{
		Local_ErrorStatus = LED_enuOk;
	}
	return Local_ErrorStatus;
}
