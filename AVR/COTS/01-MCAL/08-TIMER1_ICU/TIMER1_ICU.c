/*
 * TIMER1.c
 *
 * Created: 10/3/2023 4:11:46 AM
 *  Author: Doaa
 */ 
#include "../00-LIB/Bit_Math.h"

#include "TIMER1_ICU.h"
#include "TIMER1_Cfg_ICU.h"
#include "TIMER1_PRIV_ICU.h"
/*****************************************************************/
#define				TIMER1_NUMBER_OF_INTERRUPT_SRC				4
/*****************************************************************/

/* Global Pointers to functions */
static void (*Notification_ICU)(void) = NULL_PTR;
static void (*Notification_CompareMatchA)(void) = NULL_PTR;
static void (*Notification_CompareMatchB)(void) = NULL_PTR;
static void (*Notification_OVF)(void) = NULL_PTR;

// OR use Array of pointer to function
static void (*NotificationArray_ptfInterrupts[TIMER1_NUMBER_OF_INTERRUPT_SRC]) = {NULL_PTR};
/*****************************************************************/

TIMER1_enuErrorStatus TMR1_enuInitPreCompile(void)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;
	/* Compare Output Mode  */
#if (TIMER1_CMUnit == TIMER_1_Unit_A)
	{
#if (TIMER1_CompareOutputMode == TIMER1_Non_PWM)
		{
#if (TIMER1_CompareMatchA_NonPWM_Mode == TIMER_1_enuCompareMatchA_Normal)
			{
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_CompareMatchA_NonPWM_Mode == TIMER_1_enuCompareMatchA_Toggle)
			{
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_CompareMatchA_NonPWM_Mode == TIMER_1_enuCompareMatchA_Clear)
			{
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_CompareMatchA_NonPWM_Mode == TIMER_1_enuCompareMatchA_Set)
			{
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#else
			LocalErrorStatus = TIMER1_enuInvalidCompareMatchNon_PWM;
#endif
		}
#elif (TIMER1_CompareOutputMode == TIMER1_Fast_PWM)
		{
#if (TIMER1_CompareMatchA_FastPWM_Mode == TIMER_1_enuCompareMatchA_FastNormal)
			{
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_CompareMatchA_FastPWM_Mode == TIMER_1_enuCompareMatchA_FastWGM)
			{
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_CompareMatchA_FastPWM_Mode == TIMER_1_enuCompareMatchA_FastClearCM_SetButton)
			{
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_CompareMatchA_FastPWM_Mode == TIMER_1_enuCompareMatchA_FastSetCM_ClrButton)
			{
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#else
			LocalErrorStatus = TIMER1_enuInvalidCompareMatchFast_PWM;
#endif
		}
#elif (TIMER1_CompareOutputMode == TIMER1_PhaseCorrectFreq_PWM)
		{
#if (TIMER1_PhaseCorrFreqA_Mode == TIMER_1_enuCompareMatchA_PhaseCorrect_Normal)
			{
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_PhaseCorrFreqA_Mode == TIMER_1_enuCompareMatchA_PhaseCorrect_WGM)
			{
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_PhaseCorrFreqA_Mode == TIMER_1_enuCompareMatchA_PhaseCorrect_ClearUpCount_SetDownCount)
			{
				CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#elif (TIMER1_PhaseCorrFreqA_Mode == TIMER_1_enuCompareMatchA_PhaseCorrect_SetUpCount_ClrDownCount)
			{
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
				SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
			}
#else
			LocalErrorStatus = TIMER1_enuInvalidCompareMatchPhaseCorrectFreq_PWM;
#endif
		}
#endif
#endif



#if (TIMER1_CMUnit == TIMER_1_Unit_B)
		{
#if (TIMER1_CompareOutputMode == TIMER1_Non_PWM)
			{
#if (TIMER1_CompareMatchB_NonPWM_Mode == TIMER_1_enuCompareMatchB_Normal)
				{
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_CompareMatchB_NonPWM_Mode == TIMER_1_enuCompareMatchB_Toggle)
				{
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_CompareMatchB_NonPWM_Mode == TIMER_1_enuCompareMatchB_Clear)
				{
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_CompareMatchB_NonPWM_Mode == TIMER_1_enuCompareMatchB_Set)
				{
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#else
				LocalErrorStatus = TIMER1_enuInvalidCompareMatchNon_PWM;

#endif
			}

#elif (TIMER1_CompareOutputMode == TIMER1_Fast_PWM)
			{
#if (TIMER1_CompareMatchB_FastPWM_Mode == TIMER_1_enuCompareMatchB_FastNormal)
				{
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_CompareMatchB_FastPWM_Mode == TIMER_1_enuCompareMatchB_FastWGM)
				{
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_CompareMatchB_FastPWM_Mode == TIMER_1_enuCompareMatchB_FastClearCM_SetButton)
				{
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_CompareMatchB_FastPWM_Mode == TIMER_1_enuCompareMatchB_FastSetCM_ClrButton)
				{
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#else
				LocalErrorStatus = TIMER1_enuInvalidCompareMatchFast_PWM;

#endif
			}

#elif (TIMER1_CompareOutputMode == TIMER1_PhaseCorrectFreq_PWM)
			{
#if (TIMER1_PhaseCorrFreqB_Mode == TIMER_1_enuCompareMatchB_PhaseCorrect_Normal)
				{
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_PhaseCorrFreqB_Mode == TIMER_1_enuCompareMatchB_PhaseCorrect_WGM)
				{
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_PhaseCorrFreqB_Mode == TIMER_1_enuCompareMatchB_PhaseCorrect_ClearUpCount_SetDownCount)
				{
					CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#elif (TIMER1_PhaseCorrFreqB_Mode == TIMER_1_enuCompareMatchB_PhaseCorrect_SetUpCount_ClrDownCount)
				{
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
					SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
				}
#else
				LocalErrorStatus = TIMER1_enuInvalidCompareMatchPhaseCorrectFreq_PWM;
#endif
			}
#else
#endif
		}
#else
#endif


		/************************** Waveform Modes *****************************/
#if (TIMER1_Wave == TIMER_1_enuNormal_Mode)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseCorrect_8_Mode)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseCorrect_9_Mode)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseCorrect_10_Mode)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuCTC_Mode)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_Fast_8_Mode)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_Fast_9_Mode)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_Fast_10_Mode)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseFreqCorrect_Mode_ICR1)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseFreqCorrect_Mode_OCR1A)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseCorrect_Mode_ICR1)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_PhaseCorrect_Mode_OCR1A)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuCTC_Mode_ICR1)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_Fast_Mode_ICR1)
		{
			CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#elif (TIMER1_Wave == TIMER_1_enuPWM_Fast_Mode_OCR1A)
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		}
#else
		LocalErrorStatus = TIMER1_enuInvalidWaveGeneration;
#endif


		/********** Clock Selection ***************/
#if (TIMER1_State == TIMER1_OFF)				// Timer1 Disabled
		{
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}
#elif (TIMER1_ClockSrc == TIMER_1_enuSystemClock)
		{
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}

#elif (TIMER1_ClockSrc == TIMER_1_enuPrescaler_8)
		{
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}
#elif (TIMER1_ClockSrc == TIMER_1_enuPrescaler_64)
		{
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}
#elif (TIMER1_ClockSrc == TIMER_1_enuPrescaler_256)
		{
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}
#elif (TIMER1_ClockSrc == TIMER_1_enuPrescaler_1024)
		{
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}
#elif (TIMER1_ClockSrc == TIMER_1_enuCounterMode_FallingEdge)
		{
			CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}
#elif (TIMER1_ClockSrc == TIMER_1_enuCounterMode_RaisingEdge)
		{
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		}

#else
#endif
	}

	/******************* TIMSK **********************/
	// Enable GIE to work
#if (TIMER1_SysInterrupt == TIMER1_InterruptON)
	{
#if (TIMER1_InterruptSrc == TIMER1_InputCaptureUnit_Interrupt_EN)
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_TICIE1);
		}
#elif (TIMER1_InterruptSrc == TIMER1_OutputCompareMatch_A_Interrupt_EN)
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_OCIE1A);
		}
#elif (TIMER1_InterruptSrc == TIMER1_OutputCompareMatch_B_Interrupt_EN)
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_OCIE1B);
		}
#elif (TIMER1_InterruptSrc == TIMER1_Overflow_Interrupt_EN)
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_TOIE1);
		}
