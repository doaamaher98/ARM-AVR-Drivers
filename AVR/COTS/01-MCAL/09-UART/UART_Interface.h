/*
 * UART_Interface.h
 *
 *  Created on: Mar 31, 2023
 *      Author: engdo
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../00-LIB/Std_Types.h"

/* ============================= Pre-Processor ================================== */
#define					UART_INTERRUPT_OFF			0
#define					UART_INTERRUPT_ON			1

#define					RX_INTERRUPT_EN			1
#define					RX_INTERRUPT_DS			0

#define					TX_INTERRUPT_EN			1
#define					TX_INTERRUPT_DS			0

#define					UDRIE_INTERRUPT_EN		1
#define					UDRIE_INTERRUPT_DS		0

#define					RX_ON					1
#define					RX_OFF					0

#define					TX_ON					1
#define					TX_OFF					0

#define					URSEL_UBRRH				0
#define					URSEL_UCSRC				1

#define					UART_MODE_ASYNCH		0
#define					UART_MODE_SYNCH			1

#define					UART_PARITY_OFF			0
#define					UART_PARITY_EVEN		2
#define					UART_PARITY_ODD			3

#define					UART_STOP_BITS_1		0
#define					UART_STOP_BITS_2		1

#define					UART_REGISTER_UBRRH		0
#define					UART_REGISTER_UCSRC		1

// 9-Bit Source
#define					UART_9TH_BIT_TRANSMITTED 0
#define					UART_9TH_BIT_RECIEVED    1

// Frequency
#define 				UART_FREQ_OSC_1MHZ			1000000UL
#define					UART_FREQ_OSC_1_8MHZ		1843200UL
#define					UART_FREQ_OSC_2MHZ			2000000UL
#define					UART_FREQ_OSC_3_6864MHZ		3686400UL
#define					UART_FREQ_OSC_4MHZ			4000000UL
#define					UART_FREQ_OSC_7_3728MHZ		7372800UL
#define					UART_FREQ_OSC_8MHZ			8000000UL
#define					UART_FREQ_OSC_11_0592MHZ	11059200UL
#define					UART_FREQ_OSC_14_7456MHZ	14745600UL
#define					UART_FREQ_OSC_16MHZ			16000000UL
#define					UART_FREQ_OSC_18_4320MHZ	18432000UL
#define					UART_FREQ_OSC_20MHZ			20000000UL

// U2X Bit
#define					UART_DOUBLE_TX_SPEED_ON			1
#define					UART_DOUBLE_TX_SPEED_OFF 		2

// MPCM Bit
#define					UART_MULTIPROCESSOR_COMM_OFF	0
#define					UART_MULTIPROCESSOR_COMM_ON 	1

// ISRs
#define					ISR_RX						13
#define					ISR_UDRE					14
#define					ISR_TX						15

#define					NONE						10
/* =============================== User-defined ================================= */
// Error Status
typedef enum
{
	UART_enuOK=0,
	UART_enuNOK,
	UART_noNoInterruptSource,
	UART_enuByteNotReceived,
	UART_enuByteNotTrasmitted,
	USART_enuInvalidClkSelection,
	UART_enuInvalidUARTMode,
	UART_enuRXFrameError,
	UART_enuRXDataOverrun,
	UART_enuParityError,
	UART_enuInvalidCharacterSize,
	UART_enuInvalidBaudRate,
	UART_enuTIMEOUT,
	UART_enuNULL_PTR,

}UART_tenuErrorStatus;

// UCSRA Register [Control Status Register A]
typedef enum
{
	UART_enuMPCM=0,
	UART_enuU2X,
	UART_enuPE,
	UART_enuDOR,
	UART_enuFE,
	UART_enuUDRE,
	UART_enuTXC,
	UART_enuRXC
}UART_tenuUCSRA_Reg;


// UCSRB Register [Control Status Register B]
typedef enum
{
	UART_enuTXB8=0,
	UART_enuRXB8,
	UART_enuUCSZ2,
	UART_enuTXEN,
	UART_enuRXEN,
	UART_enuUDRIE,
	UART_enuTXCIE,
	UART_enuRXCIE
}UART_tenuUCSRB_Reg;


