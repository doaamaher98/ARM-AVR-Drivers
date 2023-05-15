/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 16 FEB 2023                              	  */
/* Version   : V.02                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A file that includes the APIS of the			  */
/*			   LCD Driver									  */
/**************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/DIO_Priv.h"

#include "LCD_Config.h"
#include "LCD_Prv.h"

/* Enum for error status */
typedef enum
{
	LCD_enuOK=0,
	LCD_enuNOK,
	LCD_enuInvalidBlockNumber,
	LCD_enuNullPtr,
	LCD_enuInvalidInitialization,
	LCD_enuInvalidCommand,
	LCD_enuInvalidData
	}LCD_tenuErrorStatus;


/* Pre-built Config
	Choosing LCD Port :
	-------------------
	DIO_enuPORTA
	DIO_enuPORTB
	DIO_enuPORTC
	DIO_enuPORTD
*/
#define			LCD_DataPins_PORT		PORTA

#define			LCD_ControlPins_PORT	PORTB

/* Configuring the Control : RS,EN & RW Pins */
#define			LCD_RS			0
#define			LCD_RW			1
#define			LCD_EN			2


/* Options :-
   --------- 
	LCD Data bits Mode
	LCD_4Bits_Data
	LCD_8Bits_Data
*/
#define			LCD_DataPinsMode			LCD_4Bits_Data


/* Options :-
   ---------
	LCD_1_Line
	LCD_2_Line
*/
#define			LCD_Lines					LCD_2_Line

/* Options :-
   ---------
	LCD_Font_5x8
	LCD_Font_5x11
*/
#define			LCD_Font_Size				LCD_Font_5x8







/******************************************* APIs ******************************************/
/********************************************************************************************/
/* Inputs        : void                                                       */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Initializing the LCD                           */
/********************************************************************************************/
LCD_tenuErrorStatus LCD_vidInit (void);

/********************************************************************************************/
/* Inputs        : The wanted Command                                                       */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Writing the Data on the digital pins								*/
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuSendData    (u8 Copy_u8Data);

/********************************************************************************************/
/* Inputs        : The wanted Command                                                       */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Writing the command on the digital pins								*/
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command);

/********************************************************************************************/
/* Inputs        : X : Rows(0,1) & Y Cols(0->15)                                            */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Going to the place to write in											*/
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuGotoXY      (u8 Copy_u8XPos, u8 Copy_u8YPos);

/********************************************************************************************/
/* Inputs        : Copy_pu8Pattern : Pointer to the array of the pattern (AC)				*/
/*				   Copy_u8BlockNum : Block number (0->7)									*/
/*				   Copy_u8XPos	   : Row line												*/	
/*                 Copy_u8YPos     : Col. position											*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Choosing the Special Character pattern in [CGRAM] to be displayed on   */
/*					 the Display [DDRAM]																*/
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuWriteSpecialPattern  (u8* Copy_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);

/********************************************************************************************/
/* Inputs        : String to Write														    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :  Displaying a String on LCD												*/
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuWriteString (char* Copy_pchString);

/********************************************************************************************/
/* Inputs        : Number to Write															*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Displaying a Number on LCD												*/
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number);

/********************************************************************************************/
/* Inputs        : Void																	    */
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality :   Clearing the Display												    */
/********************************************************************************************/
LCD_tenuErrorStatus LCD_enuClearDisplay (void);


#endif /* LCD_H_ */