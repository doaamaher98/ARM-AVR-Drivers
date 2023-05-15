/*
 * TIMER1.h
 *
 * Created: 10/3/2023 4:12:08 AM
 *  Author: Doaa
 */ 
#ifndef TIMER1_H_
#define TIMER1_H_

#include "../01-MCAL/TIMER1_PRIV.h"

/*************************** Defines ************************/
#define			TIMER1_OFF								0
#define			TIMER1_ON								1

#define			TIMER_1_Unit_A							0
#define			TIMER_1_Unit_B							1

#define			TIMER1_Non_PWM 							0
#define			TIMER1_Fast_PWM							1
#define			TIMER1_PhaseCorrectFreq_PWM				2

#define				TIMER_1_enuNormal_Mode						0
#define				TIMER_1_enuPWM_PhaseCorrect_8_Mode			1
#define				TIMER_1_enuPWM_PhaseCorrect_9_Mode			2
#define				TIMER_1_enuPWM_PhaseCorrect_10_Mode			3
#define				TIMER_1_enuCTC_Mode							4
#define				TIMER_1_enuPWM_Fast_8_Mode					5
#define				TIMER_1_enuPWM_Fast_9_Mode					6
#define				TIMER_1_enuPWM_Fast_10_Mode					7
#define				TIMER_1_enuPWM_PhaseFreqCorrect_Mode_ICR1	8
#define				TIMER_1_enuPWM_PhaseFreqCorrect_Mode_OCR1A	9
#define				TIMER_1_enuPWM_PhaseCorrect_Mode_ICR1		10
#define				TIMER_1_enuPWM_PhaseCorrect_Mode_OCR1A		11
#define				TIMER_1_enuCTC_Mode_ICR1					12
#define				TIMER_1_enuPWM_Fast_Mode_ICR1				13
#define				TIMER_1_enuPWM_Fast_Mode_OCR1A				14

#define				TIMER1_NoPrescaler							0
#define				TIMER1_Prescaler							1

#define			TIMER1_InterruptOFF						0
#define			TIMER1_InterruptON						1

#define			TIMER1_InputCaptureUnit_Interrupt_EN			0
#define			TIMER1_OutputCompareMatch_A_Interrupt_EN		1
#define			TIMER1_OutputCompareMatch_B_Interrupt_EN		2
#define			TIMER1_Overflow_Interrupt_EN					3


#define			TIMER1_CompareMatchA_NonPWM_Mode				0
#define			TIMER1_CompareMatchB_NonPWM_Mode				1

#define			TIMER1_PhaseCorrFreqA_Mode						0 
#define			TIMER1_PhaseCorrFreqB_Mode						1

/*
	Note : Don't forget to set the I-bit in SREG register to enable GIE
*/

#define			TIMER_1_Overflow_Interrupt_Flag			0
#define			TIMER_1_CompareMatch_Interrupt_Flag		1

#define			TIMER_1_PrescalerReset					0

/****************************** Types ******************************/
/* Error Status */
typedef enum
{
	TIMER1_enuOk=0,
	TIMER1_enuNOK,
	TIMER1_enuInvalidMode,
	TIMER1_enuInvalidSysClk,
	TIMER1_enuInvalidPrescaler,
	TIMER1_enuInvalidInterrupt,
	TIMER1_enuInvalidCounterMode,
	TIMER1_enuInvalidTimer,
	TIMER1_enuOFF,
	TIMER1_enuCompareMatchOFF,
	TIMER1_enuInvalidNonPWM_Mode,
	TIMER1_enuInvalidFastPWM_Mode,
	TIMER1_enuInvalidPhaseCorrect_Mode,
	TIMER1_enuNullPointerException,
	TIMER1_enuReachedOverflowValue,
	TIMER1_enuInvalidCompareMatch_Mode,
	TIMER1_enuInvalidCompareMatchNon_PWM,
	TIMER1_enuInvalidCompareMatchFast_PWM,
	TIMER1_enuInvalidCompareMatchPhaseCorrectFreq_PWM,
	TIMER1_enuInvalidWaveGeneration,
	TIMER1_enuInterruptOFF
}TIMER1_enuErrorStatus;

/* Timer Status */
typedef enum
{
	TIMER_1_enuIDLE=0,
	TIMER_1_enuBusy,
	TIMER_1_enuNumberOfTimerStatus
}TIMER1_tenuTimerStatus;

/* Waveform Generation Modes [TCCR1A] & [TCCR1B] */
typedef enum
{
	TIMER_1_enuNormal_Mode=0,
	TIMER_1_enuPWM_PhaseCorrect_8Bits_Mode,
	TIMER_1_enuPWM_PhaseCorrect_9Bits_Mode,
	TIMER_1_enuPWM_PhaseCorrect_10Bits_Mode,
	TIMER_1_enuCTC_Mode,
	TIMER_1_enuPWM_Fast_8Bits_Mode,
	TIMER_1_enuPWM_Fast_9Bits_Mode,
	TIMER_1_enuPWM_Fast_10Bits_Mode,
	TIMER_1_enuPWM_PhaseFrequencyCorrect_ICR1_Mode,
	TIMER_1_enuPWM_PhaseFrequencyCorrect_OCR1A_Mode,
	TIMER_1_enuPWM_PhaseCorrect_ICR1_Mode,
	TIMER_1_enuPWM_PhaseCorrect_OCR1A_Mode,
	TIMER_1_enuCTC_ICR1_Mode,
	TIMER_1_enuReserved_Mode,
	TIMER_1_enuPWM_Fast_ICR1_Mode,
	TIMER_1_enuPWM_Fast_OCR1A_Mode,
	TIMER_1_enuNumberOfWaveformModes
}TIMER1_tenuWaveform_Modes;