#else
#endif
	}
#else
#endif

	return LocalErrorStatus;
}
/*****************************************************************/
TIMER1_enuErrorStatus TMR1_enuInitPostCompileA(TMR1Config_UnitA_t *TMR1AConfig)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;
	/************************** Compare Output Mode ***************************/
	// 1- Non-PWM Mode
	switch(TMR1AConfig->TIMER1A_CompareMatchOutput)
	{
	case TIMER_1_enuCompareMatchA_Normal:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_Toggle:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_Clear:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_Set:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	}
	// 2-Fast PWM Mode
	switch(TMR1AConfig->TIMER1A_FastPWMOutput)
	{
	case TIMER_1_enuCompareMatchA_FastNormal:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_FastWGM:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_FastClearCM_SetButton:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_FastSetCM_ClrButton:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	}
	// 3- Phase Correct & Frequency
	switch (TMR1AConfig->TIMER1A_PhaseCorrectOutput)
	{
	case TIMER_1_enuCompareMatchA_PhaseCorrect_Normal:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_PhaseCorrect_WGM:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_PhaseCorrect_ClearUpCount_SetDownCount:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	case TIMER_1_enuCompareMatchA_PhaseCorrect_SetUpCount_ClrDownCount:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1A1);
		break;
	}
	/*********** Waveform Generation Mode ***************/
	switch (TMR1AConfig->TIMER1A_Mode)
	{
	case TIMER_1_enuNormal_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_8Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_9Bits_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_10Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuCTC_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_8Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_9Bits_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_10Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseFrequencyCorrect_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseFrequencyCorrect_OCR1A_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_OCR1A_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuCTC_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuReserved_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_OCR1A_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	}
	/*************** Clk (Prescaler) **********************/
	switch (TMR1AConfig->TIMER1A_Clk)
	{
	case TIMER_1_enuDisabled:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuSystemClock:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_8:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_64:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_256:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_1024:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuCounterMode_FallingEdge:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuCounterMode_RaisingEdge:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	}

	return LocalErrorStatus;
}
/*****************************************************************/
TIMER1_enuErrorStatus TMR1_enuInitPostCompileB(TMR1Config_UnitB_t *TMR1BConfig)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;
	/************************** Compare Output Mode ***************************/
	// 1- Non-PWM Mode
	switch(TMR1BConfig->TIMER1B_CompareMatchOutput)
	{
	case TIMER_1_enuCompareMatchB_Normal:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_Toggle:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_Clear:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_Set:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	}
	// 2-Fast PWM Mode
	switch(TMR1BConfig->TIMER1B_FastPWMOutput)
	{
	case TIMER_1_enuCompareMatchB_FastNormal:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_FastWGM:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_FastClearCM_SetButton:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_FastSetCM_ClrButton:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	}
	// 3- Phase Correct & Frequency
	switch (TMR1BConfig->TIMER1B_PhaseCorrectOutput)
	{
	case TIMER_1_enuCompareMatchB_PhaseCorrect_Normal:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_PhaseCorrect_WGM:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_PhaseCorrect_ClearUpCount_SetDownCount:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	case TIMER_1_enuCompareMatchB_PhaseCorrect_SetUpCount_ClrDownCount:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B0);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_COM1B1);
		break;
	}
	/*********** Waveform Generation Mode ***************/
	switch (TMR1BConfig->TIMER1B_Mode)
	{
	case TIMER_1_enuNormal_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_8Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_9Bits_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_10Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuCTC_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_8Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_9Bits_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_10Bits_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseFrequencyCorrect_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseFrequencyCorrect_OCR1A_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_PhaseCorrect_OCR1A_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuCTC_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuReserved_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_ICR1_Mode:
		CLR_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	case TIMER_1_enuPWM_Fast_OCR1A_Mode:
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM10);
		SET_BIT(TIMER1_TCCR1A,TIMER1_enuTCCR1A_WGM11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM12);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_WGM13);
		break;
	}
	/*************** Clk (Prescaler) **********************/
	switch (TMR1BConfig->TIMER1B_Clk)
	{
	case TIMER_1_enuDisabled:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuSystemClock:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_8:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_64:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_256:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuPrescaler_1024:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuCounterMode_FallingEdge:
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	case TIMER_1_enuCounterMode_RaisingEdge:
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS10);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS11);
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_CS12);
		break;
	}

	return LocalErrorStatus;
}
/*****************************************************************/
TIMER1_enuErrorStatus TMR1_enuSetICRValue(u16 Copy_u16TopValue)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	TIMER1_ICR1L = Copy_u16TopValue;

	return LocalErrorStatus;
}
/*****************************************************************/
TIMER1_enuErrorStatus TMR1_enuSetCompareMatch_A (u16 Cpy_u16CompareMatchValue_A)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	TIMER1_OCR1AL = Cpy_u16CompareMatchValue_A;

	return LocalErrorStatus;
}
/*****************************************************************/
TIMER1_enuErrorStatus TMR1_enuSetCompareMatch_B (u16 Cpy_u16CompareMatchValue_B)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	TIMER1_OCR1BL = Cpy_u16CompareMatchValue_B;

	return LocalErrorStatus;
}
/*****************************************************************/
TIMER1_enuErrorStatus TMR1_enuSetTimerValue (u16 Cpy_u16Value)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	/* Put the value in TCNT1 Register [Low] */
	TIMER1_TCNT1L = Cpy_u16Value;

	return LocalErrorStatus;
}
/*****************************************************************/
u16 TMR1_enuReadTimerValue (void)

