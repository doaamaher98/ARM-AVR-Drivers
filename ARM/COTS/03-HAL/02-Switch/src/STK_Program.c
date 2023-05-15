#include "Std_Types.h"

#include "STK_Interface.h"
#include "STK_Config.h"
#include "STK_Private.h"

/*********************** Global pointer to function to be used in callback *********************/
static systick_cbf_t App_cbf;
/***********************************************************************************************/
static u32 TIMEOUT = 200000;
static  u8 STK_Mode = 0;				// A flag for modes

/******************************************************************/
STK_tenuErrorStatus STK_enuInit(void)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Applying Clock Choice */
#if (SYSTICK_CLOCK_SOURCE == STK_CLK_SRC_AHB_DIV_8)
	{
		/* Choose the Clock Source */
		STK_CTRL |= STK_CLK_SRC_AHB_DIV_8;
	}
#elif (SYSTICK_CLOCK_SOURCE == STK_CLK_SRC_AHB)
	{
		/* Choose the Clock Source */
		STK_CTRL |= STK_CLK_SRC_AHB;
	}
#endif

	/* Disable Systick */
	STK_CTRL |= STK_COUNTER_DISABLED;

	/* Disable Systick interrupt */
	STK_CTRL &= STK_EXCEPTION_DISABLED;

	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuStartTimer (void)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Enable Systick */
	STK_CTRL |= STK_COUNTER_ENABLE;

	//	/* Clearing the Value Register */
	//	STK_VAL = 0;

	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuEnableInterrupt (void)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Enable Interrupt */
	STK_CTRL |= STK_EXCEPTION_ENABLE;

	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuDisableInterrupt (void)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Disable Interrupt */
	STK_CTRL &= STK_EXCEPTION_DISABLED;

	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuStopTimer (void)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Disable Counter */
	STK_CTRL |= STK_COUNTER_DISABLED;

	/* Disable Interrupt */
	STK_CTRL |= STK_EXCEPTION_DISABLED;

	//	/* Reset Load & Value Registers */
	//	STK_VAL = 0;
	//	STK_LOAD = 0;

	return LocalErrorStatus;
}
/******************************************************************/
// Synchronous
STK_tenuErrorStatus STK_enuSynchronousSetTickTimeMS (u32 Cpy_u32Ticks)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Load the ticks to load register */
	STK_LOAD = Cpy_u32Ticks;

	/* Start Timer */
	STK_enuStartTimer();

	/* Waiting until flag is raised */
	while (((STK_COUNTER_FLAG >> STK_COUNTER_BIT) == 0) && TIMEOUT > 0)
	{
		TIMEOUT--;
	}

	// Flag raised
	/* Stop Timer */
	STK_enuStopTimer();

	/* Resetting Load & Value registers */
	STK_LOAD = 0;
	STK_VAL = 0;

	return LocalErrorStatus;
}
/******************************************************************/
// Asynchronous
STK_tenuErrorStatus STK_enuAysnchSetIntervalSingle (u32 Cpy_u32Ticks, systick_cbf_t stk_single_interval)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/******************** Validation ************************/
	/* Loading ticks into LOAD register */
	STK_LOAD = Cpy_u32Ticks;

	/* Start Timer */
	STK_enuStartTimer();

	/* Calling the ISR */
	if (stk_single_interval != NULL_PTR)
	{
		App_cbf = stk_single_interval;
		/* Raising the flag mode to single interval */
		STK_Mode = STK_MODE_SINGLE_INTERVAL;
	}
	else
	{
		LocalErrorStatus = STK_enuNullPointer;
	}

	/* Enable Systick interrupt */
	STK_CTRL |= STK_EXCEPTION_ENABLE;

	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuAsynchSetIntervalPeriodic (u32 Cpy_u32Ticks, systick_cbf_t stk_periodic_interval)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/******************** Validation ************************/
	/* Loading ticks into LOAD register */
	STK_LOAD = Cpy_u32Ticks;

	/* Start Timer */
	STK_enuStartTimer();

	/* Calling the ISR */
	if (stk_periodic_interval != NULL_PTR)
	{
		App_cbf = stk_periodic_interval;
		/* Raising the flag mode to single interval */
		STK_Mode = STK_MODE_PERIODIC_INTERVAL;
	}
	else
	{
		LocalErrorStatus = STK_enuNullPointer;
	}

	/* Enable Systick interrupt */
	STK_CTRL |= STK_EXCEPTION_ENABLE;

	return LocalErrorStatus;
}
/******************************************************************/
/******************************************************************/
u32 STK_u32GetElapsedTime (void)
{
	/* Returning the elapsed time passed by [LOAD - VALUE] Registers */
	return (STK_VAL - STK_VAL);
}
/******************************************************************/
u32 STK_u32GetRemainingTime(void)
{
	/* Return the remaining time in VALUE Register */
	return STK_VAL;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuSetCallback (systick_cbf_t Systick_CallbackFunc)
{

	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/******************** Validation ************************/
	if (Systick_CallbackFunc != NULL_PTR)
	{
		App_cbf = Systick_CallbackFunc;
	}
	else
	{
		LocalErrorStatus = STK_enuNullPointer;
	}

	return LocalErrorStatus;

}
/******************************************************************/
STK_tenuErrorStatus STK_enuSetCounts (u32 Cpy_u32Counts)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Local Variable for calculating the counts */
	u32 Local_u32Counts = 0;

	/* Enable the counter */
	STK_CTRL |= STK_COUNTER_ENABLE;

	/* Checking the number of counts bounderies */
	if (Cpy_u32Counts >= STK_MIN_LOAD && Cpy_u32Counts <= STK_MAX_LOAD && (STK_VAL == 0))
	{
		/* For every 100 clk pulses => Setting Reload = 99 */
		Local_u32Counts = Cpy_u32Counts - 1;
		/* Clearing Load Register */
		STK_LOAD &= STK_CLR_LOAD;
		/* Setting Load Register */
		STK_LOAD |= Local_u32Counts;
	}
	else
	{
		LocalErrorStatus = STK_enuNOK;
	}
	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuSetPeriodMS (STK_tenuClockSources Cpy_u8ClkSrc, STK_tenuClockBusSource Cpy_u8ClkBus, u16 Cpy_u16PeriodMS)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Checking the Clock source if valid */
	if (Cpy_u8ClkSrc <= STK_NumberOfClockSources)
	{
		/* Switching the clock sources */
		switch (Cpy_u8ClkSrc)
		{
		case STK_enuHSI:			// 16MHz
		{
			switch (Cpy_u8ClkBus)
			{
			case STK_enuAHB :		// Processor Clock = 16MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodMS * STK_HSI_AHB_ClockMS);
				break;

			case STK_enuAHB_8:		// 2MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodMS * STK_HSI_AHB_8_ClockMS);
				break;
			}
		}
		break;
		case STK_enuHSE:			// 25MHz
		{
			switch (Cpy_u8ClkBus)
			{
			case STK_enuAHB :		// Processor Clock = 25MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodMS * STK_HSE_AHB_ClockMS);
				break;

			case STK_enuAHB_8:		// 25/8 = 3.125MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodMS * STK_HSE_AHB_8_ClockMS);
				break;
			}
			break;
		}
		}
	}
	else
	{
		LocalErrorStatus = STK_enuNOK;
	}

	return LocalErrorStatus;
}
/******************************************************************/
STK_tenuErrorStatus STK_enuSetPeriodUS (STK_tenuClockSources Cpy_u8ClkSrc, STK_tenuClockBusSource Cpy_u8ClkBus, u16 Cpy_u16PeriodUS)
{
	STK_tenuErrorStatus LocalErrorStatus = STK_enuOK;

	/* Checking the Clock source if valid */
	if (Cpy_u8ClkSrc <= STK_NumberOfClockSources)
	{
		/* Switching the clock sources */
		switch (Cpy_u8ClkSrc)
		{
		case STK_enuHSI:			// 16MHz
		{
			switch (Cpy_u8ClkBus)
			{
			case STK_enuAHB :		// Processor Clock = 16MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodUS * STK_HSI_AHB_ClockUS);
				break;

			case STK_enuAHB_8:		// 2MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodUS * STK_HSI_AHB_8_ClockUS);
				break;
			}
		}
		break;
		case STK_enuHSE:			// 25MHz
		{
			switch (Cpy_u8ClkBus)
			{
			case STK_enuAHB :		// Processor Clock = 25MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodUS * STK_HSE_AHB_ClockUS);
				break;

			case STK_enuAHB_8:		// 25/8 = 3.125MHz
				STK_LOAD &= STK_CLR_LOAD;
				STK_LOAD |= (Cpy_u16PeriodUS * STK_HSE_AHB_8_ClockUS);
				break;
			}
			break;
		}
		}
	}
	else
	{
		LocalErrorStatus = STK_enuNOK;
	}

	return LocalErrorStatus;
}
/******************************************************************/

/***** ISR ****/
void SysTick_Handler (void)
{
	if (App_cbf)
	{
		App_cbf();
	}
	else
	{
		/* Do nothing */
	}
}

/* ISR */
//void SysTick_Handler(void)
//{
//	u8 LocalSTK_Mode;
//
//	if (App_cbf != NULL_PTR)
//	{
//		if (STK_Mode == STK_MODE_SINGLE_INTERVAL)
//		{
//			STK_enuStopTimer();
//		}
//
//		/* Calling the function */
//		App_cbf();
//
//		/* Clearing the interrupt flag */
//		STK_CTRL &= ~(STK_COUNTER_FLAG);
//	}
//	else
//	{
//		/* Do nothing */
//	}
//}
