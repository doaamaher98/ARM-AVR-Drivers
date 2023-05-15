/*
 * TIMER1_Cfg.h
 *
 * Created: 10/3/2023 4:12:26 AM
 *  Author: Doaa
 */ 
#ifndef TIMER1_CFG_H_
#define TIMER1_CFG_H_


/************************ Configurations for pre-build *************************************/
/* Options :
   -----------
   TIMER1_ON
   TIMER1_OFF
*/
#define			TIMER1_State			TIMER1_ON

/* Options :
   ---------
   TIMER_1_enuNormal_Mode
   TIMER_1_enuPWM_PhaseCorrect_8_Mode
   TIMER_1_enuPWM_PhaseCorrect_9_Mode
   TIMER_1_enuPWM_PhaseCorrect_10_Mode
   TIMER_1_enuCTC_Mode
   TIMER_1_enuPWM_Fast_8_Mode
   TIMER_1_enuPWM_Fast_9_Mode
   TIMER_1_enuPWM_Fast_10_Mode
   TIMER_1_enuPWM_PhaseFreqCorrect_Mode_ICR1
   TIMER_1_enuPWM_PhaseFreqCorrect_Mode_OCR1A
   TIMER_1_enuPWM_PhaseCorrect_Mode_ICR1
   TIMER_1_enuPWM_PhaseCorrect_Mode_OCR1A
   TIMER_1_enuCTC_Mode_ICR1
   TIMER_1_enuPWM_Fast_Mode_ICR1
   TIMER_1_enuPWM_Fast_Mode_OCR1A				
*/   
#define			TIMER1_Wave								TIMER_1_enuPWM_Fast_Mode_ICR1


/* Options :
   ---------
   TIMER_1_Unit_A
   TIMER_1_Unit_B
*/   
#define			TIMER1_CMUnit							TIMER_1_Unit_A

/* Options :
   ---------
   TIMER1_Non_PWM 
   TIMER1_Fast_PWM
   TIMER1_PhaseCorrectFreq_PWM 
*/
#define			TIMER1_CompareOutputMode				TIMER1_Fast_PWM


/* Options :
   ---------
   TIMER_1_enuSystemClock,
   TIMER_1_enuPrescaler_8,
   TIMER_1_enuPrescaler_64,
   TIMER_1_enuPrescaler_256,
   TIMER_1_enuPrescaler_1024,
   TIMER_1_enuCounterMode_FallingEdge,
   TIMER_1_enuCounterMode_RaisingEdge,
*/
#define			TIMER1_ClockSrc			TIMER_1_enuPrescaler_8


/* Options :
   ---------
   TIMER1_Prescaler
   TIMER1_NoPrescaler
*/
#define			TIMER1_Clk				TIMER1_NoPrescaler


/* Options :
   ---------
   TIMER1_InterruptON
   TIMER1_InterruptOFF
*/
#define			TIMER1_SysInterrupt		TIMER1_InterruptON	

/* Options :
   ---------
   TIMER1_InputCaptureUnit_Interrupt_EN
   TIMER1_OutputCompareMatch_A_Interrupt_EN
   TIMER1_OutputCompareMatch_B_Interrupt_EN
   TIMER1_Overflow_Interrupt_EN				
*/
#define			TIMER1_InterruptSrc		TIMER1_OutputCompareMatch_A_Interrupt_EN


/* Options :
   ---------
   TIMER_1_enuCompareMatchA_Normal,
   TIMER_1_enuCompareMatchA_Toggle,
   TIMER_1_enuCompareMatchA_Clear,
   TIMER_1_enuCompareMatchA_Set,
*/
#define			TIMER1_CompareMatchA_NonPWM_Mode			TIMER_1_enuCompareMatchA_Normal

/* Options :
   ---------
   TIMER_1_enuCompareMatchB_FastNormal,
   TIMER_1_enuCompareMatchB_FastWGM,
   TIMER_1_enuCompareMatchB_FastClearCM_SetButton,			// Non-inverting
   TIMER_1_enuCompareMatchB_FastSetCM_ClrButton,			// Inverting
   TIMER_1_enuFastNumberOfBCompareMatchModes
*/
#define			TIMER1_CompareMatchB_NonPWM_Mode			TIMER_1_enuCompareMatchB_FastNormal
	
/* Options :
   ---------
   TIMER_1_enuCompareMatchA_FastNormal,
   TIMER_1_enuCompareMatchA_FastWGM,
   TIMER_1_enuCompareMatchA_FastClearCM_SetButton,			// Non-inverting
   TIMER_1_enuCompareMatchA_FastSetCM_ClrButton,			// Inverting
*/
#define			TIMER1_CompareMatchA_FastPWM_Mode			TIMER_1_enuCompareMatchA_FastNormal

/* Options :
   ---------
   TIMER_1_enuCompareMatchB_FastNormal,
   TIMER_1_enuCompareMatchB_FastWGM,
   TIMER_1_enuCompareMatchB_FastClearCM_SetButton,			// Non-inverting
   TIMER_1_enuCompareMatchB_FastSetCM_ClrButton,			// Inverting
*/
#define			TIMER1_CompareMatchB_FastPWM_Mode			TIMER_1_enuCompareMatchB_FastNormal

/* Options :
   ---------
   TIMER_1_enuCompareMatchA_PhaseCorrect_Normal,
   TIMER_1_enuCompareMatchA_PhaseCorrect_WGM,
   TIMER_1_enuCompareMatchA_PhaseCorrect_ClearUpCount_SetDownCount,
   TIMER_1_enuCompareMatchA_PhaseCorrect_SetUpCount_ClrDownCount,
*/
#define			TIMER1_PhaseCorrFreqA_Mode					TIMER_1_enuCompareMatchA_PhaseCorrect_Normal

/* Options :
   ---------
   TIMER_1_enuCompareMatchB_PhaseCorrect_Normal,
   TIMER_1_enuCompareMatchB_PhaseCorrect_WGM,
   TIMER_1_enuCompareMatchB_PhaseCorrect_ClearUpCount_SetDownCount,
   TIMER_1_enuCompareMatchB_PhaseCorrect_SetUpCount_ClrDownCount,
*/
#define			TIMER1_PhaseCorrFreqB_Mode					TIMER_1_enuCompareMatchB_PhaseCorrect_Normal



#endif /* TIMER1_CFG_H_ */