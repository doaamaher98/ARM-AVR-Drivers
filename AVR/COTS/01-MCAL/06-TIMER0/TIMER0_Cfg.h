/*
 * TIMER0_Cfg.h
 *
 * Created: 3/3/2023 4:12:26 AM
 *  Author: Doaa
 */ 
#ifndef TIMER0_CFG_H_
#define TIMER0_CFG_H_


/************************ Configurations for pre-build *************************************/
/* Options :
   -----------
   TIMER0_ON
   TIMER0_OFF
*/
#define			TIMER0_State			TIMER0_ON

/* Options :
   ---------
   TIMER_0_enuNormal_Mode
   TIMER_0_enuPWM_PhaseCorrect_Mode
   TIMER_0_enuCTC_Mode
   TIMER_0_enuPWM_Fast_Mode
*/   
#define			TIMER0_Wave				TIMER_0_enuNormal_Mode


/* Options :
   ---------
   TIMER0_CounterMode 
   TIMER0_TimerMode 
*/
#define			TIMER0_Mode				TIMER0_CounterMode

/* Options :
   ---------
   TIMER_0_enuPrescaler_8
   TIMER_0_enuPrescaler_64
   TIMER_0_enuPrescaler_128
   TIMER_0_enuPrescaler_256
   TIMER_0_enuPrescaler_1024
*/
#define			TIMER0_ClockSrc			TIMER_0_enuPrescaler_8

/* Options :
   ---------
   TIMER_0_enuCounterMode_FallingEdge
   TIMER_0_enuCounterMode_RaisingEdge
*/
#define			TIMER0_Counter			TIMER_0_enuCounterMode_FallingEdge

/* Options :
   ---------
   TIMER0_NoPrescaler
*/
#define			TIMER0_Clk				TIMER0_NoPrescaler

/* Options :
   ---------
   TIMER0_InterruptON
   TIMER0_InterruptOFF
*/
#define			TIMER0_SysInterrupt		TIMER0_InterruptON	

/* Options :
   ---------
   TIMER0_Overflow_Interrupt_EN
   TIMER0_CompareMatch_Interrupt_EN
*/
#define			TIMER0_InterruptSrc		TIMER0_Overflow_Interrupt_EN

/* Options :
   ---------
   TIMER0_CompareMatchON
   TIMER0_CompareMatchOFF
*/
#define			TIMER0_CompareMatch						TIMER0_CompareMatchON

/* Options :
   ---------
   TIMER_0_enuCompareMatch_Normal
   TIMER_0_enuCompareMatch_Toggle
   TIMER_0_enuCompareMatch_Clear
   TIMER_0_enuCompareMatch_Set
   TIMER0_CompareMatchOFF
*/
#define			TIMER0_CompareMatch_NonPWM_Mode			TIMER_0_enuCompareMatch_Normal

/* Options :
   ---------
   TIMER_0_enuCompareMatch_FastNormal
   TIMER_0_enuCompareMatch_FastToggle
   TIMER_0_enuCompareMatch_FastClear
   TIMER_0_enuCompareMatch_FastSet
   TIMER0_CompareMatchOFF
*/
#define			TIMER0_CompareMatch_FastPWM_Mode		TIMER_0_enuCompareMatch_FastNormal

/* Options :
   ---------
   TIMER_0_enuCompareMatch_PhaseCorrect_Normal
   TIMER_0_enuCompareMatch_PhaseCorrect_Toggle
   TIMER_0_enuCompareMatch_PhaseCorrect_Clear
   TIMER_0_enuCompareMatch_PhaseCorrect_Set
   TIMER0_CompareMatchOFF
*/
#define			TIMER0_CompareMatch_PhaseCorrect_Mode	TIMER_0_enuCompareMatch_PhaseCorrect_Normal


#endif /* TIMER0_CFG_H_ */