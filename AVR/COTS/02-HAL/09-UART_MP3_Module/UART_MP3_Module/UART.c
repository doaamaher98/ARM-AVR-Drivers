#include "UART_Interface.h"


#include "avr/delay.h"
#include "avr/interrupt.h"

#define NULL_PTR		((void *) 0x00)

USART_ConfigurationStruct  UART0 = {
	 0,
	.RXC_InterruptCall  = NULL_PTR,
	.TXC_InterruptCall  = NULL_PTR,
	.UDRE_InterruptCall = NULL_PTR 
};

ISR(USART_RXC_vect)
{
	if ( UART0.RXC_InterruptCall != NULL_PTR)
	{
		UART0.RXC_InterruptCall();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

ISR(USART_TXC_vect)
{
	if ( UART0.TXC_InterruptCall != NULL_PTR)
	{
		UART0.TXC_InterruptCall();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

ISR(USART_UDRE_vect)
{
	if ( UART0.UDRE_InterruptCall != NULL_PTR)
	{
		UART0.UDRE_InterruptCall();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

void USART_voidInit(void)
{
	u8 UCSRA_Temp=0;
	u8 UCSRB_Temp=0;
	u8 UCSRC_Temp=0;
	
	f32 UBRR_Temp=0;
	
	switch(UART0.EnableMode)
	{
		case UART_enuDisabled:
		break;
		case UART_enuRX_EN:
		UCSRB_Temp |= (1<<RXEN);
		break;
		case UART_enuTX_EN:
		UCSRB_Temp |= (1<<TXEN);
		break;
		case UART_enuTX_RX_EN:
		UCSRB_Temp |= (1<<RXEN) | (1<<TXEN);
		break;
		default:
		break;
	}
	
	switch (UART0.CommMode)
	{
		case UART_enuAsynch_NormalSpeed:
		UBRR_Temp = (((float)F_CPU) / (16.0 * UART0.BaudRate)) - 0.5;
		break;
		case  UART_enuAsynch_DoubleSpeed:
		UCSRA_Temp |= (1<<U2X);
		UBRR_Temp = (((float)F_CPU) / (8.0 * UART0.BaudRate)) - 0.5;
		break;
		case UART_enuSynch_Mode:
		UCSRC_Temp |= (1<<UMSEL);
		UBRR_Temp = (((float)F_CPU) / (2.0 * UART0.BaudRate)) - 0.5;
		switch (UART0.ClockPolarity)
		{
			case  UART_enuSampleOnFalling:
			break;
			case  UART_enuSampleOnRaising:
			UCSRC_Temp |= (1<<UCPOL);
			break;
		}
		break;
		default:
		break;
	}
	switch(UART0.ProcessorMode)
	{
		case UART_enuSingleProcessor:
		break;
		case UART_enuMultiProcessor:
		UCSRA_Temp |= (1<<MPCM);
		break;
		default:
		break;
	}
	
	switch(UART0.InterruptSrc)
	{
		case  UART_enuInterrupts_DS:
		break;
		case  UART_enuInterrupt_RXC:
		UCSRB_Temp |= (1<<RXCIE);
		break;
		case UART_enuInterrupt_TXC:
		UCSRB_Temp |= (1<<TXCIE);
		break;
		case UART_enuInterrupt_UDR_Empty:
		UCSRB_Temp |= (1<<UDRE);
		break;
		case UART_enuInterrupt_RXC_TXC:
		UCSRB_Temp |= (1<<TXCIE) | (1<<RXCIE);
		break;
		case UART_enuInterrupt_RXC_UDR_Empty:
		UCSRB_Temp |= (1<<UDRE) | (1<<RXCIE);
		break;
		case UART_enuInterrupt_TXC_UDR_Empty:
		UCSRB_Temp |= (1<<UDRE) | (1<<TXCIE);
		break;
		case UART_enuInterrupt_RXC_TXC_UDR_Empty:
		UCSRB_Temp |= (1<<UDRE) | (1<<TXCIE) | (1<<RXCIE);
		break;
		default:
		break;
	}
	
	switch(UART0.DataFrame)
	{
		case  UART_enu_5_DataBits:
		break;
		case  UART_enu_6_DataBits:
		UCSRC_Temp |= (1<<UCSZ0);
		break;
		case  UART_enu_7_DataBits:
		UCSRC_Temp |= (1<<UCSZ1);
		break;
		case  UART_enu_8_DataBits:
		UCSRC_Temp |= (1<<UCSZ0) | (1<<UCSZ1);
		break;
		case  UART_enu_9_DataBits:
		UCSRC_Temp |= (1<<UCSZ0) | (1<<UCSZ1);
		UCSRB_Temp |= (1<<UCSZ2);
		break;
		default:
		break;
	}
	
	switch (UART0.ControlFrame)
	{
		case  UART_Parity_DS_1_Stop:
		break;
		case  UART_Parity_DS_2_Stop:
		UCSRC_Temp |= (1<<USBS);
		break;
		case  UART_Parity_EVEN_1_Stop:
		UCSRC_Temp |= (1<<UPM1);
		break;
		case UART_Parity_EVEN_2_Stop:
		UCSRC_Temp |= (1<<USBS) | (1<<UPM1);
		break;
		case UART_Parity_ODD_1_Stop:
		UCSRC_Temp |= (1<<UPM0) | (1<<UPM1);
		break;
		case UART_Parity_ODD_2_Stop:
		UCSRC_Temp |= (1<<USBS) | (1<<UPM0) | (1<<UPM1);
		break;
	}
	
	UBRRH = ( (u16) UBRR_Temp) >> 8;
	UBRRL = ( (u8) UBRR_Temp);
	
	UCSRA = UCSRA_Temp;
	UCSRC = UCSRC_Temp;
	UCSRB = UCSRB_Temp;
}

void USART_voidSendByte_Synchronous(u16 Data)
{
	while((UCSRA & (1<<UDRE)) == 0){}
	
	if (UART0.DataFrame ==  UART_enu_9_DataBits)
	{
		UCSRB = (UCSRB & 0xFE) | ((Data & (1<<8)) >> 8);
	}
	UDR = (u8) Data;
}

void USART_voidSendByte_Asynchronous(u16 Data)
{
	if ((UCSRA & (1<<UDRE)) != 0)
	{
		if (UART0.DataFrame == UART_enu_9_DataBits)
		{
			UCSRB = (UCSRB & 0xFE) | ((Data & (1<<8)) >> 8);
		}
		UDR = (u8) Data;
	}
}

u16 USART_voidReadByte_Synchronous(void)
{
	u16 rxData = 0;
	
	while ( (UCSRA & (1<<RXC)) == 0){}
	
	if (UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE)))
	{
		// Error : You Should Handle it as you Wish
		if (UCSRA & (1<<FE))
		{
			UART0.ErrorType = UART_enuFrameError;
		}
		else if (UCSRA & (1<<DOR))
		{
			UART0.ErrorType =  UART_enuOverRunError;
		}
		else
		{
			UART0.ErrorType =  UART_enuParityError;
		}
	}
	
	if (UART0.DataFrame ==  UART_enu_9_DataBits)
	{
		rxData =  UCSRB & (1<<RXB8) << 7;
	}
	
	rxData |= UDR;
	
	return rxData;
}

u16 USART_voidReadByte_Asynchronous(void)
{
	u16 rxData = 0;
	
	if( (UCSRA & (1<<RXC)) != 0)
	{
		
		if (UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE)))
		{
			// Error : You Should Handle it as you Wish
			if (UCSRA & (1<<FE))
			{
				UART0.ErrorType =  UART_enuFrameError;
			}
			else if (UCSRA & (1<<DOR))
			{
				UART0.ErrorType =  UART_enuOverRunError;
			}
			else
			{
				UART0.ErrorType =  UART_enuParityError;
			}
		}
		
		if (UART0.DataFrame ==  UART_enu_9_DataBits)
		{
			rxData =  UCSRB & (1<<RXB8) << 7;
		}
		rxData |= UDR;
	}
	return rxData;
}