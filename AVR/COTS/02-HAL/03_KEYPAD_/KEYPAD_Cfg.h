/**************************************************************/
/* Author    : Doaa Maher                               	  */
/* Date      : 2 FEB 2023                              	  */
/* Version   : V.01                                     	  */
/* Target    : AVR32								    	  */
/* Descrip.  : A config file For the KEYPAD				 	  */	 
/**************************************************************/
#ifndef KEYPAD_CFG_H
#define KEYPAD_CFG_H

#include "Std_Types.h"

// #define			Keypad_NumberOfRows			4
// #define			Keypad_NumberOfCols			4

// Choosing the Port
#define			Keypad_Port							DIO_enuPORTA
/***************************** COLS ***********************************/
typedef enum 
{
	Keypad_enuCol0=0,
	Keypad_enuCol1,
	Keypad_enuCol2,
	Keypad_enuCol3,
	Keypad_enuNumberOfCols
	}Keypad_tenuCol;

/***************************** ROWS ***********************************/
typedef enum 
{
	Keypad_enuRow0=0,
	Keypad_enuRow1,
	Keypad_enuRow2,
	Keypad_enuRow3,
	Keypad_enuNumberOfRows
	}Keypad_tenuRow;

/***************************** MODES ***********************************/
typedef enum
{
	Keypad_enuNotPressed=0,
	Keypad_enuPressed
	}Keypad_enuModes;

/***************************** ROWS CONFIG ***********************************/
typedef struct 
{
	DIO_tenuPins strRow_Pin;
	Keypad_enuModes strRow_Mode;
	}Keypad_tstrRowsConfig_t;

/***************************** COLS CONFIG ***********************************/
typedef struct
{
	DIO_tenuPins strCol_Pin;
	Keypad_enuModes strCol_Mode;
}Keypad_tstrColsConfig_t;

// 
// // Choosing Keypad (4x4) Rows' Pins
// #define			ROW1_4x4		Keypad4x4Pin_0		
// #define			ROW2_4x4		Keypad4x4Pin_1		
// #define			ROW3_4x4		Keypad4x4Pin_2		
// #define			ROW4_4x4		Keypad4x4Pin_3
// 
// // Choosing Keypad (4x4) Columns' Pins				
// #define			COL1_4x4		Keypad4x4Pin_4
// #define			COL2_4x4		Keypad4x4Pin_5
// #define			COL3_4x4		Keypad4x4Pin_6
// #define			COL4_4x4		Keypad4x4Pin_7		
// /***********************************************************************/
// 
// // Choosing Keypad (4x3) Rows' Pins
// #define			ROW14x3		Keypad4x3Pin_0
// #define			ROW24x3		Keypad4x3Pin_1
// #define			ROW34x3		Keypad4x3Pin_2
// #define			ROW44x3		Keypad4x3Pin_3
// 
// // Choosing Keypad (4x3) Columns' Pins
// #define			COL1_4x3		Keypad4x3Pin_4
// #define			COL2_4x3		Keypad4x3Pin_5
// #define			COL3_4x3		Keypad4x3Pin_6

/***********************************************************************/
extern const u8 Keypad_Pin_Vals [Keypad_enuNumberOfRows][Keypad_enuNumberOfCols] ;

extern const  Keypad_tstrRowsConfig_t Keypad_tstrRowsConfig[Keypad_enuNumberOfRows];
extern const  Keypad_tstrColsConfig_t Keypad_tstrColsConfig[Keypad_enuNumberOfCols];

#endif         /* KEYPAD */