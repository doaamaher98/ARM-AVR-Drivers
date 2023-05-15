/*
 * STK.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Doaa
 */

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

#include "Std_Types.h"
/* Systick :-
 *  A 24- resolution timer
 * Memory Mapped (C- programmed not assembly)
 * Timer only (not Counter)
 * Counting Down
 * Provides underflow interrupt when reaching 0
 */
/****************************** Defines **********************************/
#define					STK_COUNTER_ENABLE					0x00000001		// Counter Enable that counts value in load register down, sets the counter flag = 1
#define					STK_COUNTER_DISABLED				0x00000000

#define					STK_EXCEPTION_ENABLE				0x00000002 		// Counting down to 0 asserts exception request
#define					STK_EXCEPTION_DISABLED				0xFFFFFFFD		// Counting down to 0 don't asserts exception request

#define					STK_CLK_SRC_AHB						0x00000004
#define					STK_CLK_SRC_AHB_DIV_8				0xFFFFFFFC

#define					STK_COUNTER_FLAG					0x00010000		// Returns 1 if timer counted to 0 (read it to clear it)
#define					STK_COUNTER_BIT						5

#define					STK_NO_REF_FLAG						0x80000000		// read only

#define 				STK_SKEW_FLAG						0x40000000

#define					STK_MODE_SINGLE_INTERVAL			1
#define					STK_MODE_PERIODIC_INTERVAL			2

#define 				STK_MIN_LOAD						1
#define					STK_MAX_LOAD						16777215		// 24-bit timer
#define					STK_CLR_LOAD						0

/* ============================= MS ========================================= */
#define					STK_HSI_AHB_ClockMS						16000
#define					STK_HSI_AHB_8_ClockMS					2000
#define 				STK_HSE_AHB_ClockMS						25000
#define					STK_HSE_AHB_8_ClockMS					3125

/* ============================= US ========================================= */
#define					STK_HSI_AHB_ClockUS						16
#define					STK_HSI_AHB_8_ClockUS					2
#define 				STK_HSE_AHB_ClockUS						25
#define					STK_HSE_AHB_8_ClockUS					3


/*************************** User defined types *****************************/
// Error Status
typedef enum
{
	STK_enuOK=0,
	STK_enuNOK,
	STK_enuNullPointer,

}STK_tenuErrorStatus;

// STK_CTRL Register
typedef enum
{
	STK_enuCounterENABLE=0,
	STK_enuExceptionRequest,
	STK_enuClockSource,
	STK_enuCounterFlag=16
}STK_tenuControlStatusRegister;

// Clock Selection
typedef enum
{
	STK_enuHSI=0,
	STK_enuHSE,
	STK_enuPLL,
	STK_NumberOfClockSources
}STK_tenuClockSources;

// Clock Bus Selection
typedef enum
{
	STK_enuAHB=0,
	STK_enuAHB_8,
}STK_tenuClockBusSource;

// Callback Function type
typedef void (*systick_cbf_t)(void);


/***************************** APIs ************************************/
/* Sequence :
 * 1- Program the Reload value
 * 2- Clear the current value
 * 3- Program control & status register
 */

/*
 * To have single interrupt; write in ISR LOAD_REG = 0 & VAL_REG = 0
 * except for that, each time VAL_REG will decrement from the val in LOAD_RED until 0 & fires an interrupt and make the process again
 */
/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Initializing SysTick Clock Source, disable systick, disable systick interrupt										*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuInit(void);

/********************************************************************************************/
/* Inputs        : 																			*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Busy waiting [Processor is halted] POLLING								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuSynchronousSetTickTimeMS (u32 Cpy_u32Ticks);
/********************************************************************************************/
/* Inputs        : The number of ticks the user wants & a pointer to func.					*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Setting the timer to count & interrupt fires ONCE						*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuAysnchSetIntervalSingle (u32 Cpy_u32Ticks, systick_cbf_t stk_single_interval);
/********************************************************************************************/
/* Inputs        : The number of ticks the user wants & a pointer to func.					*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Setting the timer to count & interrupt fires when it reaches 0 everytime	*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuAsynchSetIntervalPeriodic (u32 Cpy_u32Ticks, systick_cbf_t stk_periodic_interval);
/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuStartTimer (void);

/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuEnableInterrupt (void);

/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuDisableInterrupt (void);

/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Stops timer from counting [called with the asynchronous functions only]	*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuStopTimer (void);

/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Current Elapsed time of the timer	                                    */
/* Functionality : Returns the remaining time left until interrupt fires [Load-Value]		*/
/********************************************************************************************/
u32 STK_u32GetElapsedTime (void);

/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Remaining time of the timer to finish                                    */
/* Functionality : Returns the current value in Value register								*/
/********************************************************************************************/
u32 STK_u32GetRemainingTime(void);


/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuSetCounts (u32 Cpy_u32Counts);

/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuSetPeriodMS (STK_tenuClockSources Cpy_u8ClkSrc, STK_tenuClockBusSource Cpy_u8ClkBus, u16 Cpy_u16PeriodMS);


/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuSetPeriodMS (STK_tenuClockSources Cpy_u8ClkSrc, STK_tenuClockBusSource Cpy_u8ClkBus, u16 Cpy_u16PeriodUS);

/********************************************************************************************/
/* Inputs        : 																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : 								*/
/********************************************************************************************/
STK_tenuErrorStatus STK_enuSetCallback (systick_cbf_t Systick_CallbackFunc);


#endif /* STK_INTERFACE_H_ */
