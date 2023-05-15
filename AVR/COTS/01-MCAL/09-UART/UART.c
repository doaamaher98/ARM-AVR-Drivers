/*
 * UART.c
 *
 *  Created on: Mar 31, 2023
 *      Author: engdo
 */

#include "../00-LIB/Bit_Math.h"

#include "GIE.h"

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Config.h"

static u8 GlobalByteTX ;
static u8 *Global_AddvarRX = NULL_PTR;

/* UART :
 * 1- Wired
 * 2- Full Duplex
 * 3- Asynchronous
 * 4- P2P
 * 5- Serial
 */

/* ================================== APIs ====================================== */
UART_tenuErrorStatus UART_enuInit (void)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	/************* Checking UART Multiprocessor Communication Mode ****************/
	if (UART_MPCM_BIT == UART_MULTIPROCESSOR_COMM_ON)
	{
		SET_BIT(UART_UCSRA,UART_enuMPCM);
	}
	else if (UART_MPCM_BIT == UART_MULTIPROCESSOR_COMM_OFF)
	{
		/* Do nothing */
	}

	/************** UART MODE *******************/
	if (UART_MODE_SELECTION == UART_MODE_ASYNCH)
	{
		CLR_BIT(UART_UCSRC,UART_enuUMSEL);

		/* Checking for Double Speed Transmission */
		if (UART_DOUBLE_TX_SPEED == UART_DOUBLE_TX_SPEED_ON)
		{
			SET_BIT(UART_UCSRA,UART_enuU2X);
		}
		else if (UART_DOUBLE_TX_SPEED == UART_DOUBLE_TX_SPEED_OFF)
		{
			/* Do nothing */
			//CLR_BIT(UART_UCSRA,UART_enuU2X);
		}

	}
	else if (UART_MODE_SELECTION == UART_MODE_SYNCH)
	{
		SET_BIT(UART_UCSRC,UART_enuUMSEL);

		/* Writing 0 to U2X Bit */
		CLR_BIT(UART_UCSRA,UART_enuU2X);

		/********** Checking Clock Selection ****************/
		if (USART_CLOCK_SELECTION == USART_enuXCK_RaisingEdge)
		{
			SET_BIT(UART_UCSRC,USART_enuXCK_RaisingEdge);
		}
		else if (USART_CLOCK_SELECTION == USART_enuXCK_FallingEdge)
		{
			CLR_BIT(UART_UCSRC,USART_enuXCK_FallingEdge);
		}
		else
		{
			LocalErrorStatus = USART_enuInvalidClkSelection;
		}
	}
	else
	{
		LocalErrorStatus = UART_enuInvalidUARTMode;
	}

	/************** UART INT ON/OFF ************/
	if (UART_INTERRUPT == UART_INTERRUPT_ON)
	{
		/********** INTERRUPT SOURCE **********/
		/* Checking TX, RX or UDRIE is enabled */
		if (UART_INTERRUPT_CAUSE_1 == TX_INTERRUPT_EN && (UART_TANSMITTER_STATE == TX_ON))
		{
			SET_BIT(UART_UCSRB,UART_enuTXCIE);
		}
		else
		{
			/* Do nothing */
		}
		if (UART_INTERRUPT_CAUSE_2 == RX_INTERRUPT_EN && (UART_TANSMITTER_STATE == RX_ON))
		{
			SET_BIT(UART_UCSRB,UART_enuRXCIE);
		}
		else
		{
			/* Do nothing */
		}
		/* Assigning value inside register */

		if (UART_INTERRUPT_CAUSE_3 == UDRIE_INTERRUPT_EN)
		{
			SET_BIT(UART_UCSRB,UART_enuUDRIE);
		}
		else
		{
			LocalErrorStatus = UART_noNoInterruptSource;
		}
	}
	else if (UART_INTERRUPT == UART_INTERRUPT_OFF)
	{
		LocalErrorStatus = UART_noNoInterruptSource;
	}

	/********** Character Size  **********/
	if (UART_CHARACTER_SIZE == UART_enuCharacter_5Bits)
	{
		CLR_BIT(UART_UCSRC,UART_enuUCSZ0);
		CLR_BIT(UART_UCSRC,UART_enuUCSZ1);
		CLR_BIT(UART_UCSRB,UART_enuUCSZ2);
	}
	else if (UART_CHARACTER_SIZE == UART_enuCharacter_6Bits)
	{
		SET_BIT(UART_UCSRC,UART_enuUCSZ0);
		CLR_BIT(UART_UCSRC,UART_enuUCSZ1);
		CLR_BIT(UART_UCSRB,UART_enuUCSZ2);
	}
	else if (UART_CHARACTER_SIZE == UART_enuCharacter_7Bits)
	{
		CLR_BIT(UART_UCSRC,UART_enuUCSZ0);
		SET_BIT(UART_UCSRC,UART_enuUCSZ1);
		CLR_BIT(UART_UCSRB,UART_enuUCSZ2);
	}
	else if (UART_CHARACTER_SIZE == UART_enuCharacter_8Bits)
	{
		SET_BIT(UART_UCSRC,UART_enuUCSZ0);
		SET_BIT(UART_UCSRC,UART_enuUCSZ1);
		CLR_BIT(UART_UCSRB,UART_enuUCSZ2);
	}
	else if (UART_CHARACTER_SIZE == UART_enuCharacter_9Bits)
	{
		SET_BIT(UART_UCSRC,UART_enuUCSZ0);
		SET_BIT(UART_UCSRC,UART_enuUCSZ1);
		SET_BIT(UART_UCSRB,UART_enuUCSZ2);

		/* Checking the 9th Data bit Source */
		if (UART_9TH_BIT == UART_9TH_BIT_RECIEVED)
		{
			SET_BIT(UART_UCSRB,UART_enuRXB8);
		}
		else if (UART_9TH_BIT == UART_9TH_BIT_TRANSMITTED)
		{
			SET_BIT(UART_UCSRB,UART_enuTXB8);
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		LocalErrorStatus = UART_enuInvalidCharacterSize;
	}

	/* Checking the Register Selection */
	if (UART_REGISTER_SELECTION == UART_REGISTER_UBRRH)
	{
		SET_BIT(UART_UBRRH,UART_enuURSEL);
	}
	else if (UART_REGISTER_SELECTION == UART_REGISTER_UCSRC)
	{
		SET_BIT(UART_UCSRC,UART_enuURSEL_);
	}
	else
	{
		/* Do nothing */
	}

	/* Checking Parity Mode */
	if (UART_PARITY_SELECTION == UART_PARITY_OFF)
	{
		CLR_BIT(UART_UCSRC,UART_enuUPM0);
		CLR_BIT(UART_UCSRC,UART_enuUPM1);
	}
	else if (UART_PARITY_SELECTION == UART_PARITY_EVEN)
	{
		CLR_BIT(UART_UCSRC,UART_enuUPM0);
		SET_BIT(UART_UCSRC,UART_enuUPM1);
	}
	else if (UART_PARITY_SELECTION == UART_PARITY_ODD)
	{
		SET_BIT(UART_UCSRC,UART_enuUPM0);
		SET_BIT(UART_UCSRC,UART_enuUPM1);
	}
	else
	{
		/* Do nothing */
	}

	/* Checking Stop Bits */
	if (UART_STOP_BITS == UART_STOP_BITS_1)
	{
		CLR_BIT(UART_UCSRC,UART_enuUSBS);
	}
	else if (UART_STOP_BITS == UART_STOP_BITS_2)
	{
		SET_BIT(UART_UCSRC,UART_enuUSBS);
	}
	else
	{
		/* Do nothing */
	}

	/* Checking the Baud Rate */
	switch (UART_FREQUENCY)
	{
	case UART_enuFreqOsc_1MHz:
		switch (UART_DOUBLE_TX_SPEED)
		{
		case UART_DOUBLE_TX_SPEED_ON:
			switch (UART_BAUD_RATE)
			{
			case UART_enuBaudRate_2400:
				UART_UBRRL = 51;
				break;
			case UART_enuBaudRate_4800:
				UART_UBRRL = 25;
				break;
			case UART_enuBaudRate_9600:
				UART_UBRRL = 12;
				break;
			case UART_enuBaudRate_14400:
				UART_UBRRL = 8;
				break;
			case UART_enuBaudRate_19200:
				UART_UBRRL = 6;
				break;
			case UART_enuBaudRate_28800:
				UART_UBRRL = 3;
				break;
			case UART_enuBaudRate_38400:
				UART_UBRRL = 2;
				break;
			case UART_enuBaudRate_57600:
				UART_UBRRL = 1;
				break;
			case UART_enuBaudRate_76800:
				UART_UBRRL = 1;
				break;
			case UART_enuBaudRate_115200:
				UART_UBRRL = 0;
				break;
			case UART_enuBaudRate_230400:
				break;
			case UART_enuBaudRate_250000:
				break;
			}
			break;
			case UART_DOUBLE_TX_SPEED_OFF:
				switch (UART_BAUD_RATE)
				{
				case UART_enuBaudRate_2400:
					UART_UBRRL = 25;
					break;
				case UART_enuBaudRate_4800:
					UART_UBRRL = 12;
					break;
				case UART_enuBaudRate_9600:
					UART_UBRRL = 6;
					break;
				case UART_enuBaudRate_14400:
					UART_UBRRL = 3;
					break;
				case UART_enuBaudRate_19200:
					UART_UBRRL = 2;
					break;
				case UART_enuBaudRate_28800:
					UART_UBRRL = 1;
					break;
				case UART_enuBaudRate_38400:
					UART_UBRRL = 1;
					break;
				case UART_enuBaudRate_57600:
					UART_UBRRL = 0;
					break;
				case UART_enuBaudRate_76800:
					break;
				case UART_enuBaudRate_115200:
					break;
				case UART_enuBaudRate_230400:
					break;
				case UART_enuBaudRate_250000:
					break;
				}
				break;
		}
		break;

		case UART_enuFreqOsc_1_84MHZ:
			switch (UART_DOUBLE_TX_SPEED)
			{
			case UART_DOUBLE_TX_SPEED_ON:
				switch (UART_BAUD_RATE)
				{
				case UART_enuBaudRate_2400:
					UART_UBRRL = 95;
					break;
				case UART_enuBaudRate_4800:
					UART_UBRRL = 47;
					break;
				case UART_enuBaudRate_9600:
					UART_UBRRL = 23;
					break;
				case UART_enuBaudRate_14400:
					UART_UBRRL = 15;
					break;
				case UART_enuBaudRate_19200:
					UART_UBRRL = 11;
					break;
				case UART_enuBaudRate_28800:
					UART_UBRRL = 7;
					break;
				case UART_enuBaudRate_38400:
					UART_UBRRL = 5;
					break;
				case UART_enuBaudRate_57600:
					UART_UBRRL = 3;
					break;
				case UART_enuBaudRate_76800:
					UART_UBRRL = 2;
					break;
				case UART_enuBaudRate_115200:
					UART_UBRRL = 1;
					break;
				case UART_enuBaudRate_230400:
					UART_UBRRL = 0;
					break;
				case UART_enuBaudRate_250000:
					break;
				}

				break;
				case UART_DOUBLE_TX_SPEED_OFF:
					switch (UART_BAUD_RATE)
					{
					case UART_enuBaudRate_2400:
						UART_UBRRL = 47;
						break;
					case UART_enuBaudRate_4800:
						UART_UBRRL = 23;
						break;
					case UART_enuBaudRate_9600:
						UART_UBRRL = 11;
						break;
					case UART_enuBaudRate_14400:
						UART_UBRRL = 7;
						break;
					case UART_enuBaudRate_19200:
						UART_UBRRL = 5;
						break;
					case UART_enuBaudRate_28800:
						UART_UBRRL = 3;
						break;
					case UART_enuBaudRate_38400:
						UART_UBRRL = 2;
						break;
					case UART_enuBaudRate_57600:
						UART_UBRRL = 1;
						break;
					case UART_enuBaudRate_76800:
						UART_UBRRL = 1;
						break;
					case UART_enuBaudRate_115200:
						UART_UBRRL = 0;
						break;
					case UART_enuBaudRate_230400:
						break;
					case UART_enuBaudRate_250000:
						break;
					}
					break;
			}
			break;

			case UART_enuFreqOsc_2MHz:
				switch (UART_DOUBLE_TX_SPEED)
				{
				case UART_DOUBLE_TX_SPEED_ON:
					switch (UART_BAUD_RATE)
					{
					case UART_enuBaudRate_2400:
						UART_UBRRL = 103;
						break;
					case UART_enuBaudRate_4800:
						UART_UBRRL = 51;
						break;
					case UART_enuBaudRate_9600:
						UART_UBRRL = 25;
						break;
					case UART_enuBaudRate_14400:
						UART_UBRRL = 16;
						break;
					case UART_enuBaudRate_19200:
						UART_UBRRL = 12;
						break;
					case UART_enuBaudRate_28800:
						UART_UBRRL = 8;
						break;
					case UART_enuBaudRate_38400:
						UART_UBRRL = 6;
						break;
					case UART_enuBaudRate_57600:
						UART_UBRRL = 3;
						break;
					case UART_enuBaudRate_76800:
						UART_UBRRL = 2;
						break;
					case UART_enuBaudRate_115200:
						UART_UBRRL = 1;
						break;
					case UART_enuBaudRate_230400:
						break;
					case UART_enuBaudRate_250000:
						UART_UBRRL = 0;
						break;
					}
					break;
					case UART_DOUBLE_TX_SPEED_OFF:
						switch (UART_BAUD_RATE)
						{
						case UART_enuBaudRate_2400:
							UART_UBRRL = 51;
							break;
						case UART_enuBaudRate_4800:
							UART_UBRRL = 25;
							break;
						case UART_enuBaudRate_9600:
							UART_UBRRL = 12;
							break;
						case UART_enuBaudRate_14400:
							UART_UBRRL = 8;
							break;
						case UART_enuBaudRate_19200:
							UART_UBRRL = 6;
							break;
						case UART_enuBaudRate_28800:
							UART_UBRRL = 3;
							break;
						case UART_enuBaudRate_38400:
							UART_UBRRL = 2;
							break;
						case UART_enuBaudRate_57600:
							UART_UBRRL = 1;
							break;
						case UART_enuBaudRate_76800:
							UART_UBRRL = 1;
							break;
						case UART_enuBaudRate_115200:
							UART_UBRRL = 0;
							break;
						case UART_enuBaudRate_230400:
							break;
						case UART_enuBaudRate_250000:
							break;
						}
						break;
				}
				break;

				case UART_enuFreqOsc_3_6884MHz:
					switch (UART_DOUBLE_TX_SPEED)
					{
					case UART_DOUBLE_TX_SPEED_ON:
						switch (UART_BAUD_RATE)
						{
						case UART_enuBaudRate_2400:
							UART_UBRRL = 191;
							break;
						case UART_enuBaudRate_4800:
							UART_UBRRL = 95;
							break;
						case UART_enuBaudRate_9600:
							UART_UBRRL = 47;
							break;
						case UART_enuBaudRate_14400:
							UART_UBRRL = 31;
							break;
						case UART_enuBaudRate_19200:
							UART_UBRRL = 23;
							break;
						case UART_enuBaudRate_28800:
							UART_UBRRL = 15;
							break;
						case UART_enuBaudRate_38400:
							UART_UBRRL = 11;
							break;
						case UART_enuBaudRate_57600:
							UART_UBRRL = 7;
							break;
						case UART_enuBaudRate_76800:
							UART_UBRRL = 5;
							break;
						case UART_enuBaudRate_115200:
							UART_UBRRL = 3;
							break;
						case UART_enuBaudRate_230400:
							UART_UBRRL = 1;
							break;
						case UART_enuBaudRate_250000:
							UART_UBRRL = 1;
							break;
						}
						break;
						case UART_DOUBLE_TX_SPEED_OFF:
							switch (UART_BAUD_RATE)
							{
							case UART_enuBaudRate_2400:
								UART_UBRRL = 95;
								break;
							case UART_enuBaudRate_4800:
								UART_UBRRL = 47;
								break;
							case UART_enuBaudRate_9600:
								UART_UBRRL = 23;
								break;
							case UART_enuBaudRate_14400:
								UART_UBRRL = 15;
								break;
							case UART_enuBaudRate_19200:
								UART_UBRRL = 11;
								break;
							case UART_enuBaudRate_28800:
								UART_UBRRL = 7;
								break;
							case UART_enuBaudRate_38400:
								UART_UBRRL = 5;
								break;
							case UART_enuBaudRate_57600:
								UART_UBRRL = 3;
								break;
							case UART_enuBaudRate_76800:
								UART_UBRRL = 2;
								break;
							case UART_enuBaudRate_115200:
								UART_UBRRL = 1;
								break;
							case UART_enuBaudRate_230400:
								UART_UBRRL = 0;
								break;
							case UART_enuBaudRate_250000:
								UART_UBRRL = 0;
								break;
							}
							break;
					}
					break;

					case UART_enuFreqOsc_4MHz:
						switch (UART_DOUBLE_TX_SPEED)
						{
						case UART_DOUBLE_TX_SPEED_ON:
							switch (UART_BAUD_RATE)
							{
							case UART_enuBaudRate_2400:
								UART_UBRRL = 207;
								break;
							case UART_enuBaudRate_4800:
								UART_UBRRL = 103;
								break;
							case UART_enuBaudRate_9600:
								UART_UBRRL = 51;
								break;
							case UART_enuBaudRate_14400:
								UART_UBRRL = 34;
								break;
							case UART_enuBaudRate_19200:
								UART_UBRRL = 25;
								break;
							case UART_enuBaudRate_28800:
								UART_UBRRL = 16;
								break;
							case UART_enuBaudRate_38400:
								UART_UBRRL = 12;
								break;
							case UART_enuBaudRate_57600:
								UART_UBRRL = 8;
								break;
							case UART_enuBaudRate_76800:
								UART_UBRRL = 6;
								break;
							case UART_enuBaudRate_115200:
								UART_UBRRL = 3;
								break;
							case UART_enuBaudRate_230400:
								UART_UBRRL = 1;
								break;
							case UART_enuBaudRate_250000:
								UART_UBRRL = 1;
								break;
							}
							break;
							case UART_DOUBLE_TX_SPEED_OFF:
								switch (UART_BAUD_RATE)
								{
								case UART_enuBaudRate_2400:
									UART_UBRRL = 103;
									break;
								case UART_enuBaudRate_4800:
									UART_UBRRL = 51;
									break;
								case UART_enuBaudRate_9600:
									UART_UBRRL = 25;
									break;
								case UART_enuBaudRate_14400:
									UART_UBRRL = 16;
									break;
								case UART_enuBaudRate_19200:
									UART_UBRRL = 12;
									break;
								case UART_enuBaudRate_28800:
									UART_UBRRL = 8;
									break;
								case UART_enuBaudRate_38400:
									UART_UBRRL = 6;
									break;
								case UART_enuBaudRate_57600:
									UART_UBRRL = 3;
									break;
								case UART_enuBaudRate_76800:
									UART_UBRRL = 2;
									break;
								case UART_enuBaudRate_115200:
									UART_UBRRL = 1;
									break;
								case UART_enuBaudRate_230400:
									UART_UBRRL = 0;
									break;
								case UART_enuBaudRate_250000:
									UART_UBRRL = 0;
									break;
								}
								break;
						}
						break;

						case UART_enuFreqOsc_7_3728MHz:
							switch (UART_DOUBLE_TX_SPEED)
							{
							case UART_DOUBLE_TX_SPEED_ON:
								switch (UART_BAUD_RATE)
								{
								case UART_enuBaudRate_2400:
									UART_UBRRL = 127;
									UART_UBRRH = 1;
									break;
								case UART_enuBaudRate_4800:
									UART_UBRRL = 191;
									break;
								case UART_enuBaudRate_9600:
									UART_UBRRL = 95;
									break;
								case UART_enuBaudRate_14400:
									UART_UBRRL = 63;
									break;
								case UART_enuBaudRate_19200:
									UART_UBRRL = 47;
									break;
								case UART_enuBaudRate_28800:
									UART_UBRRL = 31;
									break;
								case UART_enuBaudRate_38400:
									UART_UBRRL = 23;
									break;
								case UART_enuBaudRate_57600:
									UART_UBRRL = 15;
									break;
								case UART_enuBaudRate_76800:
									UART_UBRRL = 11;
									break;
								case UART_enuBaudRate_115200:
									UART_UBRRL = 7;
									break;
								case UART_enuBaudRate_230400:
									UART_UBRRL = 3;
									break;
								case UART_enuBaudRate_250000:
									UART_UBRRL = 3;
									break;
								}
								break;
								case UART_DOUBLE_TX_SPEED_OFF:
									switch (UART_BAUD_RATE)
									{
									case UART_enuBaudRate_2400:
										UART_UBRRL = 191;
										break;
									case UART_enuBaudRate_4800:
										UART_UBRRL = 95;
										break;
									case UART_enuBaudRate_9600:
										UART_UBRRL = 47;
										break;
									case UART_enuBaudRate_14400:
										UART_UBRRL = 31;
										break;
									case UART_enuBaudRate_19200:
										UART_UBRRL = 23;
										break;
									case UART_enuBaudRate_28800:
										UART_UBRRL = 15;
										break;
									case UART_enuBaudRate_38400:
										UART_UBRRL = 11;
										break;
									case UART_enuBaudRate_57600:
										UART_UBRRL = 7;
										break;
									case UART_enuBaudRate_76800:
										UART_UBRRL = 5;
										break;
									case UART_enuBaudRate_115200:
										UART_UBRRL = 3;
										break;
									case UART_enuBaudRate_230400:
										UART_UBRRL = 1;
										break;
									case UART_enuBaudRate_250000:
										UART_UBRRL = 1;
										break;
									}
									break;
							}
							break;

							case UART_enuFreqOsc_8MHz:
								switch (UART_DOUBLE_TX_SPEED)
								{
								case UART_DOUBLE_TX_SPEED_ON:
									switch (UART_BAUD_RATE)
									{
									case UART_enuBaudRate_2400:
										UART_UBRRL = 160;
										UART_UBRRH = 1;
										break;
									case UART_enuBaudRate_4800:
										UART_UBRRL = 207;
										break;
									case UART_enuBaudRate_9600:
										UART_UBRRL = 103;
										break;
									case UART_enuBaudRate_14400:
										UART_UBRRL = 68;
										break;
									case UART_enuBaudRate_19200:
										UART_UBRRL = 51;
										break;
									case UART_enuBaudRate_28800:
										UART_UBRRL = 34;
										break;
									case UART_enuBaudRate_38400:
										UART_UBRRL = 25;
										break;
									case UART_enuBaudRate_57600:
										UART_UBRRL = 16;
										break;
									case UART_enuBaudRate_76800:
										UART_UBRRL = 12;
										break;
									case UART_enuBaudRate_115200:
										UART_UBRRL = 8;
										break;
									case UART_enuBaudRate_230400:
										UART_UBRRL = 3;
										break;
									case UART_enuBaudRate_250000:
										UART_UBRRL = 3;
										break;
									}
									break;
									case UART_DOUBLE_TX_SPEED_OFF:
										switch (UART_BAUD_RATE)
										{
										case UART_enuBaudRate_2400:
											UART_UBRRL = 207;
											break;
										case UART_enuBaudRate_4800:
											UART_UBRRL = 103;
											break;
										case UART_enuBaudRate_9600:
											UART_UBRRL = 51;
											break;
										case UART_enuBaudRate_14400:
											UART_UBRRL = 34;
											break;
										case UART_enuBaudRate_19200:
											UART_UBRRL = 25;
											break;
										case UART_enuBaudRate_28800:
											UART_UBRRL = 16;
											break;
										case UART_enuBaudRate_38400:
											UART_UBRRL = 12;
											break;
										case UART_enuBaudRate_57600:
											UART_UBRRL = 8;
											break;
										case UART_enuBaudRate_76800:
											UART_UBRRL = 6;
											break;
										case UART_enuBaudRate_115200:
											UART_UBRRL = 3;
											break;
										case UART_enuBaudRate_230400:
											UART_UBRRL = 1;
											break;
										case UART_enuBaudRate_250000:
											UART_UBRRL = 1;
											break;
										}
										break;
								}
								break;

								case UART_enuFreqOsc_11_0592MHz:
									switch (UART_DOUBLE_TX_SPEED)
									{
									case UART_DOUBLE_TX_SPEED_ON:
										switch (UART_BAUD_RATE)
										{
										case UART_enuBaudRate_2400:
											UART_UBRRL = 63;
											UART_UBRRH = 2;
											break;
										case UART_enuBaudRate_4800:
											UART_UBRRL = 31;
											UART_UBRRH = 1;
											break;
										case UART_enuBaudRate_9600:
											UART_UBRRL = 143;
											break;
										case UART_enuBaudRate_14400:
											UART_UBRRL = 95;
											break;
										case UART_enuBaudRate_19200:
											UART_UBRRL = 71;
											break;
										case UART_enuBaudRate_28800:
											UART_UBRRL = 47;
											break;
										case UART_enuBaudRate_38400:
											UART_UBRRL = 35;
											break;
										case UART_enuBaudRate_57600:
											UART_UBRRL = 23;
											break;
										case UART_enuBaudRate_76800:
											UART_UBRRL = 17;
											break;
										case UART_enuBaudRate_115200:
											UART_UBRRL = 11;
											break;
										case UART_enuBaudRate_230400:
											UART_UBRRL = 5;
											break;
										case UART_enuBaudRate_250000:
											UART_UBRRL = 5;
											break;
										}
										break;
										case UART_DOUBLE_TX_SPEED_OFF:
											switch (UART_BAUD_RATE)
											{
											case UART_enuBaudRate_2400:
												UART_UBRRL = 31;
												UART_UBRRH = 1;
												break;
											case UART_enuBaudRate_4800:
												UART_UBRRL = 143;
												break;
											case UART_enuBaudRate_9600:
												UART_UBRRL = 71;
												break;
											case UART_enuBaudRate_14400:
												UART_UBRRL = 47;
												break;
											case UART_enuBaudRate_19200:
												UART_UBRRL = 35;
												break;
											case UART_enuBaudRate_28800:
												UART_UBRRL = 23;
												break;
											case UART_enuBaudRate_38400:
												UART_UBRRL = 17;
												break;
											case UART_enuBaudRate_57600:
												UART_UBRRL = 11;
												break;
											case UART_enuBaudRate_76800:
												UART_UBRRL = 8;
												break;
											case UART_enuBaudRate_115200:
												UART_UBRRL = 5;
												break;
											case UART_enuBaudRate_230400:
												UART_UBRRL = 2;
												break;
											case UART_enuBaudRate_250000:
												UART_UBRRL = 2;
												break;
											}
											break;
									}
									break;

									case UART_enuFreqOsc_14_7456MHz:
										switch (UART_DOUBLE_TX_SPEED)
										{
										case UART_DOUBLE_TX_SPEED_ON:
											switch (UART_BAUD_RATE)
											{
											case UART_enuBaudRate_2400:
												UART_UBRRL = 255;
												UART_UBRRH = 2;
												break;
											case UART_enuBaudRate_4800:
												UART_UBRRL = 127;
												UART_UBRRH = 1;
												break;
											case UART_enuBaudRate_9600:
												UART_UBRRL = 191;
												break;
											case UART_enuBaudRate_14400:
												UART_UBRRL = 127;
												break;
											case UART_enuBaudRate_19200:
												UART_UBRRL = 95;
												break;
											case UART_enuBaudRate_28800:
												UART_UBRRL = 63;
												break;
											case UART_enuBaudRate_38400:
												UART_UBRRL = 47;
												break;
											case UART_enuBaudRate_57600:
												UART_UBRRL = 31;
												break;
											case UART_enuBaudRate_76800:
												UART_UBRRL = 23;
												break;
											case UART_enuBaudRate_115200:
												UART_UBRRL = 15;
												break;
											case UART_enuBaudRate_230400:
												UART_UBRRL = 7;
												break;
											case UART_enuBaudRate_250000:
												UART_UBRRL = 6;
												break;
											}
											break;
											case UART_DOUBLE_TX_SPEED_OFF:
												switch (UART_BAUD_RATE)
												{
												case UART_enuBaudRate_2400:
													UART_UBRRL = 127;
													UART_UBRRH = 1;
													break;
												case UART_enuBaudRate_4800:
													UART_UBRRL = 191;
													break;
												case UART_enuBaudRate_9600:
													UART_UBRRL = 95;
													break;
												case UART_enuBaudRate_14400:
													UART_UBRRL = 63;
													break;
												case UART_enuBaudRate_19200:
													UART_UBRRL = 47;
													break;
												case UART_enuBaudRate_28800:
													UART_UBRRL = 31;
													break;
												case UART_enuBaudRate_38400:
													UART_UBRRL = 23;
													break;
												case UART_enuBaudRate_57600:
													UART_UBRRL = 15;
													break;
												case UART_enuBaudRate_76800:
													UART_UBRRL = 11;
													break;
												case UART_enuBaudRate_115200:
													UART_UBRRL = 7;
													break;
												case UART_enuBaudRate_230400:
													UART_UBRRL = 3;
													break;
												case UART_enuBaudRate_250000:
													UART_UBRRL = 3;
													break;
												}
												break;
										}
										break;

										case UART_enuFreqOsc_16MHz:
											switch (UART_DOUBLE_TX_SPEED)
											{
											case UART_DOUBLE_TX_SPEED_ON:
												switch (UART_BAUD_RATE)
												{
												case UART_enuBaudRate_2400:
													UART_UBRRL = 64;
													UART_UBRRH = 3;
													break;
												case UART_enuBaudRate_4800:
													UART_UBRRL = 160;
													UART_UBRRH = 1;
													break;
												case UART_enuBaudRate_9600:
													UART_UBRRL = 207;
													break;
												case UART_enuBaudRate_14400:
													UART_UBRRL = 138;
													break;
												case UART_enuBaudRate_19200:
													UART_UBRRL = 103;
													break;
												case UART_enuBaudRate_28800:
													UART_UBRRL = 68;
													break;
												case UART_enuBaudRate_38400:
													UART_UBRRL = 51;
													break;
												case UART_enuBaudRate_57600:
													UART_UBRRL = 34;
													break;
												case UART_enuBaudRate_76800:
													UART_UBRRL = 25;
													break;
												case UART_enuBaudRate_115200:
													UART_UBRRL = 16;
													break;
												case UART_enuBaudRate_230400:
													UART_UBRRL = 8;
													break;
												case UART_enuBaudRate_250000:
													UART_UBRRL = 7;
													break;
												}
												break;
												case UART_DOUBLE_TX_SPEED_OFF:
													switch (UART_BAUD_RATE)
													{
													case UART_enuBaudRate_2400:
														UART_UBRRL = 160;
														UART_UBRRH = 1;
														break;
													case UART_enuBaudRate_4800:
														UART_UBRRL = 207;
														break;
													case UART_enuBaudRate_9600:
														UART_UBRRL = 103;
														break;
													case UART_enuBaudRate_14400:
														UART_UBRRL = 68;
														break;
													case UART_enuBaudRate_19200:
														UART_UBRRL = 51;
														break;
													case UART_enuBaudRate_28800:
														UART_UBRRL = 34;
														break;
													case UART_enuBaudRate_38400:
														UART_UBRRL = 25;
														break;
													case UART_enuBaudRate_57600:
														UART_UBRRL = 16;
														break;
													case UART_enuBaudRate_76800:
														UART_UBRRL = 12;
														break;
													case UART_enuBaudRate_115200:
														UART_UBRRL = 8;
														break;
													case UART_enuBaudRate_230400:
														UART_UBRRL = 3;
														break;
													case UART_enuBaudRate_250000:
														UART_UBRRL = 3;
														break;
													}
													break;
											}
											break;

											case UART_enuFreqOsc_18_4320MHz:
												switch (UART_DOUBLE_TX_SPEED)
												{
												case UART_DOUBLE_TX_SPEED_ON:
													switch (UART_BAUD_RATE)
													{
													case UART_enuBaudRate_2400:
														UART_UBRRL = 191;
														UART_UBRRH = 3;
														break;
													case UART_enuBaudRate_4800:
														UART_UBRRL = 223;
														UART_UBRRH = 1;
														break;
													case UART_enuBaudRate_9600:
														UART_UBRRL = 239;
														break;
													case UART_enuBaudRate_14400:
														UART_UBRRL = 159;
														break;
													case UART_enuBaudRate_19200:
														UART_UBRRL = 119;
														break;
													case UART_enuBaudRate_28800:
														UART_UBRRL = 79;
														break;
													case UART_enuBaudRate_38400:
														UART_UBRRL = 59;
														break;
													case UART_enuBaudRate_57600:
														UART_UBRRL = 39;
														break;
													case UART_enuBaudRate_76800:
														UART_UBRRL = 29;
														break;
													case UART_enuBaudRate_115200:
														UART_UBRRL = 19;
														break;
													case UART_enuBaudRate_230400:
														UART_UBRRL = 9;
														break;
													case UART_enuBaudRate_250000:
														UART_UBRRL = 8;
														break;
													}
													break;
													case UART_DOUBLE_TX_SPEED_OFF:
														switch (UART_BAUD_RATE)
														{
														case UART_enuBaudRate_2400:
															UART_UBRRL = 223;
															UART_UBRRH = 1;
															break;
														case UART_enuBaudRate_4800:
															UART_UBRRL = 239;
															break;
														case UART_enuBaudRate_9600:
															UART_UBRRL = 119;
															break;
														case UART_enuBaudRate_14400:
															UART_UBRRL = 79;
															break;
														case UART_enuBaudRate_19200:
															UART_UBRRL = 59;
															break;
														case UART_enuBaudRate_28800:
															UART_UBRRL = 39;
															break;
														case UART_enuBaudRate_38400:
															UART_UBRRL = 29;
															break;
														case UART_enuBaudRate_57600:
															UART_UBRRL = 19;
															break;
														case UART_enuBaudRate_76800:
															UART_UBRRL = 14;
															break;
														case UART_enuBaudRate_115200:
															UART_UBRRL = 9;
															break;
														case UART_enuBaudRate_230400:
															UART_UBRRL = 4;
															break;
														case UART_enuBaudRate_250000:
															UART_UBRRL = 4;
															break;
														}
														break;
												}
												break;

												case UART_enuFreqOsc_20MHz:
													switch (UART_DOUBLE_TX_SPEED)
													{
													case UART_DOUBLE_TX_SPEED_ON:
														switch (UART_BAUD_RATE)
														{
														case UART_enuBaudRate_2400:
															UART_UBRRL = 17;
															UART_UBRRH = 4;
															break;
														case UART_enuBaudRate_4800:
															UART_UBRRL = 8;
															UART_UBRRH = 2;
															break;
														case UART_enuBaudRate_9600:
															UART_UBRRL = 3;
															UART_UBRRH = 1;
															break;
														case UART_enuBaudRate_14400:
															UART_UBRRL = 173;
															break;
														case UART_enuBaudRate_19200:
															UART_UBRRL = 129;
															break;
														case UART_enuBaudRate_28800:
															UART_UBRRL = 86;
															break;
														case UART_enuBaudRate_38400:
															UART_UBRRL = 64;
															break;
														case UART_enuBaudRate_57600:
															UART_UBRRL = 42;
															break;
														case UART_enuBaudRate_76800:
															UART_UBRRL = 32;
															break;
														case UART_enuBaudRate_115200:
															UART_UBRRL = 21;
															break;
														case UART_enuBaudRate_230400:
															UART_UBRRL = 10;
															break;
														case UART_enuBaudRate_250000:
															UART_UBRRL = 9;
															break;
														}
														break;
														case UART_DOUBLE_TX_SPEED_OFF:
															switch (UART_BAUD_RATE)
															{
															case UART_enuBaudRate_2400:
																UART_UBRRL = 8;
																UART_UBRRH = 2;
																break;
															case UART_enuBaudRate_4800:
																UART_UBRRL = 3;
																UART_UBRRH = 1;
																break;
															case UART_enuBaudRate_9600:
																UART_UBRRL = 129;
																break;
															case UART_enuBaudRate_14400:
																UART_UBRRL = 86;
																break;
															case UART_enuBaudRate_19200:
																UART_UBRRL = 64;
																break;
															case UART_enuBaudRate_28800:
																UART_UBRRL = 42;
																break;
															case UART_enuBaudRate_38400:
																UART_UBRRL = 32;
																break;
															case UART_enuBaudRate_57600:
																UART_UBRRL = 21;
																break;
															case UART_enuBaudRate_76800:
																UART_UBRRL = 15;
																break;
															case UART_enuBaudRate_115200:
																UART_UBRRL = 10;
																break;
															case UART_enuBaudRate_230400:
																UART_UBRRL = 4;
																break;
															case UART_enuBaudRate_250000:
																UART_UBRRL = 4;
																break;
															}
															break;
													}
													break;
	}

	return LocalErrorStatus;
}
/*****************************************************************************/
UART_tenuErrorStatus UART_enuNotConfigInit (void)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	u8 LocalUCSRC_Buffer = 0;

	/***************** Making UART Asych ************/
	// By default

	/*************** Character Size : 8 ******************/
	SET_BIT(LocalUCSRC_Buffer,UART_enuUCSZ0);
	SET_BIT(LocalUCSRC_Buffer,UART_enuUCSZ1);

	/**************** Accessing UCSRC ****************/
	SET_BIT(LocalUCSRC_Buffer,UART_enuURSEL_);

	/**************** Making NO Bits for Parity *********/
	// By default

	/**************** STOP Bits = 1 ******************/
	// By default

	/**************** Assigning Local var into UCSRC **********/
	UART_UCSRC = LocalUCSRC_Buffer;

	/***************** Baud rate = 9600b/s ****************/
	UART_UBRRL = 51;

	/************** RX & TX Enable *****************/
	SET_BIT(UART_UCSRB,UART_enuRXEN);
	SET_BIT(UART_UCSRB,UART_enuTXEN);

	return LocalErrorStatus;
}
/*****************************************************************************/
UART_tenuErrorStatus UART_enuSendAsynchByte (u8 Cpy_u8Data)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	u8 LocalTC_Complete = GET_BIT(UART_UCSRA,UART_enuTXC);

	/* Checking that Data Received Completely */
	if ((LocalTC_Complete == 1) && (UART_INTERRUPT_CAUSE_2 == TX_INTERRUPT_EN))
	{
		GlobalByteTX = Cpy_u8Data;
	}
	else
	{
		LocalErrorStatus = UART_enuByteNotReceived;
	}

	return LocalErrorStatus;

}
/*****************************************************************************/
UART_tenuErrorStatus UART_enuSendSynchByte (u8 Cpy_u8Data)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	u8 LocalCounter = 0;
	u8 TIMEOUT	= 255;

	u8 LocalTC_Complete = GET_BIT(UART_UCSRA,UART_enuTXC);

	while ((LocalTC_Complete == 0) && (LocalCounter < TIMEOUT))
	{
		TIMEOUT --;
	}
	if (TIMEOUT)
	{
		UART_UDR = Cpy_u8Data;
	}
	else
	{
		LocalErrorStatus = UART_enuTIMEOUT;
	}

	return LocalErrorStatus;
}
/*****************************************************************************/
UART_tenuErrorStatus UART_enuRecieveAsynchByte (u8 *Cpy_Addu8Data)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;
	u8 LocalCounter =0;
	u8 TIMEOUT	= 255;

	u8 LocalRX_Complete = GET_BIT(UART_UCSRA,UART_enuRXC);

	u8 LocalRX_FrameError = GET_BIT(UART_UCSRA,UART_enuFE);
	u8 LocalRX_Overrun = GET_BIT(UART_UCSRA,UART_enuDOR);
	u8 LocalRX_ParityError = GET_BIT(UART_UCSRA, UART_enuPE);

	/*********** Waiting until data is received : POLLING ******************/
	while ((LocalRX_Complete == 0) && (TIMEOUT > LocalCounter))
	{
		TIMEOUT--;
	}

	/* Checking that Data Received Completely */
	if ((LocalRX_Complete == 1) && (UART_INTERRUPT_CAUSE_1 == RX_INTERRUPT_EN))
	{
		if (Cpy_Addu8Data != NULL_PTR)
		{
			Global_AddvarRX = Cpy_Addu8Data ;
		}
	}

	/* Checking for errors that can occur while recieving */
	else if (LocalRX_FrameError == 1)
	{
		LocalErrorStatus = UART_enuRXFrameError;
	}
	else if (LocalRX_Overrun == 1)
	{
		LocalErrorStatus = UART_enuRXDataOverrun;
	}
	else if (LocalRX_ParityError == 1)
	{
		LocalErrorStatus = UART_enuParityError;
	}
	else
	{
		LocalErrorStatus = UART_enuByteNotReceived;
	}

	return LocalErrorStatus;
}
/*****************************************************************************/
UART_tenuErrorStatus UART_enuRecieveSynchByte (u8 *Cpy_Addu8Data)
{
	UART_tenuErrorStatus LocalErrorStatus = UART_enuOK;

	u8 LocalRX_Complete = GET_BIT(UART_UCSRA,UART_enuRXC);

	u8 LocalCounter = 0;
	u8 TIMEOUT	= 255;

	if (Cpy_Addu8Data != NULL_PTR)
	{
		while ((LocalRX_Complete == 0) && (LocalCounter< TIMEOUT))
		{
			TIMEOUT --;
		}

		if (TIMEOUT)
		{
			*Cpy_Addu8Data = UART_UDR;
		}
		else
		{
			LocalErrorStatus = UART_enuTIMEOUT;
		}
	}
	else
	{
		LocalErrorStatus = UART_enuNULL_PTR;
	}

	return LocalErrorStatus;
}
/*****************************************************************************/
/*****************************************************************************/
u8 UART_u8RecieveData (void)
{
	u8 LocalRX_Complete = GET_BIT(UART_UCSRA,UART_enuRXC);

	/* Polling */
	while (LocalRX_Complete == 0);

	return UART_UDR;
}
/*****************************************************************************/
void UART_voidSendData (u8 Cpy_u8Data)
{
	/* Checking Data Transmit buffer : MUST BE EMPTY */
	u8 LocalTX_UDRE = GET_BIT(UART_UCSRA,UART_enuUDRE);

	/* Polling */
	while (LocalTX_UDRE == 0);

	UART_UDR = Cpy_u8Data;
}


/* ================================= ISRs ========================================= */
/* ================================================================================ */

ISR_RX_Complete(ISR_RX)
{
	if (Global_AddvarRX != NULL_PTR)
	{
		*Global_AddvarRX = UART_UDR;
	}
	else
	{
		/* Do nothing */
	}
}
/*****************************************************************************/
ISR_UDRE_Empty(ISR_UDRE)
{

}
/*****************************************************************************/

ISR_TX_Complete(ISR_TX)
{
	UART_UDR = GlobalByteTX;
}
/*****************************************************************************/