// UCSRC Register [Control Status Register C]
typedef enum
{
	UART_enuUCPOL=0,
	UART_enuUCSZ0,
	UART_enuUCSZ1,
	UART_enuUSBS,
	UART_enuUPM0,
	UART_enuUPM1,
	UART_enuUMSEL,
	UART_enuURSEL_
}UART_tenuUCSRC_Reg;

// UBRRH Register : USART Baud Rate Register
typedef enum
{
	UART_enuUBRR8=0,
	UART_enuUBRR9,
	UART_enuUBRR10,
	UART_enuUBRR11,
	UART_enuURSEL=7				// Selects accessing the UBRRH=0 or UCSRC=1
}UART_tenuUBRRH_Reg;

// UBRRL Register : USART Baud Rate Register
typedef enum
{
	UART_enuUBRR0=0,
	UART_enuUBRR1,
	UART_enuUBRR2,
	UART_enuUBRR3,
	UART_enuUBRR4,
	UART_enuUBRR5,
	UART_enuUBRR6,
	UART_enuUBRR7,
}UART_tenuUBRRL_Reg;

// Baud Rate Options
typedef enum
{
	UART_enuBaudRate_2400=0,
	UART_enuBaudRate_4800,
	UART_enuBaudRate_9600,
	UART_enuBaudRate_14400,
	UART_enuBaudRate_19200,
	UART_enuBaudRate_28800,
	UART_enuBaudRate_38400,
	UART_enuBaudRate_57600,
	UART_enuBaudRate_76800,
	UART_enuBaudRate_115200,
	UART_enuBaudRate_230400,
	UART_enuBaudRate_250000,
}UART_tenuBaudRates;

// Frequency Values
typedef enum
{
	UART_enuFreqOsc_1MHz =0,
	UART_enuFreqOsc_1_84MHZ,
	UART_enuFreqOsc_2MHz,
	UART_enuFreqOsc_3_6884MHz,
	UART_enuFreqOsc_4MHz,
	UART_enuFreqOsc_7_3728MHz,
	UART_enuFreqOsc_8MHz,
	UART_enuFreqOsc_11_0592MHz,
	UART_enuFreqOsc_14_7456MHz,
	UART_enuFreqOsc_16MHz,
	UART_enuFreqOsc_18_4320MHz,
	UART_enuFreqOsc_20MHz,
}UART_tenuFrequencyValues;

// Operating Modes
typedef enum
{
	UART_enuNormalMode=0,
	UART_enuDoubleSpeedMode,
	UART_enuSynchronous_MasterMode,
}UART_tenuOperatingModes;

// Character Size : Default = 8-bits
typedef enum
{
	UART_enuCharacter_5Bits=0,
	UART_enuCharacter_6Bits,
	UART_enuCharacter_7Bits,
	UART_enuCharacter_8Bits,
	UART_enuCharacter_9Bits =7
}UART_tenuUCSZ_CharacterSize;

// Synchronous Mode ONLY, XCK Edge
typedef enum
{
	USART_enuXCK_RaisingEdge=0,
	USART_enuXCK_FallingEdge,
	USART_enuXCK_NONE
}USART_tenuClockPolarity;

/************************************ ISRs Functions ****************************************/
// 1- UART RX Complete
#define			ISR_RX_Complete(ISR_RX)				void __vector_##ISR_RX (void) __attribute__((signal));\
													void __vector_##ISR_RX (void)

// 2- UART Data Register Empty [UDRE]
#define			ISR_UDRE_Empty(ISR_UDRE)			void __vector_##ISR_UDRE (void) __attribute__((signal));\
													void __vector_##ISR_UDRE (void)
// 3- UART TX Complete
#define			ISR_TX_Complete(ISR_TX)				void __vector_##ISR_TX (void) __attribute__((signal));\
													void __vector_##ISR_TX (void)

/* ==================================== APIs ========================================== */
UART_tenuErrorStatus UART_enuInit (void);

UART_tenuErrorStatus UART_enuSendAsynchByte (u8 Cpy_u8Data);

UART_tenuErrorStatus UART_enuSendSynchByte (u8 Cpy_u8Data);

UART_tenuErrorStatus UART_enuRecieveAsynchByte (u8 *Cpy_Addu8Data);

UART_tenuErrorStatus UART_enuRecieveSynchByte (u8 *Cpy_Addu8Data);

/***********************************************************************************************/
u8 UART_u8RecieveData (void);
void UART_voidSendData (u8 Cpy_u8Data);


#endif /*UART_INTERFACE_H_ */
