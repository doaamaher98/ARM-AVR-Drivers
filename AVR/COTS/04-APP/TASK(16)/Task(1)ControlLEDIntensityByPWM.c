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

void PWM_LED_Intensity(void);

int main(void)
{
	u8 Compare_Match_Value = 0;	
	DIO_enuInit();
	
	TMR0Config_t TimerConfigPWM;
	
	TimerConfigPWM.Timer0_Mode = TIMER_0_enuPWM_Fast_Mode;
	TimerConfigPWM.Timer0_PreloadValue = TIMER_0_enuPrescaler_8;
	/* Non-Inverted Mode [Set on Top & Clr on Compare]
	   Duty Cycle is directly propo. with Compare Match value 
	   So, when Compare match value increases , Duty cycle increases ; Intensity Increases */
	TimerConfigPWM.Timer0_FastPWMOutput = TIMER_0_enuCompareMatch_FastClearCM_SetTop;
	
	TMR0_enuInitPostCompile(&TimerConfigPWM);
	/* Connect pin to PB3 */
	while (1)
	{
		for (Compare_Match_Value =0; Compare_Match_Value <= TIMER0_OVERFLOW_VAL; Compare_Match_Value ++)
		{
			TMR0_enuSetCompareMatchValue(Compare_Match_Value);
			Delay_MS(10);
		}	
	}
}