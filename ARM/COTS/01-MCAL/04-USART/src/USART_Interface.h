/*
 * UART_Interface.h
 *
 *  Created on: Apr 6, 2023
 *      Author: Doaa Maher
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include "Std_Types.h"
#include "USART_Config.h"

/* USART :
 * 1- Supports both Synchronous & Asynchronous Communication
 * 2- Supports half duplex Single wire communication, as well as full duplex.
 * 3- Supports LIN (Local Interconnection network)
 * 4- DMA is used for multibuffer configuration for a high speed data communication.
 * 5- NRZ standard format.
 * 6- Oversampling methods by 16 or 8
 * 7- Fractional baud rate generator
 * 8- Data bits are (8,9)
 * 9- Stop bits are (1,2)
 * 10- Separated enable bits for TX and RX
 * 11- Flags for transfer detection as :
 * 	1- RX buffer full.
 * 	2- TX buffer empty
 * 	3- End of trasmission flags.
 * 12- Parity bit (1)
 * 13- Error detection flags :
 * 	1- Overrun Error
 * 	2- Noise Detection
 * 	3- Frame Error
 * 	4- Parity Error
 * 14- Has 10 Interrupt sources !! [CTS, LIN break, TX register empty, TX completed, RX register full, IDLE line RX, + the 4 Errors.
 * 15- In mute mode if address match was wrong.
 * 16- Wakes up from the mute mode by the IDLE line detection or Address mark detection.
 * 17- 2 RX wakeup modes :
 * 	1- Address bit (9th MSB)
 * 	2- IDLE line.
 */
/* Pins :
 * 1- RX [Input]
 * 2- TX [Output]
 * 3- Common Ground
 */
/* Frame :
 * 1- IDLE line prior to TX or RX
 * 2- Start bit (1)
 * 3- Data Bits (8,9) [LSb first]
 * 4- Stop Bits (1,2,0.5,1.5) to indicate the frame is completed.
 * 5- Fractional baud rate with a [12-bit mantissa and 4-bit fraction]
 * 6- Status Register (USART_SR)
 * 7- Data Register (USART_DR)
 * 8- Baud rate Register (USART_BRR) [12-bit mantissa and 4-bit fraction]
 * 9- Guardtime Register (USART_GTPR) in case of smartcard mode.
 *
 */
/* 1- Synchronous Mode : [Needs a clock] : CK pin
 * CK pin : Transmitter clock output, in parallel, data can be received synchronous on RX, it can be used to control peripherals that have shift registers as [LCD drivers].
 * Clock & Polarity phases are software programmed.
 * In smartcard mode, CK pin can provide clock to the smartcard.
 */
/* CTS & RTS Pins : Pins required in HW flow control mode :
 * 1- CTS : "Clear to Send" blocks the data TX at the end of the current transfer when it's high. [end of Transmission]
 * 2- RTS : "Request to Send" indicates that the USART is ready to receive a data when it's low.  [start of Receiving]
 */
/* USART Character Description :
 * 1- Data bits maybe (8 or 9) according to the M-bit in the USART_CR1 Register.
 * 2- TX Pin is LOW 	: States the Start bit, and when TX pin is HIGH : Indicates the stop bit.
 * 3- IDLE Character 	: It's an entire frame of 1's followed by the Start bit = [number of stop bits] of the next frame
 * 		TX:		11111111110:start_bit
 * 4- Break Character   : It's an entire frame of 0's Received, At it's end, the TX inserts (1 or 2 stop bits)=1's to acknowledge the start bit.
 * 		RX:		00000000001:stop_bit			=> 0:start_bit
 * 5- TX & RX shares the same baud rate generator, the clock for each is generated when it's EN bit is Set.
 */
