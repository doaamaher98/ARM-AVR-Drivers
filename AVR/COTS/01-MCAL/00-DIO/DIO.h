/*******************************************************/
/* Author    : Doaa Maher                              */
/* Date      : 16 JAN 2023                             */
/* Version   : V.01                                    */
/* Target    : AVR32								   */
/* Descrip.  : Interface file that includes :		   */
/*			   1- Functions prototypes [APIs]		   */
/*			   2- Parameters definitions			   */
/*******************************************************/
#ifndef DIO_H
#define DIO_H

#include "Std_Types.h"

#include "DIO_Cfg.h"

/********************* Enum with the Error Status *********************/
typedef enum {
	DIO_enuOK  = 0 		  ,		// To Make sure Compiler will start from zero
	DIO_enuNOK     		  ,
	DIO_enuNULLPtr 	   	  ,
	DIO_enuInvalidPortNum ,
	DIO_enuInvalidPinNum  ,
	DIO_enuInvalidValue
} DIO_tenuErrorStatus;

/****************************************************************/
/*      DIO Init Function										*/
/*		Input  : Void											*/
/*		Output : DIO_tenuErrorStatus to Report Errors		   	*/
/****************************************************************/
DIO_tenuErrorStatus DIO_enuInit (void);

/****************************************************************/
/****************************************************************/
/*    DIO Set PIN Function										*/
/*	  Input  : Pin Number (Range from 0-31)						*/
/*	  Output : DIO_tenuErrorStatus to Report Errors				*/
/******************************************************8*********/
DIO_tenuErrorStatus DIO_enuSetPin (DIO_tenuPins Cpy_enuPinNumber);

/***************************************************************/
/***************************************************************/
/*    DIO Clear Pin Function								   */
/*	  Input  : Pin Number (Range from 0-31)					   */
/*	  Output : DIO_tenuErrorStatus to Report Errors			   */
/***************************************************************/
DIO_tenuErrorStatus DIO_enuClearPin (DIO_tenuPins Cpy_enuPinNumber);

/************************************************************************************************/
/************************************************************************************************/
/*    DIO Get Pin Function																		*/
/*	  Inputs : Pin Number (Range from 0-31), The Address of the Pin Value that needs to be get  */
/*	  Output : DIO_tenuErrorStatus to Report Errors												*/
/************************************************************************************************/
DIO_tenuErrorStatus DIO_enuGetPin (DIO_tenuPins Cpy_enuPinNumber, u8 *Add_u8PinValue);

/************************************************************************************************/
/*    DIO Get Port Function																		*/
/*	  Inputs : Port Number (Range from 0-3), The Address of the Port Value that needs to be get */
/*	  Output : DIO_tenuErrorStatus to Report Errors												*/
/************************************************************************************************/
DIO_tenuErrorStatus DIO_enuSetPort (DIO_tenuPort Cpy_enuPortNumber, u8 Cpy_AssignedPortVal);


/***************************************************************/
/*    DIO Set PIN Value Function							  */
/*	  Input  : Pin Number (Range from 0-31)					  */
/*			   & Value (HIGH or LOW							  */
/*	  Output : DIO_tenuErrorStatus to Report Errors			  */
/***************************************************************/
DIO_tenuErrorStatus DIO_enuSetPinValue (DIO_tenuPins Cpy_enuPinNumber, DIO_tenuPinMode Cpy_enuPinValue);
/***************************************************************/
#endif /* DIO_H */