{
	return TIMER1_TCNT1L;
}

/****************** Interrupt *********************/
TIMER1_enuErrorStatus TMR1_enuEnableTimer1InterruptSource (u8 Cpy_u8InterruptSrc)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_ICU)
	{
		SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_TICIE1);
	}
	else if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_CompareMatchA)
	{
		SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_OCIE1A);
	}
	else if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_CompareMatchB)
	{
		SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_OCIE1B);
	}
	else if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_OVF)
	{
		SET_BIT(TIMER1_TIMSK, TIMER1_enuTIMSK_TOIE1);
	}
	else
	{
		LocalErrorStatus = TIMER1_enuNOK;
	}

	return LocalErrorStatus;
}
/*************************************************************/
TIMER1_enuErrorStatus TMR1_enuDisableTimer1InterruptSource (u8 Cpy_u8InterruptSrc)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_ICU)
	{
		CLR_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_TICIE1);
	}
	else if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_CompareMatchA)
	{
		CLR_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_OCIE1A);
	}
	else if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_CompareMatchB)
	{
		CLR_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_OCIE1B);
	}
	else if (Cpy_u8InterruptSrc == TIMER1_InterruptSrc_OVF)
	{
		CLR_BIT(TIMER1_TIMSK, TIMER1_enuTIMSK_TOIE1);
	}
	else
	{
		LocalErrorStatus = TIMER1_enuNOK;
	}

	return LocalErrorStatus;
}
/*************************************************************/
TIMER1_enuErrorStatus TMR1_enuSetInterruptSrcCallBack (void (*Notify_Interrupt)(void),u8 Cpy_u8InterruptID)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	if (Notify_Interrupt != NULL_PTR)
	{
		if (Cpy_u8InterruptID == TIMER1_InterruptSrc_ICU)
		{
			Notification_ICU = Notify_Interrupt;
		}
		else if (Cpy_u8InterruptID == TIMER1_InterruptSrc_CompareMatchA)
		{
			Notification_CompareMatchA = Notify_Interrupt;
		}
		else if (Cpy_u8InterruptID == TIMER1_InterruptSrc_CompareMatchB)
		{
			Notification_CompareMatchB = Notify_Interrupt;
		}
		else if (Cpy_u8InterruptID == TIMER1_InterruptSrc_OVF)
		{
			Notification_OVF = Notify_Interrupt;
		}
		else
		{
			LocalErrorStatus = TIMER1_enuInvalidInterrupt;
		}
	}
	else
	{
		LocalErrorStatus = TIMER1_enuNOK;
	}
	return LocalErrorStatus;
}
/*************************************************************/