/* Transmitter  :
 * ==============
 * 1- When the TX_EN bit is Set in TX shift register, the TX gets it clock pulses on the CK Pin.
 * Character TX :
 * ===============
 * 1- In USART_TX, data shifts out LSb first on the TX pin, USART_DR has a buffer [TDR] between internal bus & transmit shift register.
 * 2- Every character is preceded by a start bit : 0 for one bit period. Character terminates by a configurable number or stop bits that could be (1,2,1.5,0.5)
 * 3- NOTE: The enable Pin [TE] should not be reset during the Transmission, with resetting it, the data would be corrupted on the TX pin due to the stopping of the baud rate counters, so the current data transmitted will be lost.
 * 4- IDLE frame is send after [TE] is enabled.
 * Stop Bits : [Are programmed in Control register2, bits #12,#13]
 * ==========
 * 1- 1 Stop bit	: DEFAULT
 * 2- 2 Stop bits	: Supported by Normal USART, single-wire and modem modes.
 * 3- 0.5 Stop bit	: Used while receiving data in smartcard mode.
 * 4- 1.5 Stop bits	: Used while receiving & transmitting in smartcard mode.
 * 5- They are placed at the IDLE line frame "1's"
 * 6- NOTE : Break Transmission "0's" will be 10-low bits followed by the number of stop bits "1's"
 * Procedure :-
 * =============
 * 1- Enable the USART by Setting UE bit in [USART_CR1]
 * 2- Program the M-bit in [USART_CR1] to define Word length
 * 3- Program the Stop bits in [USART_CR2]
 * 4- Select DMA enable [DMAT]bit in [USART_CR3] if Multibuffer communication will take place, with configuring the DMA register.
 * 5- Select the Desired Baud rate in the [USART_BRR]
 * 6- Set the [TE]bit in the [USART_CR1] to enable TX and send it the Clock to make an IDLE frame as first transmission.
 * 7- Write the Data to send in the [USART_DR] which clears the [TXE bit], repeat this for each data transmitted if single buffer.
 * 8- After Writing the data in the [USART_DR], poll for the flag [TC=1] to indicate that the transmission is completed.
 *
 * NOTE : [TXE] bit is cleared when we write on the [USART_DR]
 * Single Byte Communication :-
 * ============================
 * 1- [TXE]bit is Set by HW as it indicates :-
 * i-	That the data moved from [TDR] to shift register & the transmission has started.
 * ii-	That [TDR] register is empty.
 * iii-	That the next data can be written in the [USRAT_DR] without overwritting the previous data.
 * 2- This flag generates an interrupt is the [TXEIE]bit is Set.
 * 3- When Transmission Takes places, 	A WRITE INSTRUCTION to the [USART_DR] is made and data is stored in the [TDR] register which is copied in the shift register at the end of the current transmission.
 * 4- When No Transmission Takes place, A WRITE INSTRUCTION to the [USART_DR] is made to place the data directly in the shift register, the data transmission then starts and [TXE]bit is Set.
 *
 * 5- If a frame is transmitted after the stop bit and the [TXE] is Set THEN the [TC] is SET! and an interrupt is generated if the [TCIE]bit is set in [USART_CR1].
 * 6- After writing the last data in the [USART_DR], You must poll to wait the [TC] to be Set before Disabling the USRAT or let the controller to enter low power mode.
 * 7- [TC]bit is cleared by Software Sequences :
 * i -	 We read from the [USART_SR]
 * ii- 	 We write to the  [USART_DR]
 * iii-	 We write 0 to it, this clearing sequence is recommended only for multibuffer communication
 *
 * Break Characters :-
 * =================
 * 1- Setting the SBK-bit transmits a break character.
 * 2- Break frame length depends on M-bit
 * 3- If SBK-bit is Set =1 			=> 	A break character is sent on the TX line after finishing the current character transmission.
 * 4- This bit is reset by HW when the break character is completed.
 * 5- the USART inserts a logic "1" at the end of the last break frame to guarantee the recognition of the start bit of the next frame.
 * 6- NOTE : if the SW resets the SBK-bit before the break transmission, the break character will not be transmitted!
 * 7- For 2 consecutive breaks, the SBK-bit should be Set after the stop bit of the previous break.
 *
 * IDLE Characters :-
 * ==================
 * 1- Setting the [TE]bit drives the USART to send an IDLE line frame before the first data frame.
 */
