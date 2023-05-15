/*
 * TIMER0.c
 *
 * Created: 3/3/2023 4:10:04 AM
 * Author : Doaa Maher
 */ 

#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Bit_Math.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/GIE.h"
#include "../01-MCAL/TIMER0.h"

#define			COMP_MATCH_COUNTS		8000

void Timer_Interrupt(void);

int main(void)
{
	DIO_enuInit();
// 	DIO_enuSetPinValue(DIO_enuPin0,DIO_enuOutputHigh);		// High initially

	TMR0_enuInitPreCompile();
	TMR0_enuSetCompareMatchValue(125);
	
	TMR0_enuRegisterCallback_CTC(&Timer_Interrupt);
	
	GIE_enuInit_EnableGIE();
	
    while (1) 
    {
    }
}

/* ISR */
void Timer_Interrupt(void)
{
	static u8 LocalCounter=0;
	static u8 LocalLED_State=0;			// Flag
	
	LocalCounter ++;
	
	if (LocalCounter == COMP_MATCH_COUNTS)
	{
		if (LocalLED_State == 0)
		{
			DIO_enuSetPinValue(DIO_enuPin0,DIO_enuHigh);
		}
		else if (LocalLED_State == 1)
		{
			LocalLED_State = 1;
			DIO_enuSetPinValue(DIO_enuPin0,DIO_enuOutputLow);
		}
		
		/* Resetting local counter */
		LocalCounter =0;
	}
}
 