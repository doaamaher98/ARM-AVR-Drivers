/*
 * main.c
 *
 * Created: 3/11/2023 7:04:38 AM
 * Author : Doaa Maher
 */ 

#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/GIE.h"

#include "../03-HAL/LED.h"

void main(void)
{
	DIO_enuInit();
	UART_enuNotConfigInit();

	u8 LocalData=0;

	while (1)
	{
		LocalData = UART_u8RecieveData();

		if (LocalData == '1')
		{
			HAL_LED_ON(LED_enuPin0);
		}

		else if (LocalData == '0')
		{
			HAL_LED_OFF(LED_enuPin0);
		}
	}
	UART_voidSendData('Done');
}