/* Receiver :-
 * ===========
 * 1- The USART can receive data (8 or 9) bits depending on the M-bit in the [USART_CR1]
 *
 * Start Bit Detection :-
 * ======================
 * 1- It's the same when oversampling by 16 or 8.
 * 2- The start bit is detected when a specific sequence of samples are recognized :
 * 		Sequence : 1 1 1 0 X 0 X 0 X 0 0 0 0
 * 3- If the Sequence is not completed, the start bit detection aborts and the receiver returns to the IDLE state and waits for a Falling Edge.
 * 4- Start bit is confirmed [RXNE]flag is set & [RXNEIE=1] interrupt too if :
 *
 * 5- Start bit is validated [RXNE]flag is set & [RXNEIE=1] interrupt but the [NE]noise flag is set if both samples are at 0.
 *
 * Character Reception :-
 * ======================
 * 1- Data is shifted in the LSb first through the RX pin.
 * 2- the [USART_DR] has a buffer [RDR] between internal bus and the received shift register.
 *
 * Procedure :-
 * ============
 * 1- Enable the USART by Setting [UE]bit in [USART_CR1]
 * 2- Program the M-bit in the [USART_CR1] to define the word length.
 * 3- Program the number of stop bits in [USART_CR2]
 * 4- Select DMA EN [DMAR] in [USART_CR3] if multibuffer communication is taking place.
 * 5- Select the desired baud rate using the [USART_BRR]
 * 6- Set the [RE]bit in [USART_CR1] to enable receiver to start looking for the start bit.
 *
 * When a character is received :-
 * ===============================
 * 1- [RXNE]bit is Set to indicate that the content of the shift register is transfered to [RDR] : Data is received and can be read.
 * 2- [RXNEIE]bit is Set : Interrupt is generated.
 * 3- Error flags could be set if there were a frame error, noise, or an overrun detected in the reception.
 * 4- If multibuffer, [RXNE] is Set after every received byte and it's cleared by the DMA read to the Data register.
 * 5- If singlebuffer, [RXNE] is Cleared by SW read to the [USART_DR].
 * 6- The [RXNE]flag could also be cleared by writing 0 to it.
 * 7- the [RXNE]flag must be cleared before the reception of the next character to avoid overrun error.
 * NOTE : The [RE]bit should not be reset while receiving data, if this happened, reception will be aborted.
 * NOTE : When a break character is received, the USART handles it as a framing ERROR!
 * NOTE : When an idle frame is detected, the same procedure as data received character + an interrupt if [IDLEIE]bit is set will occur.
 *
 * Overrun Error :-
 * ================
 * 1- It occurs when a character is received when [RXNE] has not reset.
 * 2- Thus, data can't be transfered from the shift register to the RSR register until the [RXNE] is reset.
 * 3- The [RXNE] flag is set after every byte is received.
 * When the Overrun happens :-
 * ============================
 * 1- [ORE]bit is Set
 * 2- RDR won't be lost.
 * 3- Shift register will be overwritten.
 * 4- An interrupt is generated if [RXNEIE]bit is set or both [EIE] & [DMAR] are set.
 * 5- [ORE]bit is reset by reading the [USART_SR] followed by [USART_DR] read operation.
 *
 * When this bit is set, it indicates that at least 1 data has been lost :
 * 1- if [RXNE=1] then the last valid data is stored in RDR and can be read.
 * 2- if [RXNE=0] then the last valid data has been read and nothing to read in the RDR.
 *
 *
 * Framing Error :-
 * ================
 * 1- It's detected when the stop bit/s isn't recognized on reception at the expected time.
 *
 * When the framing error happens :-
 * ================================
 * 1- [FE]bit = 1 by HW
 * 2- Invalid data transferred from the shift register to the [USART_DR] register.
 * 3- No interrupt is generated in case of 1 byte communication.
 * 4- It's reset by [USART_SR] read operation followed by [USART_DR] read operation.
 */
/* Fractional Baud rate Generation :
 * 1- It's the same value for the RX & TX
 * 2- It's programmed in the Mantissa & Fraction values of USARTDIV
 * 3- Equation (1) :
 * ===================
 * 								 fClk
 * TX/RX Baud Rate = ---------------------------------
 * 						  8 x (2-OVER8) * USARTDIV
 * 1- USRATDIV is an unsigned fixed point number thats coded at [USART_BRR]
 * 2- When OVER8=0		=> The fractional part is coded on 4-bits, thus, programmed by DIV_fraction[3:0]bits in [USART_BRR]
 * 3- When OVER8=1		=> The fractional part is coded on 3-bits, thus, programmed by DIV_fraction[2:0]bits in [USART_BRR] and bit DIV_fraction[3] must be CLEARED.
 *
 * NOTE : The baud counters are updated with new values in baud registers after write operation to [USART_BRR] is done.
 *
 */