/* Compare Match Output Modes "NON PWM" [TCCR1A] [Unit A] */
typedef enum
{
	TIMER_1_enuCompareMatchA_Normal=0,
	TIMER_1_enuCompareMatchA_Toggle,
	TIMER_1_enuCompareMatchA_Clear,
	TIMER_1_enuCompareMatchA_Set,
	TIMER_1_enuNumberOfACompareMatchModes
}TIMER1_tenuCompareMatchA_NonPWM_Mode;

/* Compare Match Output Modes "NON PWM" [TCCR1A] [Unit B] */
typedef enum
{
	TIMER_1_enuCompareMatchB_Normal=0,
	TIMER_1_enuCompareMatchB_Toggle,
	TIMER_1_enuCompareMatchB_Clear,
	TIMER_1_enuCompareMatchB_Set,
	TIMER_1_enuNumberOfBCompareMatchModes
}TIMER1_tenuCompareMatchB_NonPWM_Mode;

/**************************************************************/
/* Compare Match Output Modes "FAST PWM" [TCCR1A] [Unit A] */
typedef enum
{
	TIMER_1_enuCompareMatchA_FastNormal=0,
	TIMER_1_enuCompareMatchA_FastWGM,
	TIMER_1_enuCompareMatchA_FastClearCM_SetButton,			// Non-inverting
	TIMER_1_enuCompareMatchA_FastSetCM_ClrButton,			// Inverting
	TIMER_1_enuFastNumberOfACompareMatchModes
}TIMER1_tenuCompareMatchA_FastPWM_Mode;

/* Compare Match Output Modes "FAST PWM" [TCCR1A] [Unit B] */
typedef enum
{
	TIMER_1_enuCompareMatchB_FastNormal=0,
	TIMER_1_enuCompareMatchB_FastWGM,
	TIMER_1_enuCompareMatchB_FastClearCM_SetButton,			// Non-inverting
	TIMER_1_enuCompareMatchB_FastSetCM_ClrButton,			// Inverting
	TIMER_1_enuFastNumberOfBCompareMatchModes
}TIMER1_tenuCompareMatchB_FastPWM_Mode;

/**************************************************************/
/* Compare Match Output Modes "Phase Correct" [TCCR1A] [Unit A] */
typedef enum
{
	TIMER_1_enuCompareMatchA_PhaseCorrect_Normal=0,
	TIMER_1_enuCompareMatchA_PhaseCorrect_WGM,
	TIMER_1_enuCompareMatchA_PhaseCorrect_ClearUpCount_SetDownCount,
	TIMER_1_enuCompareMatchA_PhaseCorrect_SetUpCount_ClrDownCount,
	TIMER_1_enuPhaseCorrectANumberOfCompareMatchModes
}TIMER1_tenuCompareMatchA_PhaseCorrect_Mode;

/* Compare Match Output Modes "Phase Correct" [TCCR1A] [Unit B] */
typedef enum
{
	TIMER_1_enuCompareMatchB_PhaseCorrect_Normal=0,
	TIMER_1_enuCompareMatchB_PhaseCorrect_WGM,
	TIMER_1_enuCompareMatchB_PhaseCorrect_ClearUpCount_SetDownCount,
	TIMER_1_enuCompareMatchB_PhaseCorrect_SetUpCount_ClrDownCount,
	TIMER_1_enuPhaseCorrectBNumberOfCompareMatchModes
}TIMER1_tenuCompareMatchB_PhaseCorrect_Mode;
/**************************************************************/

/* Clock Select [TCCR1B] */
typedef enum
{
	TIMER_1_enuDisabled=0,
	TIMER_1_enuSystemClock,
	TIMER_1_enuPrescaler_8,
	TIMER_1_enuPrescaler_64,
	TIMER_1_enuPrescaler_256,
	TIMER_1_enuPrescaler_1024,
	TIMER_1_enuCounterMode_FallingEdge,
	TIMER_1_enuCounterMode_RaisingEdge,
	TIMER_1_enuNumberOfClockSelectionSources
}TIMER1_tenuClockSelect;

/**************************************************************/
/* TCCR1A Register */
typedef enum
{
	TIMER1_enuTCCR1A_WGM10=0,				// Waveform Generation Mode
	TIMER1_enuTCCR1A_WGM11,					// Waveform Generation Mode
	TIMER1_enuTCCR1A_FOC1B,					// Force Output Compare for Compare Unit B
	TIMER1_enuTCCR1A_FOC1A,					// Force Output Compare for Compare Unit A
	TIMER1_enuTCCR1A_COM1B0,				// Compare Output Mode For Compare Unit B
	TIMER1_enuTCCR1A_COM1B1,				// Compare Output Mode For Compare Unit B
	TIMER1_enuTCCR1A_COM1A0,				// Compare Output Mode For Compare Unit A
	TIMER1_enuTCCR1A_COM1A1					// Compare Output Mode For Compare Unit A
}TIMER1_tenuTCCR1A_Register;

