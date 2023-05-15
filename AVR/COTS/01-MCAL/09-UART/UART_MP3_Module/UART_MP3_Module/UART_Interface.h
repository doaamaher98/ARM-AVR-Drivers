/*
 * UART_Interface.h
 *
 * Created: 4/12/2023 5:03:11 AM
 *  Author: engdo
 */ 

/* For linking time Configuration Driver */
/* For Post-build Configurable Driver */
/* For making Prebuild Driver */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "Std_Types.h"

// Enum for Error Status
typedef enum
{
	UART_enuOK=0,
	UART_enuNOK,
	UART_enuParityError,
	UART_enuOverRunError,
	UART_enuFrameError,
}UART_tenuErrorStatus;

// Enum for UART Processor Mode
typedef enum
{
	UART_enuSingleProcessor=0,
	UART_enuMultiProcessor,
}UART_tenuProcessorMode;

// Enum for UART Modes
// typedef enum
// {
// 	UART_enuAsynch_Mode=0,
// 	UART_enuSynch_Mode
// }UART_tenuMode;

// Enum for UART Speed Modes [Synch & Asynch]
typedef enum
{
	UART_enuAsynch_NormalSpeed=0,
	UART_enuAsynch_DoubleSpeed,
	UART_enuSynch_Mode
}UART_tenuCommunicationModes;

// Enum for Enable Mode [TX or RX or Both]
typedef enum
{
	UART_enuDisabled=0,
	UART_enuTX_EN,
	UART_enuRX_EN,
	UART_enuTX_RX_EN,
}UART_tenuEnableMode;

// Enum for Interrupts
typedef enum
{
	UART_enuInterrupts_DS =0,
	UART_enuInterrupt_RXC,
	UART_enuInterrupt_TXC,
	UART_enuInterrupt_UDR_Empty,
	UART_enuInterrupt_RXC_TXC,
	UART_enuInterrupt_RXC_UDR_Empty,
	UART_enuInterrupt_TXC_UDR_Empty,
	UART_enuInterrupt_RXC_TXC_UDR_Empty,
}UART_tenuInterruptSource;

// Enum for Data Frame Size
typedef enum
{
	UART_enu_5_DataBits=0,
	UART_enu_6_DataBits,
	UART_enu_7_DataBits,
	UART_enu_8_DataBits,
	UART_enu_9_DataBits,	
}UART_tenuDataFrame;

// Enum for Parity and Stop Bits [Control]
typedef enum
{
	UART_Parity_DS_1_Stop=0,
	UART_Parity_DS_2_Stop,
	UART_Parity_EVEN_1_Stop,
	UART_Parity_EVEN_2_Stop,
	UART_Parity_ODD_1_Stop,
	UART_Parity_ODD_2_Stop,
}UART_tenuControlFrame;

// Enum for UART Clock polarity
typedef enum
{
	UART_enuSampleOnFalling=0,
	UART_enuSampleOnRaising,
}UART_tenuClockPolarity;

// Callback function type
typedef void (*Notification) (void);

// Struct for UART Configurations [Refere to Upper enums]
typedef struct  
{
	UART_tenuProcessorMode ProcessorMode;
	UART_tenuCommunicationModes		CommMode;
	UART_tenuEnableMode		EnableMode;
	UART_tenuInterruptSource InterruptSrc;
	UART_tenuDataFrame		DataFrame;
	UART_tenuControlFrame	 ControlFrame;
	UART_tenuClockPolarity	 ClockPolarity;		// Only if working with Synchronous Mode
	u16						 BaudRate;
	UART_tenuErrorStatus	 ErrorType;
	Notification	TXC_InterruptCall;
	Notification	RXC_InterruptCall;
	Notification	UDRE_InterruptCall;
}USART_ConfigurationStruct;

// Extern Array of Configs, Linking time build
extern const USART_ConfigurationStruct UART_Configurations ;

/* ======================= APIs ========================= */
extern USART_ConfigurationStruct   UART0;

void USART_voidInit(void);
void USART_voidSendByte_Synchronous(u16 Data);
void USART_voidSendByte_Asynchronous(u16 Data);
u16 USART_u16ReadByte_Synchronous(void);
u16 USART_u16ReadByte_Asynchronous(void);


#endif /* UART_INTERFACE_H_ */