/* Transmission :
 * * 1- Enable the USART by Setting UE bit in [USART_CR1]
 * 2- Program the M-bit in [USART_CR1] to define Word length
 * 3- Program the Stop bits in [USART_CR2]
 * 4- Select DMA enable [DMAT]bit in [USART_CR3] if Multibuffer communication will take place, with configuring the DMA register.
 * 5- Select the Desired Baud rate in the [USART_BRR]
 * 6- Set the [TE]bit in the [USART_CR1] to enable TX and send it the Clock to make an IDLE frame as first transmission.
 * 7- Write the Data to send in the [USART_DR] which clears the [TXE bit], repeat this for each data transmitted if single buffer.
 * 8- After Writing the data in the [USART_DR], poll for the flag [TC=1] to indicate that the transmission is completed.
 */

#include "GPIO.h"
/* ====================== Defines ============================== */
#define				IDLE				0
#define				BUSY				1

#define				INIT				2
#define				NOT_INIT			3

// USARTs
#define				USART1				0
#define				USART2				1
#define				USART6				2

/* ======================== Pre-processor ========================= */
/* ============ USART_SR ================= */
//// Clearing the SR Register
//#define					USART_SR_CLR				0x00000000
//// Getting the Parity Error Bit in Receiver Mode, CLR by SW. [0:No PE, 1:PE]
//#define					USART_SR_PE_GET				((USART_SR >> USART_enuPE) &1)
//// Getting the Framing Error Bit	[0:No FE, 1:FE] ; IT DOES NOT GENERATE AN INTERRPUT!, but the RXNE generates it.
//#define					USART_SR_FE_GET				((USART_SR >> USART_enuFE) &1)
//// Getting the Nose Error Bit		[0: No NF, 1:NF] ; Cleared by a SW Sequence (READ SR then DR); IT DOES NOT GENERATE AN INTERRUPT, but the RXNE does.
//#define					USART_SR_NF_GET				((USART_SR >> USART_enuNF) &1)
//// Getting the Overrun Error Bit in Receiver Mode, INTERRUPT GENERATED when RXNEIE=1 in USART_CR1, Clr by SW sequence [read SR then read DR]
//#define					USART_SR_ORE_GET			((USART_SR >> USART_enuORE) &1)
//// Getting the IDLE line Bit, Interrupt generated when IDLEIE=1 in USART_CR1, Clr by SW sequence [read SR then read DR]
//#define					USART_SR_IDLE_GET			((USART_SR >> USART_enuIDLE) &1)
//// Getting the RXNE Read Data Register not Empty, when the RDR shift register has been transferred, [0:Data not received, 1:Data received] it's Set by HW [RXNEIE=1] in USART_CR1, Clr by Read DR and also by Writing 0 to it [clearing is recommended for Multibuffer comm. "DMA"
//#define					USART_SR_RXNE_GET			((USART_SR >> USART_enuRXNE) &1)
//// Clearing the RXNE Bit MASK [&] : as it's r/w
//#define					USART_SR_RXNE_CLR			0xFFFFFFDF
//// Getting the TC Bit, [0: TX not completed, 1:TX completed], Interrupt generated when [TCIE=1] in USART_CR1, Clr by sequence [Read SR WRITE DR], can be clr by SW too.
//#define					USART_SR_TC_GET				((USART_SR >> USART_enuTC) &1)
//// Clearing the TC Bit Mask [&]   : as it's r/w
//#define					USART_SR_TC_CLR				0xFFFFFFCF
//// Getting the TXE Bit, Interrupt generated when [TXEIE=1] in USART_CR1, clr by WRITE DR. [0:not transferred, 1:transferred]
//#define					USART_SR_TXE_GET			((USART_SR >> USART_enuTXE) &1)
//// Getting the LBD Bit, Interrupt generated when [LBDIE=1] in USART_CR2, clr by SW
//#define					USART_SR_LBD_GET			((USART_SR >> USART_enuLBD) &1)
//// Clearing the LBD Bit Mask [&]  : as it's r/w
//#define					USART_SR_LBD_CLR			0xFFFFFEFF
//// Getting the CTS Bit, Interrupt is generated if [CTSIE=1] in USART_CR3 [0:no change in CTS line, 1:Change in CTS line]
//#define					USART_SR_CTS_GET			((USART_SR >> USART_enuCTS) &1)
//// Clearing the CTS Bit Mask [&]  : as it's r/w
//#define					USART_SR_CTS_CLR			0xFFFFFDFF

