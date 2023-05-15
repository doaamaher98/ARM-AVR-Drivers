/*
 * SPI_Slave.c
 *
 * Created: 4/14/2023 7:48:50 AM
 * Author : engdo
 */ 

#include <avr/io.h>

#include "./MCAL/UART_Interface.h"
#include "./MCAL/SPI_Slave_Interface.h"


int main(void)
{
	u8 Data = 0;
	
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
		unsigned char Data = 0;

		Data = SPI_u8ReadByte();
		
		USART_SendByte_Blocking(Data);
	}
}

