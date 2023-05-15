/*
 * TIMER0.c
 *
 * Created: 3/3/2023 4:10:04 AM
 * Author : Doaa Maher
 */ 

#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Bit_Math.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/GIE.h"
#include "../01-MCAL/TIMER0.h"

#include "../02-HAL/PUSH_BUTTON.h"

#define			COMP_MATCH_COUNTS_Low		10
#define			COMP_MATCH_COUNTS_High		20

void PWM_LED_Intensity(void);

int main(void)
{
	u8 Button_1 = DIO_enuPin0;
	u8 Button_2 = DIO_enuPin1;
	
	u8 PinState1 =0;
	u8 PinState2 =0;
	
	u8 Compare_Match_Value = 0;
	
	DIO_enuInit();
	DIO_enuSetPinValue(DIO_enuPin2,DIO_enuOutputHigh);			// By default
	
	TMR0Config_t TimerConfig;
	
	TimerConfig.Timer0_Mode = TIMER_0_enuPWM_Fast_Mode;
	TimerConfig.Timer0_PreloadValue = TIMER_0_enuPrescaler_8;
	
	TMR0_enuInitPostCompile(&TimerConfig);
	TMR0_enuSetCompareMatchValue(Compare_Match_Value);			// initial
	
// 	TMR0_enuRegisterCallback_CTC(&PWM_LED_Intensity);
// 	GIE_enuInit_EnableGIE();
	
    while (1) 
    {
		Get_PUSH_BUTTON_State(DIO_enuPin0,&PinState1);
		Delay_MS(100);
		if (PinState1 == PUSH_BUTTON_enuPressed)
		{
			Compare_Match_Value+=5;
			// Check for overflow
			if (Compare_Match_Value >= TIMER0_OVERFLOW_VAL)
			{
				Compare_Match_Value = TIMER0_OVERFLOW_VAL-1;
			}
			TMR0_enuSetCompareMatchValue(Compare_Match_Value);
		}
		
		Get_PUSH_BUTTON_State(DIO_enuPin0,&PinState2);
		if (PinState2 == PUSH_BUTTON_enuReleased)
		{
			Compare_Match_Value = TIMER0_OVERFLOW_VAL;
			Compare_Match_Value -= 5;
			// Check if it goes off
			if (Compare_Match_Value <= 0)
			{
				Compare_Match_Value = 0;		// initial state
			}
			else
			{
				/*Do nothing*/
			}
			TMR0_enuSetCompareMatchValue(Compare_Match_Value);
		}	
    }
}