/* ============ USART_DR ================= */
#define					USART_DR_DATA_BITS			9

/* ============ USART_BRR ================= */
#define					USART_BRR_FRACTION_BITS		4 		// when [OVER8=1 MSb is cleared]
#define					USART_BRR_MANTISSA_BITS		12

#define					USART_BRR_DIV_FRACTION_BIT3_CLR		0xFFFFFFF7

#define					USART_BRR_FRACTION_PART_SET		0x00000001
#define					USART_BRR_MANTISSA_PART_SET		0x00001110
#define					USART_BRR_CLR					0x00000000
/* ============ USART_CR1 ================= */
#define					USART_CR1_SBK_SET			0x00000001	// Send break characters
#define					USART_CR1_SBK_CLR			0xFFFFFFFE

#define					USART_CR1_RWU_SET			0x00000002	// RX wakeup, To determine if USART was in mute mode or not, [Set=Mute, Clr=Active]
#define					USART_CR1_RWU_CLR			0xFFFFFFFD

#define					USART_CR1_RE_SET			0x00000004	// [Set:Enable RX and search for start bit, CLR:disable RX]
#define					USART_CR1_RE_CLR			0xFFFFFFFC

#define					USART_CR1_TE_SET			0x00000008	// [Set:Enable TX  CLR:disable TX]
#define					USART_CR1_TE_CLR			0xFFFFFFF7

#define					USART_CR1_IDLEIE_EN			0x00000010	// [Set:Enable INT , CLR:disable INT]
#define					USART_CR1_IDLEIE_DS			0xFFFFFFEF

#define					USART_CR1_RXNEIE_EN			0x00000020	// [Set:Enable INT , CLR:disable INT]
#define					USART_CR1_RXNEIE_DS			0xFFFFFFDF

#define					USART_CR1_TCIE_EN			0x00000040	// [Set:Enable INT , CLR:disable INT]
#define					USART_CR1_TCIE_DS			0xFFFFFFBF

#define					USART_CR1_TXEIE_EN			0x00000080	// [Set:Enable INT , CLR:disable INT]
#define					USART_CR1_TXEIE_DS			0xFFFFFF7F

#define					USART_CR1_PEIE_EN			0x00000100	// [Set:Enable INT , CLR:disable INT]
#define					USART_CR1_PEIE_DS			0xFFFFFEFF

#define					USART_CR1_PS_ODD			0x00000200	// [Set:ODD Parity , CLR:EVEN Parity]
#define					USART_CR1_PS_EVEN			0xFFFFFBFF
#define					USART_CR1_PS_CLR			0xFFFFFBFF

#define					USART_CR1_PCE_EN			0x00000400	// [Set: PCE EN , CLR: PCE DS]
#define					USART_CR1_PCE_DS			0xFFFFFCFF
#define					USART_STOP_CLR_MASK			0xFFFFCFFF


#define					USART_CR1_WAKE_ADD_MARK		0x00000800	// Address Mark
#define					USART_CR1_WAKE_IDLE_LINE	0xFFFFF7FF	// IDLE Line

#define					USART_CR1_8_DATA_BITS		0xFFFFEFFF
#define					USART_CR1_9_DATA_BITS		0x00001000
#define					USART_CR1_DATABITS_CLR		0xFFFFEFFF

#define					USART_CR1_EN				0x00002000
#define					USART_CR1_DS				0xFFFFDFFF

#define					USART_CR1_OVERSAMPLE_DIV_8	0x00008000
#define					USART_CR1_OVERSAMPLE_DIV_16	0xFFFF7FFF

