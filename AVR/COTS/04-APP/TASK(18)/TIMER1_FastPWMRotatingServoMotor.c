/*
 * TIMER1.c
 *
 * Created: 3/10/2023 4:44:04 PM
 * Author : Doaa
*/
#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/TIMER1.h"


int main(void)
{
	DIO_enuInit();
	
	TMR1_enuInitPreCompile();
	
	// HW Fast PWM => OC1A (PD5)
	/* Setting Top Value */
	TMR1_enuSetICRValue(20000);				// 20 msec
	
	u8 LocalCounter =0;
    /* Replace with your application code */
    while (1) 
    {
		// As Actual Servo motors works with 750msec => 2500msec to rotate the 180 degrees
		for (LocalCounter = 750; LocalCounter <= 2500; LocalCounter++)
		{	
			/* Setting Compare Match Value */
			TMR1_enuSetCompareMatch_A(LocalCounter);	
			// Delay
			Delay_MS(5);
		}
			
    }
}

