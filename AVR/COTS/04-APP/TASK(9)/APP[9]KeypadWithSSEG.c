

#include <avr/io.h>

#include "Delay.h"
#include "DIO.h"
#include "LED.h"
#include "KEYPAD.h"
#include "SSEGMENT.h"

int main(void)
{
	DIO_enuInit();

	// Displaying zero by default
	HAL_SSEG_Display(DIO_enuPORTB,0);
	
	u8 Status;
    /* Replace with your application code */
    while (1) 
    {
		HAL_GET_KEYPAD_KEY(&Status);
		Delay_MS(50);
		HAL_SSEG_Display(DIO_enuPORTB,Status);
    }
	

}