/* ============ USART_CR2 ================= */
#define					USART_CR2_LBDL_11_BITS		0x00000020
#define					USART_CR2_LCDL_10_BITS		0xFFFFFFDF

#define					USART_CR2_LBDIE_INTERRUPT_EN	0x00000040
#define					USART_CR2_LBDIE_INTERRUPT_DS	0xFFFFFFB0

#define					USART_CR2_LBCL_OP				0x00000100
#define					USART_CR2_LBCL_NOT_OP			0xFFFFFEFF

#define					USART_CR2_CPHA_SECOND			0x00000200
#define					USART_CR2_CPHA_FIRST			0xFFFFFDFF

#define					USART_CR2_CPOL_HIGH				0x00000400	// Steady high on CK pin
#define					USART_CR2_CPOL_LOW				0xFFFFFBFF	// Steady low on CK pin

#define					USART_CR2_CLKEN					0x00000800
#define					USART_CR2_CLKDS					0xFFFFF7FF

#define					USART_CR2_1_STOP_BITS			0x00000000
#define					USART_CR2_0_5_STOP_BITS			0x00001000
#define					USART_CR2_2_STOP_BITS			0x00002000
#define					USART_CR2_1_5_STOP_BITS			0x00003000

#define					USART_CR2_LINEN					0x00004000
#define					USART_CR2_LINDS					0xFFFFBFFF

/* ============ USART_CR3 ================= */
#define					USART_CR3_EIE_EN				0x00000001
#define					USART_CR3_EIE_DS				0xFFFFFFFE

#define					USART_CR3_IRDA_EN				0x00000002
#define					USART_CR3_IRDA_DS				0xFFFFFFFD

#define					USART_CR3_IRDA_LOW_POWER_MODE	0x00000004
#define					USART_CR3_IRDA_NORMAL_MODE		0xFFFFFFFB

#define					USART_CR3_HALF_DUPLEX_ON		0x00000008
#define					USART_CR3_HALF_DUPLEX_OFF		0xFFFFFFF7

#define					USART_CR3_NACK_EN				0x00000010
#define					USART_CR3_NACK_DS				0xFFFFFFEF

#define					USART_CR3_SMARTCARD_EN			0x00000020
#define					USART_CR3_SMARTCARD_DS			0xFFFFFFDF

#define					USART_CR3_DMA_RX_EN				0x00000040
#define					USART_CR3_DMA_RX_DS				0xFFFFFFBF

#define					USART_CR3_DMA_TX_EN				0x00000080
#define					USART_CR3_DMA_TX_DS				0xFFFFFF7F

#define					USART_CR3_RTSE_INTERRUPT_EN		0x00000100
#define					USART_CR3_RTSE_INTERRUPT_DS		0xFFFFFEFF

#define					USART_CR3_CTSE_INTERRUPT_EN		0x00000200
#define					USART_CR3_CTSE_INTERRUPT_DS		0xFFFFFDFF

#define					USART_CR3_CTSIE_INTERRUPT_EN	0x00000400
#define					USART_CR3_CTSIE_INTERRUPT_DS	0xFFFFFBFF

#define					USART_CR3_1_SAMPLE_METHOD		0x00000800
#define					USART_CR3_3_SAMPLE_METHOD		0xFFFFF7FF

/* ============ USART_GTPR ================= */
#define					USART_GTPR_PRESCALER_BITS		8
#define					USART_GTPR_GUARD_TIME_BITS		8


/* ======================= User-defined Types ========================= */
// Error Status
typedef enum
{
	USART_enuOK=0,
	USART_enuNOK,
	USART_enuBUSY,
	USART_enuWaiting,
	USART_enuNullPointer,
}USART_tenuErrorStatus;

// USART State
typedef enum
{
	USART_enuDS=0,
	USART_enuEN
}USART_enuState;

// USART Mode
typedef enum
{
	USART_enuSend=0,
	USART_enuReceive
}USART_enuTXRXModes;

// Number Of USART
typedef enum
{
	USART_enuUSART1=0,
	USART_enuUSART2,
	USART_enuUSART6,
	USART_enuNumberOfChannels
}USART_enuChannels;

// Data Bits
typedef enum
{
	USART_enu_8_DataBits=0,
	USART_enu_9_DataBits
}USART_tenuDataBits;