/*********************** ICU *********************************/
TIMER1_enuErrorStatus TMR1_enuICUInit(void)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	/* ICU Edge Select : Raising Edge */
	SET_BIT(TIMER1_TCCR1B, TIMER1_enuTCCR1B_ICES1);

	/* Enable ICU Interrupt */
	SET_BIT(TIMER1_TIMSK,TIMER1_enuTIMSK_TICIE1);

	return LocalErrorStatus;
}
/*************************************************************/
TIMER1_enuErrorStatus TMR1_enuSetICU_TriggerEdge (u8 Cpy_u8Trigger)
{
	TIMER1_enuErrorStatus LocalErrorStatus = TIMER1_enuOk;

	/* Trigger : Raising Edge */
	if (Cpy_u8Trigger == TIMER1_ICU_RaisingEdge)
	{
		SET_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_ICES1);
	}

	/* Trigger : Falling Edge */
	else if (Cpy_u8Trigger == TIMER1_ICU_FallingEdge)
	{
		CLR_BIT(TIMER1_TCCR1B,TIMER1_enuTCCR1B_ICES1);
	}
	else
	{
		LocalErrorStatus = TIMER1_enuNOK;
	}
	return LocalErrorStatus;
}
/*************************************************************/
u16 TMR1_u16ReadICUInputCapture (void)
{
	return TIMER1_ICR1L;
}
/*************************************************************/

/*********************** ISRs *************************/
TIMER_1_InputCaptureEvent(ISR_TIMER1_CAPTURE_EVENT)
{
	if (Notification_ICU != NULL_PTR)
	{
		Notification_ICU();
	}
}
TIMER_1_CompareMatchA_ISR(ISR_TIMER1_COMP_A)
{
	if (Notification_CompareMatchA != NULL_PTR)
	{
		Notification_CompareMatchA();
	}
}
TIMER_1_CompareMatchB_ISR(ISR_TIMER1_COMP_B)
{
	if (Notification_CompareMatchB != NULL_PTR)
	{
		Notification_CompareMatchB();
	}
}
TIMER_1_OVF_ISR(ISR_TIMER1_OVF)
{
	if (Notification_OVF != NULL_PTR)
	{
		Notification_OVF();
	}
}
