/*
 * TIMER0.h
 *
 * Created: 3/3/2023 4:12:08 AM
 *  Author: Doaa
 */ 
#ifndef TIMER0_H_
#define TIMER0_H_

#include "../01-MCAL/TIMER0_PRIV.h"

/*************************** Defines ************************/
#define			TIMER0_OFF								0
#define			TIMER0_ON								1

#define			TIMER0_TimerMode						0
#define			TIMER0_CounterMode						1

#define			TIMER0_NoPrescaler						0

#define			TIMER0_InterruptOFF						0
#define			TIMER0_InterruptON						1

#define			TIMER0_CompareMatchOFF					0
#define			TIMER0_CompareMatchON					1

#define			TIMER0_Overflow_Interrupt_EN			0
#define			TIMER0_CompareMatch_Interrupt_EN		1
/*
	Note : Don't forget to set the I-bit in SREG register to enable GIE
*/

#define			TIMER_0_Overflow_Interrupt_Flag			0
#define			TIMER_0_CompareMatch_Interrupt_Flag		1

#define			TIMER_0_PrescalerReset					0

/****************************** Types ******************************/
/* Error Status */
typedef enum
{
	Timer0_enuOk=0,
	Timer0_enuNOK,
	Timer0_enuInvalidMode,
	Timer0_enuInvalidSysClk,
	Timer0_enuInvalidPrescaler,
	TIMER0_enuInvalidInterrupt,
	TIMER0_enuInvalidCounterMode,
	TIMER0_enuInvalidTimer,
	Timer0_enuOFF,
	TIMER0_enuCompareMatchOFF,
	TIMER0_enuInvalidNonPWM_Mode,
	TIMER0_enuInvalidFastPWM_Mode,
	TIMER0_enuInvalidPhaseCorrect_Mode,
	TIMER0_enuNullPointerException,
	TIMER0_enuReachedOverflowValue,
	
}TIMER0_enuErrorStatus;

/* Timer Status */
typedef enum
{
	TIMER_0_enuIDLE=0,
	TIMER_0_enuBusy,
	TIMER_0_enuNumberOfTimerStatus
}TIMER0_tenuTimerStatus;

/* Waveform Generation Modes [TCCR0] */
typedef enum
{
	TIMER_0_enuNormal_Mode=0,
	TIMER_0_enuPWM_PhaseCorrect_Mode,
	TIMER_0_enuCTC_Mode,
	TIMER_0_enuPWM_Fast_Mode,
	TIMER_0_enuNumberOfWaveformModes
}TIMER0_tenuWaveform_Modes;


/* Compare Match Output Modes "NON PWM" [TCCR0] */
typedef enum
{
	TIMER_0_enuCompareMatch_Normal=0,
	TIMER_0_enuCompareMatch_Toggle,
	TIMER_0_enuCompareMatch_Clear,
	TIMER_0_enuCompareMatch_Set,
	TIMER_0_enuNumberOfCompareMatchModes
}TIMER0_tenuCompareMatch_NonPWM_Mode;


/* Compare Match Output Modes "FAST PWM" [TCCR0] */
typedef enum
{
	TIMER_0_enuCompareMatch_FastNormal=0,
	TIMER_0_enuCompareMatch_FastReserved,
	TIMER_0_enuCompareMatch_FastClearCM_SetTop,
	TIMER_0_enuCompareMatch_FastSetCM_ClrTop,
	TIMER_0_enuFastNumberOfCompareMatchModes
}TIMER0_tenuCompareMatch_FastPWM_Mode;

/* Compare Match Output Modes "Phase Correct" [TCCR0] */
typedef enum
{
	TIMER_0_enuCompareMatch_PhaseCorrect_Normal=0,
	TIMER_0_enuCompareMatch_PhaseCorrect_Reserved,
	TIMER_0_enuCompareMatch_PhaseCorrect_ClearUpCount_SetDownCount,
	TIMER_0_enuCompareMatch_PhaseCorrect_SetUpCount_ClrDownCount,
	TIMER_0_enuPhaseCorrectNumberOfCompareMatchModes
}TIMER0_tenuCompareMatch_PhaseCorrect_Mode;


/* Clock Select */
typedef enum
{
	TIMER_0_enuDisabled=0,
	TIMER_0_enuSystemClock,
	TIMER_0_enuPrescaler_8,
	TIMER_0_enuPrescaler_64,
	TIMER_0_enuPrescaler_256,
	TIMER_0_enuPrescaler_1024,
	TIMER_0_enuCounterMode_FallingEdge,
	TIMER_0_enuCounterMode_RaisingEdge,
	TIMER_0_enuNumberOfClockSelectionSources
}TIMER0_tenuClockSelect;


/* TCCR0 Register */
typedef enum
{
	TIMER0_enuTCCR0_CS00=0,
	TIMER0_enuTCCR0_CS01,
	TIMER0_enuTCCR0_CS02,
	TIMER0_enuTCCR0_WGM01,
	TIMER0_enuTCCR0_COM00,
	TIMER0_enuTCCR0_COM01,
	TIMER0_enuTCCR0_WGM00,
	TIMER0_enuTCCR0_FOC0
}TIMER0_tenuTCCR0_Register;

/* TIMSK */
typedef enum
{
	TIMER0_enuTIMSK_TOIE0=0,
	TIMER0_enuTIMSK_OCIE0
}TIMER0_tenuTIMSK_Register;


/* Struct for Timer0 Configurations */
typedef struct 
{
	TIMER0_tenuWaveform_Modes Timer0_Mode;
	TIMER0_tenuClockSelect Timer0_Clk;
	TIMER0_tenuCompareMatch_NonPWM_Mode Timer0_CompareMatchOutput;
	TIMER0_tenuCompareMatch_FastPWM_Mode Timer0_FastPWMOutput;
	TIMER0_tenuCompareMatch_PhaseCorrect_Mode Timer0_PhaseCorrectOutput;
	u32 Timer0_PreloadValue;
}TMR0Config_t;


/**************************** APIs ******************************/
/* ============================================================ */
/*    Function : TMR0_enuInitPreCompile							*/
/*	  Input	   : void											*/
/*	  Output   : Pre-Compilation of Timer0						*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuInitPreCompile(void);
/* ============================================================ */
/*    Function : TMR0_enuInitPostCompile						*/
/*	  Input	   : void											*/
/*	  Output   : Post-Compilation of Timer0						*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuInitPostCompile(TMR0Config_t *TMR0Config);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuStart(void);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuRegisterCallback_Overflow(void (*TMR0cbf_t)(void));
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuRegisterCallback_CTC(void (*TMR0cbf_t)(void));
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuSetTimerValue (u8 Cpy_u8TimerValue);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER0_enuErrorStatus TMR0_enuSetCompareMatchValue (u8 Cpy_u8CompareMatchValue);



#endif /* TIMER0_H_ */