// Parity Control
typedef enum
{
	USART_enuPARITY_EN=0,
	USART_enuPARITY_DS,
}USART_tenuParityControl;

// Parity Type
typedef enum
{
	USART_enuOddParity=0,
	USART_enuEvenParity,
	USART_enuNoParity,
}USART_tenuParityType;

// Oversampling options
typedef enum
{
	USART_enuOverSampling_DIV_16=0,
	USART_enuOverSampling_DIV_8,
}USART_tenuOverSampling;

// Stop Bits Options
typedef enum
{
	USART_enuStopBits_1=0,
	USART_enuStopBits_1_5,
	USART_enuStopBits_2,
	USART_enuStopBits_0_5
}USART_tenuStopBits;

// TX State
typedef enum
{
	USART_enuTX_EN=0,
	USART_enuTX_DS
}USART_tenuTXState;

// RX State
typedef enum
{
	USART_enuRX_EN=0,
	USART_enuRX_DS
}USART_tenuRXState;

// USART_SR : Status Register
typedef enum
{
	USART_enuPE=0,			// r
	USART_enuFE,            // r
	USART_enuNF,            // r
	USART_enuORE,           // r
	USART_enuIDLE,          // r
	USART_enuRXNE,			// r/w
	USART_enuTC,			// r/w
	USART_enuTXE,			// r
	USART_enuLBD,
	USART_enuCTS,
}USART_tenuSR_Register;

// USART_BRR : Baud rate register
typedef enum
{
	USART_enuDIV_Fraction0=0,
	USART_enuDIV_Fraction1,
	USART_enuDIV_Fraction2,
	USART_enuDIV_Fraction3,
	USART_enuDIV_Mantissa0,
	USART_enuDIV_Mantissa1,
	USART_enuDIV_Mantissa2,
	USART_enuDIV_Mantissa3,
	USART_enuDIV_Mantissa4,
	USART_enuDIV_Mantissa5,
	USART_enuDIV_Mantissa6,
	USART_enuDIV_Mantissa7,
	USART_enuDIV_Mantissa8,
	USART_enuDIV_Mantissa9,
	USART_enuDIV_Mantissa10,
	USART_enuDIV_Mantissa11
}USART_tenuBRR_Register;

// USART_GTPR : Prescaler Values [LOW POWER BaudRate]
typedef enum
{
	USART_enuPrescaler_Div_1=0x00000001,
	USART_enuPrescaler_Div_2,
	USART_enuPrescaler_Div_3,
	USART_enuPrescaler_Div_4,
	USART_enuPrescaler_Div_5,

}USART_tenuPrescaler;

// USART_CR1 : Control Register [1]
typedef enum
{
	USART_enuSBK=0,
	USART_enuRWU,
	USART_enuRE,
	USART_enuTE,
	USART_enuIDLEIE,
	USART_enuRXNEIE,
	USART_enuTCIE,
	USART_enuTXEIE,
	USART_enuPEIE,
	USART_enuPS,
	USART_enuPCE,
	USART_enuWAKE,
	USART_enuM,
	USART_enuUE,
	USART_enuOVER8=15,
}USART_tenuCR1_Register;

// USART_CR2 : Control Register [2]
typedef enum
{
	USART_enuAdd0=0,
	USART_enuAdd1,
	USART_enuAdd2,
	USART_enuAdd3,
	USART_enuLBDL =5,
	USART_enuLBDIE,
	USART_enuLBCL=8,
	USART_enuCPHA,
	USART_enuCPOL,
	USART_enuCLKEN,
	USART_enuStop0,
	USART_enuStop1,
	USART_enuLINEN,
}USART_tenuCR2_Register;

// USART_CR3 : Control Register [3]
typedef enum
{
	USART_enuEIE=0,
	USART_enuIREN,
	USART_enuIRLP,
	USART_enuHDSEL,
	USART_enuNACK,
	USART_enuSCEN,
	USART_enuDMAR,
	USART_enuDMAT,
	USART_enuRTSE,
	USART_enuCTSE,
	USART_enuCTSIE,
	USART_enuONEBIT,
}USART_tenuCR3_Register;

