/*
 * TIMER1.c
 *
 * Created: 3/10/2023 4:44:04 PM
 * Author : Doaa
*/
#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/ADC.h"
#include "../01-MCAL/GIE.h"
#include "../01-MCAL/TIMER1.h"


/* Mapping Function to map reading */
s32 Mapping_Func (s32 Cpy_s32MinInput, s32 Cpy_s32MaxInput, s32 Cpy_s32MinOutput, s32 Cpy_s32MaxOutput, s32 Cpy_s32Input);


int main(void)
{
	DIO_enuInit();
	
	ADC_EnableADC();
	ADC_SetChannelNumber(ADC_enuChannel0);
	ADC_SetVoltageReference(ADC_enuExternalAREF);
	ADC_SetDataAdjustment(ADC_enuADLAR_RightAdjust);
	ADC_SetPrescaler(ADC_enuPrescalerDiv128);
	
	ADC_StartADCConversion();
	
	TMR1Config_UnitA_t Timer1_Cfg;
	
	Timer1_Cfg.TIMER1A_Clk= TIMER_1_enuPrescaler_8;
	Timer1_Cfg.TIMER1A_FastPWMOutput= TIMER_1_enuCompareMatchA_FastClearCM_SetButton;
	Timer1_Cfg.TIMER1A_Mode = TIMER_1_enuPWM_Fast_ICR1_Mode;
	
	TMR1_enuInitPostCompileA(&Timer1_Cfg);
	
	// HW Fast PWM => OC1A (PD5)
	/* Setting Top Value */
	TMR1_enuSetICRValue(20000);				// 20 msec
	
	u8 LocalCounter =0;
	u16 ADC_POT_VAL =0;
	u16 ADC_Reading;
	
	s32 Mapping_Val;
	
    /* Replace with your application code */
    while (1) 
    {
		/*************** 0 -> 180 Degrees on Servo *********************/
		/* Reading the ADC Val on POT */
		ADC_SynchReadADC_Channel10_Bit(&ADC_POT_VAL);
		/* Calling Mapping function to map the reading of the POT */
		Mapping_Val = Mapping_Func(0,1024,750,2500,ADC_POT_VAL);
		/* Passing the value after mapping to Timer1 (OCR) */
		TMR1_enuSetCompareMatch_A(Mapping_Val);
    }
}

/* Mapping Function */
s32 Mapping_Func (s32 Cpy_s32MinInput, s32 Cpy_s32MaxInput, s32 Cpy_s32MinOutput, s32 Cpy_s32MaxOutput, s32 Cpy_s32Input)
{
	s32 Local_s32Output = 0;
	
	Local_s32Output = Cpy_s32Input - Cpy_s32MinInput;
	
	Local_s32Output *= (Cpy_s32MaxOutput - Cpy_s32MinOutput);
	Local_s32Output /= (Cpy_s32MaxInput - Cpy_s32MinInput);
	Local_s32Output += Cpy_s32MinOutput;
	
	return Local_s32Output;
} 