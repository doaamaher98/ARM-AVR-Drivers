/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 16 JAN 2023                              */
/* Version   : V.01                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations file that includes :		*/ 
/*			   1- Configs that can be customized by the */
/*			      User.									*/
/********************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "Std_Types.h"

/********************* Enum with the REG DIRECTION *********************/
typedef enum {
	DIO_enuINPUT  = 0,			// 0
	DIO_enuOUTPUT 				// 1
} DIO_tenuDirection;

/********************* Enum with the Input PIN VALUE *******************/
typedef enum {
	DIO_enuLow  = 0,				// 0
	DIO_enuHigh, 					// 1
} DIO_tenuPinValue;

/**************** Enum with the [Input,Output] PIN MODES ****************/
typedef enum {
	DIO_enuInputPinPullUp	= 0, 		 // 0
	DIO_enuInputPinHighImp	   ,		 // 1
	DIO_enuOutputLow  		   ,	 	 // 2
	DIO_enuOutputHigh 					 // 3
} DIO_tenuPinMode;


/************************ Enum with the Pins *************************/
typedef enum {
	/************ PORTA ***********/
	DIO_enuPin0  = 0, 			// 0
	DIO_enuPin1     ,			// 1
	DIO_enuPin2     ,			// 2
	DIO_enuPin3     ,			// 3
	DIO_enuPin4     ,			// 4
	DIO_enuPin5     ,			// 5
	DIO_enuPin6     ,			// 6
	DIO_enuPin7     ,			// 7
	/************ PORTB ***********/
	DIO_enuPin8     ,			// 8
	DIO_enuPin9     ,			// 9
	DIO_enuPin10    ,			// 10
	DIO_enuPin11    ,			// 11
	DIO_enuPin12    ,			// 12
	DIO_enuPin13    ,			// 13
	DIO_enuPin14    ,			// 14
	DIO_enuPin15    ,			// 15
	/************ PORTC ***********/
	DIO_enuPin16    ,			// 16
	DIO_enuPin17    ,			// 17
	DIO_enuPin18    ,			// 18
	DIO_enuPin19    ,			// 19
	DIO_enuPin20    ,			// 20
	DIO_enuPin21    ,			// 21
	DIO_enuPin22    ,			// 22
	DIO_enuPin23    ,			// 23
	DIO_enuPin24    ,			// 24
	/************ PORTD ***********/
	DIO_enuPin25    ,			// 25
	DIO_enuPin26    ,			// 26
	DIO_enuPin27    ,			// 27
	DIO_enuPin28    ,			// 28
	DIO_enuPin29    ,			// 29
	DIO_enuPin30    ,			// 30
	DIO_enuPin31    ,			// 31
	/************ PIN NO. ***********/
	DIO_enuNumberOfPins			// 32
} DIO_tenuPins;


/********************* Enum with the PORT NUMBER *********************/
typedef enum {
	DIO_enuPORTA  = 0 ,			// 0
	DIO_enuPORTB	  , 		// 1
	DIO_enuPORTC	  ,			// 2
	DIO_enuPORTD	  ,			// 3
	DIO_enuNumberOfPorts		// 4
} DIO_tenuPort;

/********************** PIN Config :[DIR, MODE] ***************************/
typedef struct {
	DIO_tenuDirection       DIO_strPinDirection;
	DIO_tenuPinMode		    DIO_strPinMode ;
} DIO_strPinCfg_t;


// To Make sure it doesn't change in runtime, make the Array constant
// Customized by the User.
extern DIO_strPinCfg_t DIO_strPinCfg [DIO_enuNumberOfPins];


#endif /* DIO_CFG_H */