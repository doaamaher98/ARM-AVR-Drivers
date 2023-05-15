/*
 * UART_Config.h
 *
 *  Created on: Mar 31, 2023
 *      Author: engdo
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/* ========================== Pre-Compile Configs ============================ */

/* Options :
 * UART_INTERRUPT_ON
 * UART_INTERRUPT_OFF
 */
#define				UART_INTERRUPT				UART_INTERRUPT_OFF


/* Options :
 * RX_INTERRUPT_EN
 * TX_INTERRUPT_EN
 * UDRIE_INTERRUPT_EN
 * NONE
 */
#define				UART_INTERRUPT_CAUSE_1		RX_INTERRUPT_EN

/* Options :
 * RX_INTERRUPT_EN
 * TX_INTERRUPT_EN
 * UDRIE_INTERRUPT_EN
 * NONE
 */
#define				UART_INTERRUPT_CAUSE_2		TX_INTERRUPT_EN

/* Options :
 * RX_INTERRUPT_EN
 * TX_INTERRUPT_EN
 * UDRIE_INTERRUPT_EN
 * NONE
 */
#define				UART_INTERRUPT_CAUSE_3		NONE

/* Options :
 * RX_ON
 * RX_OFF
 */
#define				UART_RECIEVER_STATE			RX_ON


/* Options :
 * TX_ON
 * TX_OFF
 */
#define				UART_TANSMITTER_STATE		TX_ON


/* Options :
 * UART_enuCharacter_5Bits
 * UART_enuCharacter_6Bits
 * UART_enuCharacter_7Bits
 * UART_enuCharacter_8Bits
 * UART_enuCharacter_9Bits
 */
#define				UART_CHARACTER_SIZE			UART_enuCharacter_8Bits


/* Options :
 * UART_9TH_BIT_RECIEVED
 * UART_9TH_BIT_TRANSMITTED
 */
#define				UART_9TH_BIT				UART_9TH_BIT_RECIEVED


/* Options :
 * UART_MODE_ASYNCH
 * UART_MODE_SYNCH
 */
#define				UART_MODE_SELECTION			UART_MODE_ASYNCH


/* Options :
 * UART_PARITY_OFF
 * UART_PARITY_EVEN
 * UART_PARITY_ODD
 */
#define				UART_PARITY_SELECTION		UART_PARITY_ODD


/* Options :
 * UART_STOP_BITS_1
 * UART_STOP_BITS_2
 */
#define				UART_STOP_BITS				UART_STOP_BITS_1

/* Options :
 * USART_enuXCK_RaisingEdge
 * USART_enuXCK_FallingEdge
 * USART_enuXCK_NONE
 */
#define				USART_CLOCK_SELECTION		USART_enuXCK_NONE

/* Options :
 * UART_REGISTER_UBRRH
 * UART_REGISTER_UCSRC
 */
#define				UART_REGISTER_SELECTION		UART_REGISTER_UBRRH


/* Options :
 * UART_enuBaudRate_2400
 * UART_enuBaudRate_4800
 * UART_enuBaudRate_9600
 * UART_enuBaudRate_14400
 * UART_enuBaudRate_19200
 * UART_enuBaudRate_28800
 * UART_enuBaudRate_38400
 * UART_enuBaudRate_57600
 * UART_enuBaudRate_76800
 * UART_enuBaudRate_115200
 * UART_enuBaudRate_230400
 * UART_enuBaudRate_250000
 */
#define				UART_BAUD_RATE			UART_enuBaudRate_9600

/* Options :
 * UART_enuFreqOsc_1MHz
 * UART_enuFreqOsc_1_84MHZ
 * UART_enuFreqOsc_2MHz
 * UART_enuFreqOsc_3_6884MHz
 * UART_enuFreqOsc_4MHz
 * UART_enuFreqOsc_7_3728MHz
 * UART_enuFreqOsc_8MHz
 * UART_enuFreqOsc_11_0592MHz
 * UART_enuFreqOsc_14_7456MHz
 * UART_enuFreqOsc_16MHz
 * UART_enuFreqOsc_18_4320MHz
 * UART_enuFreqOsc_20MHz
 */
#define				UART_FREQUENCY			UART_enuFreqOsc_8MHz

/* Options :
 * UART_enuNormalMode
 * UART_enuDoubleSpeedMode
 * UART_enuSynchronous_MasterMode
 */
#define				UART_OPERATING_MODE		UART_enuNormalMode

/* Options :
 * UART_DOUBLE_TX_SPEED_ON
 * UART_DOUBLE_TX_SPEED_OFF
 */
#define				UART_DOUBLE_TX_SPEED	UART_DOUBLE_TX_SPEED_ON

/* Options :
 * UART_MULTIPROCESSOR_COMM_ON
 * UART_MULTIPROCESSOR_COMM_OFF
 */
#define				UART_MPCM_BIT			UART_MULTIPROCESSOR_COMM_OFF


#endif /* UART_CONFIG_H_ */
