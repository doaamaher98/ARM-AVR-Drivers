/*
 * LCD.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Doaa Maher
 */

#include "GPIO.h"

#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

#define				LCD_NOT_INIT					9
#define				LCD_IDLE						10

// Struct for Buffer Request.
typedef struct
{
	const char *LCD_String;
	u8			LCD_Length;
	u8			LCD_Position_X;
	u8			LCD_Position_Y;
	u8			LCD_CurrentPosition;
}LCD_tstrRequestData_t;

// LCD Data Request Object
LCD_tstrRequestData_t LCD_DataRequest;

/********************************** AT FIRST STATE ********************************************/
static u8 State = LCD_enuInitPins;				// First State as initially value
static u8 Init_Done = 0 ;						// A flag raised when the initialization is completed
static u8 Request = LCD_enuNoRequest ;			// No Request initially

/************** Static Functions *****************/
static void LCD_enuWriteCommand   (u8 Cpy_u8Command);
static void LCD_enuWriteData 	  (u8 Cpy_u8Data);
static void LCD_voidWriteSequence (void);		// Write Sequence function in Service Layer
static void LCD_voidClearSequence (void);		// Clear Sequence function in Service Layer

/**************************************************************************************************/
void LCD_enuInit_8Bits (void)
{
	/* Initializing Control Pins */
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RS);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RW);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E);

	/* Initializing Data Pins */
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[0]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[1]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[2]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[3]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[4]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[5]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[6]);
	GPIO_enuInit(&LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[7]);
}
/**************************************************************************************************/
// Initialization With State Machine
LCD_tenuStatus LCD_enuLCDStateMachineInit (void)
{
	static u8 LocalCouter =0;
	/* =========== First State Machine ================ */
	// State  :	 Case
	switch (State)
	{

	case LCD_enuInitPins :
	{
		LCD_enuInit_8Bits();
		State = LCD_enuInitPinsDelay;
	}
	break;

	case LCD_enuInitPinsDelay :
	{
		if (LocalCouter <= 20 )
		{
			LocalCouter ++;
		}
		else
		{
			State = LCD_enuFunctionSet;
		}
	}
	break;

	// First State : Function Set
	case LCD_enuFunctionSet:
	{
		// Take an Action
		LCD_enuWriteCommand(LCD_enuLCD_FunctionSet_8Bit_2Lines_5x8);
		// Next State
		State = LCD_enuDisplayOnOffControl;
		break;
	}

	// Second State : Display On-Off Control
	case LCD_enuDisplayOnOffControl :
	{
		// Take an Action
		LCD_enuWriteCommand(LCD_enuLCD_DisplayON_CursorON_BlinkON);
		// Next Stage
		State = LCD_enuDisplayClear;
		break;
	}

	// Third State : Display Clear
	case LCD_enuDisplayClear :
	{
		// Take an Action
		LCD_enuWriteCommand(LCD_enuLCD_ClearDisplay);
		// Next Stage
		State = LCD_enuEntryModeSet;
		break;
	}

	// Forth State : Entry Mode Set
	case LCD_enuEntryModeSet:
	{
		// Take an Action
		LCD_enuWriteCommand(LCD_enuLCD_EntryModeSet_CBRight_NoShift);
		/****************** FINISHED 1st STATE MACHINE *******************/
		// Raising Init Done Flag
		Init_Done = 1;
		// Making the State Machine State back to IDLE
		State = LCD_enuIDLE;
		break;
	}
	}
	// Returning the State of the State machine
	return State;
}
/**************************************************************************************************/
// Sending String Asynchronous State machine.
LCD_tenuStatus LCD_enuWriteStringAsynch (const char *String, u8 Cpy_u8Length, u8 Cpy_u8PositionX, u8 Cpy_u8PositionY)
{
	/* If no handling and no intialization : Busy write */
	LCD_tenuStatus LocalStatus = LCD_enuBusyWrite;

	/* ============= Checking the State machine current condition =================== */
	// If it's in IDLE: not BUSY & thus can write
	if (State == LCD_enuIDLE)
	{
		// Change it's state to Busy Write
		State = LCD_enuBusyWrite;

		/******************** Handling Buffer Send **********************/
		LCD_DataRequest.LCD_String 			= String;
		LCD_DataRequest.LCD_Length 			= Cpy_u8Length;
		LCD_DataRequest.LCD_Position_X 		= Cpy_u8PositionX;
		LCD_DataRequest.LCD_Position_Y 		= Cpy_u8PositionY;
		LCD_DataRequest.LCD_CurrentPosition = 0;

		LCD_enuGotoXY(Cpy_u8PositionX,Cpy_u8PositionY);

		// After handling the Buffer, Make the Status Ready,OK
		LocalStatus = LCD_enuOK;
		// Make Also the Request To be ready to WRITE
		Request = LCD_enuWriteRequest;
	}

	// If it's not initialized yet, Return a msg to inform the user that intialization is missed
	else if (State == LCD_NOT_INIT)
	{
		LocalStatus = LCD_enuNotInitialized;
	}
	// Returning the Local Status to the user
	return LocalStatus;
}
/**************************************************************************************************/
LCD_tenuStatus LCD_enuClearString (void)
{
	/** Clearing the Written String : **/

	// Setting LocalStatus to be Busy Clear
	LCD_tenuStatus LocalStatus = LCD_enuBusyClear;

	// Setting Request to Clear
	Request = LCD_enuClearRequest;

	// Returning the LocalStatus
	return LocalStatus;
}
/**************************************************************************************************/
LCD_tenuStatus LCD_enuGotoXY (u8 Cpy_u8X , u8 Cpy_u8Y)
{
	// Initializig a local variable for holding the position
	u8 LocalLocation = 0;

	// Setting a local Status to be OK; thus the cursor is ready to go to the position
	LCD_tenuStatus LocalStatus = LCD_enuOK;

	// Checking if the Row position was in First Row :
	if (Cpy_u8X == 0)
	{
		// Setting the location position to Y, as x=0
		LocalLocation = Cpy_u8Y;
	}
	// Checking if the Row position was in Second Row :
	else if (Cpy_u8X == 1)
	{
		// Setting the location position to Y+2nd row address
		LocalLocation = Cpy_u8X + LCD_ROW2_ADDRESS;
	}
	// If the parameters not in Range
	else
	{
		LocalStatus = LCD_enuInvalidParameters;
	}

	/* Set DDRAM Address & Set D7 = 1 */
	// Setting the AC (Address Counter) Points to this location
	LCD_enuWriteCommand(LocalLocation + LCD_enuLCD_Pin7);

	// Returning the local status
	return LocalStatus;
}
/**************************************************************************************************/
static void LCD_enuWriteCommand (u8 Cpy_u8Command)
{
	// Initializing a Local Iterator to iterate through the Data Pins to Send them the Sent command
	u8 LocalIterator =0;
	// Initializing a Temp buffer that will hold the Sent Command
	u8 TempBuffer = 0;

	/* Setting E = 0 */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Pin,GPIO_enuPin_LOW);
	/* Setting RS = 0 [Command] */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Pin,GPIO_enuPin_LOW);
	/* Setting = 0  [Write] */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Pin,GPIO_enuPin_LOW);


	/* Data Pins = Command */
	for (LocalIterator =0; LocalIterator < LCD_DATA_PINS ; LocalIterator++)
	{
		// Getting the Command value & Put it in Buffer
		TempBuffer = (Cpy_u8Command >> LocalIterator) & 1;
		// Setting the Data Pins with the TempBuffer gotten
		GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[LocalIterator].GPIO_Port, LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[LocalIterator].GPIO_Pin, TempBuffer);
	}

	/* Enable at last E = 1 */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Pin, GPIO_enuPin_HIGH);
}
/**************************************************************************************************/
static void LCD_enuWriteData (u8 Cpy_u8Data)
{
	// Initializing a Local Iterator to iterate through the Data Pins to Write on them the Send Data
	u8 LocalIterator =0;
	// Initializing a TempBuffer that will hold the Send Data
	u8 TempBuffer =0 ;

	/* Setting E = 0 */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Pin,GPIO_enuPin_LOW);
	/* Setting RS = 1 [Data] */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RS.GPIO_Pin,GPIO_enuPin_HIGH);
	/* Setting RW = 0  [Write] */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_RW.GPIO_Pin,GPIO_enuPin_LOW);

	/* Data Pins = Data */
	for (LocalIterator =0; LocalIterator < LCD_DATA_PINS ; LocalIterator++)
	{
		// Getting The Data Value into the TempBuffer
		TempBuffer = (Cpy_u8Data >> LocalIterator) &1;
		// Setting the Data pins with the sent Data from TempBuffer
		GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[LocalIterator].GPIO_Port, LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_Data[LocalIterator].GPIO_Pin, TempBuffer);
	}

	/* Enable at last E=1 */
	GPIO_enuSetPinValue_(LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Port,LCD_Array[LCD_enuAdvertisement].LCD_tstrLCD_Pins_t.LCD_E.GPIO_Pin,GPIO_enuPin_HIGH);
}
/**************************************************************************************************/
static void LCD_voidWriteSequence (void)
{
	// Checking If the Current position on LCD is = to the first position in it; Thus it's Ready to be Written on
	if (LCD_DataRequest.LCD_CurrentPosition == LCD_DataRequest.LCD_Length)
	{
		// Setting The State to be IDLE = READY
		State = LCD_enuIDLE;
		// Taking no Requests until writing is done
		Request = LCD_enuNoRequest;
	}
	// Checking if the current position was the last position on the LCD; thus go to the first position to start writing from there
	else if (LCD_DataRequest.LCD_CurrentPosition == LCD_MAX_SCREEN_POSITION)
	{
		// Go to starting position
		LCD_enuGotoXY(1,0);
	}

	// If it was not at the beginning or at last, Write the Data in this location
	else
	{
		// Write the data in the current position
		LCD_enuWriteData( LCD_DataRequest.LCD_String[LCD_DataRequest.LCD_CurrentPosition] );
		// Increment this position by 1 to write the rest
		LCD_DataRequest.LCD_CurrentPosition ++;
	}
}
/**************************************************************************************************/
static void LCD_voidClearSequence (void)
{
	LCD_enuWriteCommand(LCD_enuLCD_ClearDisplay);
}
/**************************************************************************************************/
/* ================================== LCD Task ================================== */
/* 1- LCD_Init
 * 2- LCD_WriteSequence
 * 3- LCD_ClearSequence
 */
void LCD_voidTask (void)
{
	// First thing at the LCD Task, is checking if the LCD was initialized or not; by the flag
	if (Init_Done == 0)			// Not initiallized
	{
		// Not initialized, Initialize it!
		LCD_enuLCDStateMachineInit();
	}
	// If initalized.
	else if (Init_Done == 1)
	{
		// Check the Request Type if it was Write or Read

		/* ================= State Machine for 2 Services (WriteSequence & ClearSequence) ============ */
		switch (Request)
		{
		case LCD_enuWriteRequest:
		{
			// Call it's function for Service
			LCD_voidWriteSequence();
			break;
		}

		case LCD_enuClearRequest:
		{
			// Call it's function for Service
			LCD_voidClearSequence();
			break;
		}
		}
	}
}
/**************************************************************************************************/
