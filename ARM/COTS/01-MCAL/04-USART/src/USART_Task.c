/*
 * USART_Task.c
 *
 *  Created on: Apr 12, 2023
 *      Author: engdo
 */

#include "USART_Interface.h"

void RX_Finished (void);

void USART_Task(void)
{
	u8 Data[2];
	/* Check if Current Status is IDLE to be able to be received */
	if (USART_u8GetCurrentStatus() == IDLE)
	{
		/* Receive Byte */
		USART_enuReceiveAsynchZeroCpy(USART_enuUSART1,Data,2,&RX_Finished);
	}

}

