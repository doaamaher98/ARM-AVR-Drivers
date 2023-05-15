/********************************************************/
/* Author    : Doaa Maher                               */
/* Date      : 4 FEB 2023                              */
/* Version   : V.02                                     */
/* Target    : AVR32								    */
/* Descrip.  : Configurations implementation c file		*/ 
/********************************************************/
#include "DIO.h"

#include "KEYPAD_Cfg.h"
#include "SSEGMENT.h"

const  Keypad_tstrRowsConfig_t Keypad_tstrRowsConfig[Keypad_enuNumberOfRows]=
{
	{DIO_enuPin0, Keypad_enuNotPressed},
	{DIO_enuPin1, Keypad_enuNotPressed},	
	{DIO_enuPin2, Keypad_enuNotPressed},	
	{DIO_enuPin3, Keypad_enuNotPressed}	
};

const  Keypad_tstrColsConfig_t Keypad_tstrColsConfig[Keypad_enuNumberOfCols]=
{
	{DIO_enuPin4, Keypad_enuNotPressed},
	{DIO_enuPin5, Keypad_enuNotPressed},
	{DIO_enuPin6, Keypad_enuNotPressed},
	{DIO_enuPin7, Keypad_enuNotPressed}
};

// 4x4 Keypad
const u8 Keypad_Pin_Vals [Keypad_enuNumberOfRows][Keypad_enuNumberOfCols] =
{
	{7,8,9,7},
	{4,5,6,4},
	{1,2,3,1},
	{0,0,0,0}
};