/*
 * TIMER0.c
 *
 * Created: 3/3/2023 4:11:46 AM
 *  Author: Doaa
 */ 
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Std_Types.h"

#include "TIMER0.h"
#include "TIMER0_Cfg.h"
#include "TIMER0_PRIV.h"

#define			NULL_PTR			((void*)0)
/* Global Static Pointers to function definition */
static void (*Timer0_CallBack_Overflow)(void) = NULL;
static void (*Timer0_CallBack_CTC)(void) =		NULL;


/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuInitPreCompile(void)
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;

	/***************** Mode [WaveGeneration] ********************/
#if (TIMER0_Wave == TIMER_0_enuCTC_Mode)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM01);
//	SET_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_OCIE0);

	#if TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Normal
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM00);
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM01);

	#elif TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Toggle
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM00);
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM01);

	#elif TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Clear
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM01);

	#elif TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Set
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM00);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_COM01);
	#endif

	#elif TIMER0_Wave == TIMER_0_enuNormal_Mode

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM01);
//	SET_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_TOIE0);


#endif

	/*************** Clock Select *********************/
	/************** Timer isn't used ********************/
	// TIMER is OFF
#if (TIMER0_State == TIMER0_OFF)
	{
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
	}
	// TIMER is ON
#elif TIMER0_State == TIMER0_ON
	// 1- Timer mode
	#if TIMER0_Mode == TIMER0_TimerMode
		/* Prescaler options */
		#if TIMER0_ClockSrc == TIMER_0_enuPrescaler_8
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);

		#elif TIMER0_ClockSrc == TIMER_0_enuPrescaler_64

			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);

		#elif TIMER0_ClockSrc == TIMER_0_enuPrescaler_256

			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);

		#elif TIMER0_ClockSrc == TIMER_0_enuPrescaler_1024

			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
		#else
			LocalErrorStatus = Timer0_enuInvalidPrescaler;
		#endif

	// 2- Counter Mode
#elif TIMER0_Mode == TIMER0_CounterMode

	#if TIMER0_Counter == TIMER_0_enuCounterMode_FallingEdge

		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);

	#elif TIMER0_Counter == TIMER_0_enuCounterMode_RaisingEdge

		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
	#endif

	#else
		LocalErrorStatus = TIMER0_enuInvalidCounterMode;
	#endif

#endif


#if (TIMER0_Clk == TIMER0_NoPrescaler)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);

#else
	LocalErrorStatus = Timer0_enuNOK;
#endif

	/************ Compare Match Interrupt/ Overflow Interrupt **************/
#if TIMER0_SysInterrupt == TIMER0_InterruptON

	#if TIMER0_InterruptSrc == TIMER0_Overflow_Interrupt_EN

		SET_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_TOIE0);

	#elif TIMER0_InterruptSrc == TIMER0_CompareMatch_Interrupt_EN

		SET_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_OCIE0);
	#endif


#elif (TIMER0_SysInterrupt == TIMER0_InterruptOFF)

	CLR_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_TOIE0);
	CLR_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_OCIE0);

#else
	LocalErrorStatus = TIMER0_enuInvalidInterrupt;
#endif

	/**************** Compare Match Output Mode ***********************/
#if (TIMER0_CompareMatch == TIMER0_CompareMatchON)

	// 1- Non-PWM Mode
#if (TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Normal)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Toggle)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Clear)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_NonPWM_Mode == TIMER_0_enuCompareMatch_Set)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#else
	LocalErrorStatus = TIMER0_enuInvalidNonPWM_Mode;
#endif


	// 2- Fast PWM
#if (TIMER0_CompareMatch_FastPWM_Mode == TIMER_0_enuCompareMatch_FastNormal)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_FastPWM_Mode == TIMER_0_enuCompareMatch_FastReserved)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_FastPWM_Mode == TIMER_0_enuCompareMatch_FastClearCM_SetTop)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_FastPWM_Mode == TIMER_0_enuCompareMatch_FastSetCM_ClrTop)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#else
	LocalErrorStatus = TIMER0_enuInvalidFastPWM_Mode;
#endif

	// 3- Phase Correct
#if (TIMER0_CompareMatch_PhaseCorrect_Mode == TIMER_0_enuCompareMatch_PhaseCorrect_Normal)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_PhaseCorrect_Mode == TIMER_0_enuCompareMatch_PhaseCorrect_Reserved)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_PhaseCorrect_Mode == TIMER_0_enuCompareMatch_PhaseCorrect_ClearUpCount_SetDownCount)

	CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#elif (TIMER0_CompareMatch_PhaseCorrect_Mode == TIMER_0_enuCompareMatch_PhaseCorrect_SetUpCount_ClrDownCount)

	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
	SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);

#else
	LocalErrorStatus = TIMER0_enuInvalidPhaseCorrect_Mode;
#endif

#else
	LocalErrorStatus = TIMER0_enuCompareMatchOFF;
