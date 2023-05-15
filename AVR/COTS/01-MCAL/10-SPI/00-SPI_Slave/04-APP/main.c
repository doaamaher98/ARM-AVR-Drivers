#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/SPI_Interface.h"

#include "../03-HAL/LED.h"

void main(void)
{
	u8 ReceivedData;

	DIO_enuInit();

	SPI_enuSlaveInit();

	while (1)
	{
		ReceivedData = SPI_u8Transcieve(10);
		Delay_MS(10);

		if (ReceivedData == 1)		/* Sent from the Master */
		{
			HAL_LED_ON(LED_enuPin0);
			Delay_MS(500);
			HAL_LED_ON(LED_enuPin1);
			Delay_MS(500);
			HAL_LED_ON(LED_enuPin2);
		}
	}

}
