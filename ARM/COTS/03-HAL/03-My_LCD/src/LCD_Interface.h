/*
 * LCD_Interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Doaa Maher
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "Std_Types.h"

#include "GPIO.h"
/* =================== Pre-processor ======================= */
/****************** Options for configurations *******************/
// RS [Register Select]
#define					LCD_COMMAND					0
#define					LCD_DATA					1

// RW Selection
#define					LCD_WRITE					0
#define					LCD_READ					1

// Enable Pin
#define					LCD_DS						0
#define					LCD_EN						1

// Data Pins Modes
#define					LCD_4_MODE_DATA				0
#define					LCD_8_MODE_DATA				1

// Number of Lines [N]
#define					LCD_1_LINE					0
#define					LCD_2_LINES					1

// Font Size [F]
#define					LCD_5x8_FONT				0
#define					LCD_5x11_FONT				1

// Display Enable [D]
#define					LCD_DISPLAY_DS				0
#define					LCD_DISPLAY_EN				1

// Cursor Enable [C]
#define					LCD_CURSOR_DS				0
#define					LCD_CURSOR_EN				1

// Blink Cursor [B]
#define					LCD_NO_BLINK_CURSOR			0
#define					LCD_BLINK_CURSOR			1

// X & Y Positions limits
#define					LCD_MAX_X_POSITIONS			15
#define					LCD_MAX_Y_POSITIONS			15
#define					LCD_MAX_SCREEN_POSITION		15

// Data Pins
#define					LCD_DATA_PINS				8
/* ==================== User-defined ======================= */
// LCD Status
typedef enum
{
	LCD_enuOK = 0,				// 0
	LCD_enuIDLE,				// 1
	LCD_enuBusyWrite,			// 2
	LCD_enuBusyClear,			// 3
	LCD_enuNotInitialized,		// 4
	LCD_enuInvalidParameters,	// 5
}LCD_tenuStatus;

// State Machine States for LCD for "State"
typedef enum
{
	LCD_enuInitPins = 0 ,
	LCD_enuInitPinsDelay,
	LCD_enuFunctionSet,					// 0
	LCD_enuDisplayOnOffControl	,		// 1
	LCD_enuDisplayClear,				// 2
	LCD_enuEntryModeSet,				// 3

}LCD_tenuStateMachineStates;

// Type for "Request"
typedef enum
{
	LCD_enuNoRequest = 0,				// 0
	LCD_enuWriteRequest,				// 1
	LCD_enuClearRequest,				// 2
}LCD_tenuRequestType;

// LCD Numbers
typedef enum
{
	LCD_enuLCD0=0,
	//	LCD_enuLCD1,
	//	LCD_enuLCD2,
	//	LCD_enuLCD3,
	//	LCD_enuLCD4,
	//	LCD_enuLCD5,
	//	LCD_enuLCD6,
	//	LCD_enuLCD7,
	LCD_enuNumberOfLCDs
}LCD_tenuLCDNumbers;

// LCD Ports
typedef enum
{
	LCD_enuPORTA = 0,
	LCD_enuPORTB,
	LCD_enuPORTC,
	LCD_enuPORTD,
	LCD_enuPORTE,
	LCD_enuPORTH,
	LCD_enuNumberOfPorts,
}LCD_tenuPorts;

// LCD GPIO Pins
typedef enum
{
	LCD_enuLCD_Pin0 = (u16) 0x0001,
	LCD_enuLCD_Pin1 = (u16) 0x0002,
	LCD_enuLCD_Pin2 = (u16) 0x0004,
	LCD_enuLCD_Pin3 = (u16) 0x0008,
	LCD_enuLCD_Pin4 = (u16) 0x0010,
	LCD_enuLCD_Pin5 = (u16) 0x0020,
	LCD_enuLCD_Pin6 = (u16) 0x0040,
	LCD_enuLCD_Pin7 = (u16) 0x0080,
	LCD_enuLCD_Pin8 = (u16) 0x0100,
	LCD_enuLCD_Pin9 = (u16) 0x0200,
	LCD_enuLCD_Pin10 = (u16) 0x0400,
	LCD_enuLCD_Pin11 = (u16) 0x0800,
	LCD_enuLCD_Pin12 = (u16) 0x1000,
	LCD_enuLCD_Pin13 = (u16) 0x2000,
	LCD_enuLCD_Pin14 = (u16) 0x4000,
	LCD_enuLCD_Pin15 = (u16) 0x8000,
	LCD_enuLCDNumberOfPins = 16,
}LCD_tenuPins;

// LCD Control Pins
typedef enum
{
	LCD_enuRS = 0,				// [Selects Command[0] or Data[1]]
	LCD_enuRW,					// [Write[0] or Read[1]]
	LCD_enuE,					// [Enable Pin On[1], Off[0]]
	LCD_enuNumberOfControlPins
}LCD_tenuControlPins;

// LCD Data Pins
typedef enum
{
	LCD_enuDataPin0 = 0,
	LCD_enuDataPin1,
	LCD_enuDataPin2,
	LCD_enuDataPin3,
	LCD_enuDataPin4,
	LCD_enuDataPin5,
	LCD_enuDataPin6,
	LCD_enuDataPin7,
	LCD_enuNumberOfDataPins
}LCD_tenuDataPins;