#endif

	return LocalErrorStatus;
}
/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuInitPostCompile(TMR0Config_t *TMR0Config)
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;

	if (TMR0Config->Timer0_Mode < TIMER_0_enuNumberOfWaveformModes)
	{
		switch(TMR0Config->Timer0_Mode)
		{
		case TIMER_0_enuNormal_Mode:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM01);

			// 			TIMER0_TCCR0 = TMR0Config->Timer0_PreloadValue;
			break;

		case TIMER_0_enuCTC_Mode:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM01);

			// 			TIMER0_OCR0 = TMR0Config->Timer0_PreloadValue;
			break;

		case TIMER_0_enuPWM_Fast_Mode:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM01);

			// 			TIMER0_OCR0 = TMR0Config->Timer0_PreloadValue;
			break;

		case TIMER_0_enuPWM_PhaseCorrect_Mode:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_WGM01);

			// 			TIMER0_OCR0 = TMR0Config->Timer0_PreloadValue;
			break;

		default:
			LocalErrorStatus = Timer0_enuInvalidMode;
		}
	}

	if (TMR0Config->Timer0_Clk < TIMER_0_enuNumberOfClockSelectionSources)
	{
		switch(TMR0Config->Timer0_Clk)
		{
		case TIMER_0_enuDisabled:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuSystemClock:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuPrescaler_8:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuPrescaler_64:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuPrescaler_256:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuPrescaler_1024:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuCounterMode_FallingEdge:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		case TIMER_0_enuCounterMode_RaisingEdge:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS02);
			break;

		default:
			LocalErrorStatus = Timer0_enuInvalidPrescaler;
		}
	}

	switch (TMR0Config->Timer0_CompareMatchOutput)
	{
	case TIMER_0_enuCompareMatch_Normal:
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		break;

	case TIMER_0_enuCompareMatch_Toggle:
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		break;

	case TIMER_0_enuCompareMatch_Clear:
		CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		break;

	case TIMER_0_enuCompareMatch_Set:
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
		SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
		break;

	default:
		LocalErrorStatus = TIMER0_enuInvalidNonPWM_Mode;
	}
	/*******************/
	if (TMR0Config->Timer0_FastPWMOutput < TIMER_0_enuFastNumberOfCompareMatchModes)
	{
		switch (TMR0Config->Timer0_FastPWMOutput)
		{
		case TIMER_0_enuCompareMatch_FastNormal:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		case TIMER_0_enuCompareMatch_FastReserved:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		case TIMER_0_enuCompareMatch_FastClearCM_SetTop:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		case TIMER_0_enuCompareMatch_FastSetCM_ClrTop:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		default:
			LocalErrorStatus = TIMER0_enuInvalidNonPWM_Mode;
		}
	}

	if (TMR0Config->Timer0_PhaseCorrectOutput < TIMER_0_enuPhaseCorrectNumberOfCompareMatchModes)
	{
		switch (TMR0Config->Timer0_PhaseCorrectOutput)
		{
		case TIMER_0_enuCompareMatch_PhaseCorrect_Normal:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		case TIMER_0_enuCompareMatch_PhaseCorrect_Reserved:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		case TIMER_0_enuCompareMatch_PhaseCorrect_ClearUpCount_SetDownCount:
			CLR_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		case TIMER_0_enuCompareMatch_PhaseCorrect_SetUpCount_ClrDownCount:
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS00);
			SET_BIT(TIMER0_TCCR0,TIMER0_enuTCCR0_CS01);
			break;

		default:
			LocalErrorStatus = TIMER0_enuInvalidNonPWM_Mode;
		}
	}

	return LocalErrorStatus;
}
/*********************************************************************************************/
/*TIMER0_enuErrorStatus TMR0_enuSetTickTimeMS(u16 Copy_u16TickTime, u32 Copy_u32Clock)
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;

}*/
/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuSetTimerValue (u8 Cpy_u8TimerValue)
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;
	if (Cpy_u8TimerValue < TIMER0_OVERFLOW_VAL)
	{
		/* Writing Preload Value */
		TIMER0_TCNT0 = Cpy_u8TimerValue;
	}
	else
	{
		LocalErrorStatus = TIMER0_enuReachedOverflowValue;
	}
	return LocalErrorStatus;
}
/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuSetCompareMatchValue(u8 Cpy_u8CompareMatchValue)
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;
	if (Cpy_u8CompareMatchValue < TIMER0_OVERFLOW_VAL)
	{
		TIMER0_OCR0 = Cpy_u8CompareMatchValue;
	}
	else
	{
		LocalErrorStatus = TIMER0_enuReachedOverflowValue;
	}

	return LocalErrorStatus;
}
/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuRegisterCallback_Overflow(void (*TMR0cbf_t)(void))
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;

	/* Set Interrupt for OVF */
	SET_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_TOIE0);

	if (TMR0cbf_t != NULL_PTR)
	{
		Timer0_CallBack_Overflow = TMR0cbf_t;
	}
	else
	{
		LocalErrorStatus = TIMER0_enuNullPointerException;
	}

	return LocalErrorStatus;
}
/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuRegisterCallback_CTC(void (*TMR0cbf_t)(void))
{
	TIMER0_enuErrorStatus LocalErrorStatus = Timer0_enuOk;

	/* Set Interrupt for CTC */
	SET_BIT(TIMER0_TIMSK,TIMER0_enuTIMSK_OCIE0);

	if (TMR0cbf_t != NULL_PTR)
	{
		Timer0_CallBack_CTC = TMR0cbf_t;
	}
	else
	{
		LocalErrorStatus = TIMER0_enuNullPointerException;
	}

	return LocalErrorStatus;
}
/*********************************************************************************************/
TIMER0_enuErrorStatus TMR0_enuStart(void)
{

}

/* Timer0 Overflow ISR */
TIMER_0_OverFlow(ISR_TIMER0_OVF)
{
	/* Check Pointer != NULL */
	if (Timer0_CallBack_Overflow != NULL_PTR)
	{
		Timer0_CallBack_Overflow();
	}
	else
	{
		/*Do nothing*/
	}
}
/*********************************************************************************************/
/* Timer0 Compare Match ISR */
TIMER_0_CompareMatch(ISR_TIMER0_COMP)
{
	/* Check Pointer != NULL */
	if (Timer0_CallBack_CTC != NULL_PTR)
	{
		Timer0_CallBack_CTC();
	}
	else
	{
		/*Do nothing*/
	}
}
/*********************************************************************************************/