// USART Interrupts
typedef enum
{
	USART_enuTransmitDataRegisterEmpty_Interrupt=0,
	USART_enuCTS_Flag_Interrupt,
	USART_enuTransmissionComplete_Interrupt,
	USART_enuReceivedDataReadyToRead_Interrupt,
	USART_enuOverrunError_Interrupt,
	USART_enuIDLEline_Interrupt,
	USART_enuParityError_Interrupt,
	USART_enuBreakFlag_Interrupt,
	USART_enuNoiseFlag_OverrunError_FramingError_DMA_Interrupt,
	USART_enuNumberOfInterrupts
}USART_enuInterrupts;

// USART Modes
typedef enum
{
	USART_enuAsynch_Mode=0,
	USART_enuSynch_Mode,

	USART_enuHWFlow_Mode,
	USART_enuDMA_Mode,
	USART_enuMultiprocessor_Mode,
	USART_enuSmartCard_Mode,
	USART_enuHalfDuplex_Mode,
	USART_enuIrDA_Mode,
	USART_enuLIN_Mode
}USART_enuModes;

// USART Pins [TX,RX]
typedef struct
{
	GPIO_tsrt_PortConfig_t USART_TX;
	GPIO_tsrt_PortConfig_t USART_RX;
}USART_tstrPins_t;

// USART Configuration Structure to be used in initialization function
typedef struct
{
	USART_enuChannels			USART_Channel;		// channel number
	USART_enuState				USART_Enable;		// usart enable or disable
	USART_tenuDataBits			USART_DataBits;		// number of data bits
	USART_tenuParityControl		USART_ParityControl;// parity en or ds
	USART_tenuParityType		USART_ParityType;	// number of parity bits
	USART_tenuOverSampling		USART_OverSampling; // div 8 or div 16
	USART_tenuStopBits			USART_StopBits;		// 1,2,1.5,0.5
	u32							USART_BaudRate;		// baudrate
	USART_tenuTXState			USART_TX_Enable;	// en or ds
	USART_tenuRXState			USART_RX_Enable;	// en or ds
	USART_enuInterrupts		 	USART_Interrupt_Src;// interrupt src
	USART_tstrPins_t		 	USART_Pins;
	u8							USART_TXDataRegisterEmpty; // interrupt TX
	u8							USART_RXDataRegisterEmpty; // interrupt RX
	u8							USART_TXCompleteInterrupt; // interrupt TXC
}USART_tstrConfig_t;

// Array of USARTs with their Configurations
extern USART_tstrConfig_t USART_Cfg [NUMBER_OF_USART_CHANNELS];

// Callback Function
typedef void (*Callback_t)(void);


/* ============================================ APIs ===================================================== */
/* Function 	: USART_enuInit
 * Input		: Object of USART_tstrConfig_t
 * Return   	: Error Status to ensure function safety
 * Description  : The USART is Configured by Setting Pin #10 as AF.
 * 				  The USART channel is selected from the AF.
 */
USART_tenuErrorStatus USART_enuInit(USART_tstrConfig_t * USART_Config);

/* Function 	: USART_enuSendAsynchZeroCpy
 * Input		: Object of USART_Channel to detect wanted channel
 * 				  Data Buffer
 * 				  Data Size
 * 				  Callback function to Send data Asynchronous
 * Return   	: Error Status to ensure function safety
 * Description  : Sending the Data Buffer Asynchronous
 */
extern USART_tenuErrorStatus USART_enuSendAsynchZeroCpy (USART_enuChannels USART_Channel, u8 * Data_Buffer, u32 Data_Size , Callback_t Cpy_Cbf);

/* Function 	: USART_enuReceiveAsynchZeroCpy
 * Input		: Object of USART_Channel to detect wanted channel
 * 				  Data Buffer
 * 				  Data Size
 * 				  Callback function to Send data Asynchronous
 * Return   	: Error Status to ensure function safety
 * Description  : Receiving the Data Buffer Asynchronous
 */
extern USART_tenuErrorStatus USART_enuReceiveAsynchZeroCpy (USART_enuChannels USART_Channel, u8 * Received_Buffer, u32 Data_Size , Callback_t Cpy_Cbf);



extern u8 USART_u8GetCurrentStatus (void);

#endif /* USART_INTERFACE_H_ */
