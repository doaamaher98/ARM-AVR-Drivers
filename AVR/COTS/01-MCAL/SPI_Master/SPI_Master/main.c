/*
 * SPI_Master.c
 *
 * Created: 4/14/2023 7:48:21 AM
 * Author : engdo
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "SPI_Master_Interface.h"
#include "UART_Interface.h"


int main(void)
{
	u8 Data =0;
	
	/* Configure USART */
	UART0.EnableMode = USART_Tx_Rx;
	UART0.BaudRate = 9600;
	UART0.CommunicationMode = USART_Async_DoubleSpeed;
	UART0.ControlFrame = USART_ParityDisable_1Stop;
	UART0.DataFrame = USART_8bitData;
	UART0.CommunicationTerminal= USART_SingleProcessor;
	UART0.InterruptSource = USART_InterruptDisable;
	USART_Init();
	SPI_voidInit();
	
	while(1)
	{
		/* Rx Data From UART */
		Data = USART_ReadByte_Blocking();
		
		/* Out 0 to SS pin To Select uc */
		//PORTB &= ~(1<<4);
		SPI_voidSendByte(Data);
		/* Out 1 to SS pin To Terminate Communication */
		//PORTB |= (1<<4);
	}
}