/* TCCR1B Register */
typedef enum
{
	TIMER1_enuTCCR1B_CS10=0,				// Clock Select
	TIMER1_enuTCCR1B_CS11,					// Clock Select
	TIMER1_enuTCCR1B_CS12,					// Clock Select
	TIMER1_enuTCCR1B_WGM12,					// Waveform Generation Mode
	TIMER1_enuTCCR1B_WGM13,					// Waveform Generation Mode
	TIMER1_enuTCCR1B_NONE,					// Reserved
	TIMER1_enuTCCR1B_ICES1,					// Input Capture Edge Select
	TIMER1_enuTCCR1B_ICNC1					// Input Capture Noise Canceler
}TIMER1_tenuTCCR1B_Register;
/**************************************************************/
/* TIMSK [Interrupt Mask Register] */
typedef enum
{
	TIMER1_enuTIMSK_TOIE1=2,				// Overflow Interrupt EN
	TIMER1_enuTIMSK_OCIE1B,					// Output Compare B Interrupt EN
	TIMER1_enuTIMSK_OCIE1A,					// Output Compare A Interrupt EN
	TIMER1_enuTIMSK_TICIE1					// Input Capture Interrupt EN
}TIMER1_tenuTIMSK_Register;
/**************************************************************/
/* Interrupt Flag Register [TIFR] */
typedef enum
{
	TIMER1_enuTIMSK_TOV=2,					// Overflow Flag
	TIMER1_enuTIMSK_OCIF1B,					// Output Compare Match B Flag
	TIMER1_enuTIMSK_OCIF1A,					// Output Compare Match A Flag
	TIMER1_enuTIMSK_ICF1					// Input Capture Flag
}TIMER1_tenuTIFR_Register;
/**************************************************************/
/* Structures for TIMER1 Configurations */
/*************************************/
// Unit A
typedef struct 
{
	TIMER1_tenuWaveform_Modes			  TIMER1A_Mode;
	TIMER1_tenuClockSelect				  TIMER1A_Clk;
	TIMER1_tenuCompareMatchA_NonPWM_Mode  TIMER1A_CompareMatchOutput;
	TIMER1_tenuCompareMatchA_FastPWM_Mode TIMER1A_FastPWMOutput;
	TIMER1_tenuCompareMatchA_PhaseCorrect_Mode TIMER1A_PhaseCorrectOutput;
	u32 TIMER1_PreloadValueA;
}TMR1Config_UnitA_t;

// Unit B
typedef struct
{
	TIMER1_tenuWaveform_Modes				TIMER1B_Mode;
	TIMER1_tenuClockSelect					TIMER1B_Clk;
	TIMER1_tenuCompareMatchB_NonPWM_Mode	TIMER1B_CompareMatchOutput;
	TIMER1_tenuCompareMatchB_FastPWM_Mode	TIMER1B_FastPWMOutput;
	TIMER1_tenuCompareMatchB_PhaseCorrect_Mode TIMER1B_PhaseCorrectOutput;
	u32 TIMER1_PreloadValueB;
}TMR1Config_UnitB_t;

/* ============================================================ */
/* ========================== APIs ============================ */
/* ============================================================ */
/*    Function : TMR1_enuInitPreCompile							*/
/*	  Input	   : void											*/
/*	  Output   : Pre-Compilation of TIMER1						*/
/* ============================================================ */
TIMER1_enuErrorStatus TMR1_enuInitPreCompile(void);
/* ============================================================ */
/*    Function : TMR1_enuInitPostCompile						*/
/*	  Input	   : void											*/
/*	  Output   : Post-Compilation of TIMER1	Unit (A)			*/
/* ============================================================ */
TIMER1_enuErrorStatus TMR1_enuInitPostCompileA(TMR1Config_UnitA_t *TMR1AConfig);
/* ============================================================ */
/*    Function : TMR1_enuInitPostCompile						*/
/*	  Input	   : void											*/
/*	  Output   : Post-Compilation of TIMER1	Unit(B)				*/
/* ============================================================ */
TIMER1_enuErrorStatus TMR1_enuInitPostCompileB(TMR1Config_UnitB_t *TMR1BConfig);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER1_enuErrorStatus TMR1_enuSetICRValue(u16 Copy_u16TopValue);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER1_enuErrorStatus TMR1_enuSetCompareMatch_A (u16 Cpy_u16CompareMatchValue_A);
/* ============================================================ */
/*    Function :												*/
/*	  Input	   : 												*/
/*	  Output   : 												*/
/* ============================================================ */
TIMER1_enuErrorStatus TMR1_enuSetCompareMatch_B (u16 Cpy_u16CompareMatchValue_B);







#endif /* TIMER1_H_ */