// LCD Commands
typedef enum
{
	LCD_enuLCD_ClearDisplay 						= 0b00000001,
	LCD_enuLCD_ReturnHome 							= 0b00000010,

	LCD_enuLCD_EntryModeSet_CBLeft_NoShift			= 0b00000100,
	LCD_enuLCD_EntryModeSet_CBLeft_Shift			= 0b00000101,
	LCD_enuLCD_EntryModeSet_CBRight_NoShift 		= 0b00000110,
	LCD_enuLCD_EntryModeSet_CBRight_Shift			= 0b00000111,

	LCD_enuLCD_DisplayOFF_CursorOFF_BlinkOFF 		= 0b00001000,
	LCD_enuLCD_DisplayOFF_CursorOFF_BlinkON			= 0b00001001,
	LCD_enuLCD_DisplayOFF_CursorON_BlinkOFF			= 0b00001010,
	LCD_enuLCD_DisplayOFF_CursorON_BlinkON			= 0b00001011,
	LCD_enuLCD_DisplayON_CursorOFF_BlinkOFF			= 0b00001100,
	LCD_enuLCD_DisplayON_CursorOFF_BlinkON			= 0b00001101,
	LCD_enuLCD_DisplayON_CursorON_BlinkOFF			= 0b00001110,
	LCD_enuLCD_DisplayON_CursorON_BlinkON			= 0b00001111,

	LCD_enuLCD_DisplayShiftCursorLeft 				= 0b00010000,
	LCD_enuLCD_DisplayShiftCursorRight				= 0b00010100,
	LCD_enuLCD_DisplayCursorShiftLeft				= 0b00011000,
	LCD_enuLCD_DisplayCursorShiftRight				= 0b00011100,

	LCD_enuLCD_FunctionSet_8Bit_1Line_5x8			= 0b00110000,
	LCD_enuLCD_FunctionSet_8Bit_2Lines_5x8			= 0b00111000,
	LCD_enuLCD_FunctionSet_8Bit_1Line_5x11			= 0b00110100,
	LCD_enuLCD_FunctionSet_8Bit_2Lines_5x11			= 0b00111100,

	LCD_enuLCD_FunctionSet_4Bit_1Line_5x8			= 0b00100000,
	LCD_enuLCD_FunctionSet_4Bit_2Lines_5x8			= 0b00101000,
	LCD_enuLCD_FunctionSet_4Bit_1Line_5x11			= 0b00100100,
	LCD_enuLCD_FunctionSet_4Bit_2Lines_5x11			= 0b00101100,

	LCD_enuSetCGRAM_Address							= 0b01000000,		// 0x40
	LCD_enuSetDDRAM_Address							= 0b10000000,		// 0x80
}LCD_tenuLCDCommands;

// LCD Name : Will be used as indicies in the array of LCDs
typedef enum
{
	LCD_enuAdvertisement=0,
	//	LCD_enuNamesDisplaying,
	//	LCD_enuFestival,
}LCD_enuLCDName;

// LCD Modes
typedef enum
{
	LCD_enu_4Bits_Mode = 0,
	LCD_enu_8Bits_Mode,
	LCD_enuNumberOfOperatingModes
}LCD_tenuModes;

// Struct for LCD Control & Data Pins = LCD Pin configurations
typedef struct
{
	// Struct(1) : For LCD Mode & Name Selection
	struct
	{
		LCD_tenuModes  LCD_Mode;
	}LCD_tstr_OperatingMode_t;

	struct
	{
		// Struct(2) : For LCD Control & Data Pins [Of GPIO Struct type]
		GPIO_tsrt_PortConfig_t LCD_RS;
		GPIO_tsrt_PortConfig_t LCD_RW;
		GPIO_tsrt_PortConfig_t LCD_E;
		GPIO_tsrt_PortConfig_t LCD_Data[8];
	}LCD_tstrLCD_Pins_t;
}LCD_tstrPinConfiguration_t;

// Array of LCD Configs
extern LCD_tstrPinConfiguration_t LCD_Array [LCD_enuNumberOfLCDs];
/* =================================== APIs ========================================== */
/*
 * Init Function 8-bits
 */
void LCD_enuInit_8Bits (void);

/*
 * Init function with State Machine
 */
LCD_tenuStatus LCD_enuLCDStateMachineInit (void);

/*
 * LCD Task Function
 */
void LCD_voidTask (void);

/*
 * Writing String Asynchronous on LCD Function
 */
LCD_tenuStatus LCD_enuWriteStringAsynch (const char *String, u8 Cpy_u8Length, u8 Cpy_u8PositionX, u8 Cpy_u8PositionY);

/*
 * Clearing the String written on LCD
 */
LCD_tenuStatus LCD_enuClearString (void);

/*
 * Setting Positions (x,y)
 */
LCD_tenuStatus LCD_enuGotoXY (u8 Cpy_u8X , u8 Cpy_u8Y);

/*****************************************************************************************/

// Will be implemented later
LCD_tenuStatus LCD_enuSendString (u8 * Cpy_u8String);
LCD_tenuStatus LCD_enuSendNumber (u8 Cpy_u8Number);
LCD_tenuStatus LCD_enuSendSpecialCharacter (u8 *Cpy_u8AddPattern, u8 Cpy_u8Block, u8 Cpy_u8X , u8 Cpy_u8Y);

#endif /* LCD_INTERFACE_H_ */
/*****************************************************************************************/
