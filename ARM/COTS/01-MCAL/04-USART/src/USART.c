/*
 * UART.c
 *
 *  Created on: Apr 6, 2023
 *      Author: Doaa Maher
 */
#include "NVIC.h"

#include "USART_Interface.h"
#include "USART_Config.h"

/* ====================== Defines ============================== */
#define				F_CPU				(16000000UL)
/* ============================ Types ====================== */
// USART Registers
typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
}USART_tstr_Registers_t;

// Array of 3 Peripherals sharing same type : same registers [on APB1 bus]
USART_tstr_Registers_t * const volatile USART[3] =
{
		/* USART1 */ [USART1] = (( USART_tstr_Registers_t* ) 0x40011000),
		/* USART2 */ [USART2] = (( USART_tstr_Registers_t* ) 0x40004400),
		/* USART6 */ [USART6] = (( USART_tstr_Registers_t* ) 0x40114000),
};

/* ================= Static Global Vars for TX ================= */
// For TX States for the 3 USARTs : Initially not initialized
static u8 TX_State[3] = {NOT_INIT,NOT_INIT,NOT_INIT};
// For TX Buffer to be Sent [array of pointers] // 2D Array
static u8 *TX_Buffer[3] = {NULL_PTR,NULL_PTR,NULL_PTR};
// For TX Size for the 3 USARTs
static u32 TX_Size[3] = {0,0,0};
// For TX Indicies
static u32 TX_Index[3] = {0,0,0};

/* Callback function */
static Callback_t TX_Cbf[3] = {NULL_PTR,NULL_PTR,NULL_PTR};
/* ============================================================= */
/* ================= Static Global Vars for RX ================= */
// For RX States for the 3 USARTs : Initially not initialized
static u8 RX_State[3] = {NOT_INIT,NOT_INIT,NOT_INIT};
// For RX Buffer to be Received [array of pointers] // 2D Array
static u8 *RX_Buffer[3] = {NULL_PTR,NULL_PTR,NULL_PTR};
// For RX Size for the 3 USARTs
static u32 RX_Size[3] = {0,0,0};
// For RX Indicies
static u32 RX_Index[3] = {0,0,0};

/* Callback Function */
static Callback_t RX_Cbf[3] = {NULL_PTR,NULL_PTR,NULL_PTR};
/* ============================================================= */
/* ==================== Static Functions Prototypes ============== */
static void USART_voidBaudRate_USART_Calculation (USART_tstrConfig_t * USART_Cfg);
static void USART_voidHandler (USART_enuChannels USART_Channel);
/* =============================================================== */
/* ====================== Global Variables ========================= */
static u8 USART_USED=0;

/* ========================= APIs Implementation ============================ */
static void USART_voidBaudRate_USART_Calculation (USART_tstrConfig_t * USART_Cfg)
{
	/* 								 fClk
	 * TX/RX Baud Rate = ---------------------------------
	 * 						  8 x (2-OVER8) * USARTDIV
	 */

	f32 USARTDIV = 0;			// Has value in BRR

	u32 Mantissa_Part =0;
	u32 Fraction_Part =0;
	u8  Over8_Bit =0;

	u32 LocalTempOverSampling = USART_Cfg->USART_OverSampling;

	// Checking OVER8 Condition to know the fractional part bits (3 or 4)
	if (LocalTempOverSampling == USART_enuOverSampling_DIV_16)			// = 0
	{
		Over8_Bit = 0;
		// Fractional part is coded on 4-bits
	}
	else if (LocalTempOverSampling == USART_enuOverSampling_DIV_8)		// = 1
	{
		Over8_Bit =1;
		// Fractional part is coded on 3-bits
		// DIV_FractionBit3 must be cleared.
		//		LocalBuffer = USART[USART_USED]->USART_BRR;

		//		LocalBuffer &= USART_BRR_DIV_FRACTION_BIT3_CLR;
	}

	// Calculating USARTDIV Value & Cast it to f32:
	USARTDIV = ((f32)(F_CPU)) / (f32)((USART_Cfg->USART_BaudRate*8*(2-Over8_Bit)));

	// Assign the Mantissa Part : By Casting USARTDIV to u32
	Mantissa_Part = (u32)USARTDIV;

	// Assign the Fraction Part : By Subtracting (USARTDIV - Mantissa)
	// Checking the OverSampling was 16 or 8
	switch (LocalTempOverSampling)
	{
	case USART_enuOverSampling_DIV_16:
	{
		Fraction_Part = (USARTDIV - Mantissa_Part) * 16;
	}
	break;

	case USART_enuOverSampling_DIV_8:
	{
		Fraction_Part = (USARTDIV - Mantissa_Part) * 8;
	}
	break;
	}

	// Finally, Assign the Mantissa & Fraction To BRR Register
	// Clearing the Register
	USART[USART_Cfg->USART_Channel]->USART_BRR |= ((Fraction_Part & 0x0F) | (Mantissa_Part << 4));
}
/************************************************************************************/
/* Before Transmitting the byte */
static void USART_voidHandler (USART_enuChannels USART_Channel)
{
	/* ========================= Transmission =============================== */
	// First, Check for TX State if it was Busy [Sending]
	if (TX_State[USART_Channel] == BUSY)
	{
		// Checking if transmission is completed
		if ((USART[USART_Channel]->USART_SR >> USART_enuTC) & 1)
		{
			// Check if the Index of TX was less than the TX Size
			if (TX_Index[USART_Channel] < TX_Size[USART_Channel])
			{
				/************* Data Transmission is happening ***************/
				// Move the Data from the Buffer "with the index" into the DR register
				USART[USART_Channel]->USART_DR = TX_Buffer[USART_Channel][TX_Index[USART_Channel]];
				// Increment Index Array
				TX_Index[USART_Channel]++;
			}
			else //if (TX_Index[USART_Channel] > TX_Size[USART_Channel])
			{
				/************ Transmission is done *************/
				// Make State to be IDLE
				TX_State[USART_Channel] = IDLE;
				// Clear the Transmission Interrupt Flag
				USART[USART_Channel]->USART_CR1 &= USART_CR1_TCIE_DS;
				// Check the TX Callback function
				if (TX_Cbf[USART_Channel])
				{
					// Call it
					TX_Cbf[USART_Channel]();
				}
			}
		}
	}


	/* ========================= Reception =============================== */
	// First, Check for TX State if it was Busy [Sending]
	if ((RX_State[USART_Channel] == BUSY) && ((USART[USART_Channel]->USART_SR >> USART_enuRXNE)&1))
	{
		// Check if the Index of RX was less than the RX Size
		if (RX_Index[USART_Channel] < RX_Size[USART_Channel])
		{
			/************* Data Reception is happening ***************/
			// Move the Data from the DR register "with the index" into the RX Buffer
			RX_Buffer[USART_Channel][RX_Index[USART_Channel]] = (u8)USART[USART_Channel]->USART_DR;
			// Increment Index Array
			RX_Index[USART_Channel]++;
		}
		if (RX_Index[USART_Channel] == RX_Size[USART_Channel])
		{
			/************ Reception is done *************/
			// Make State to be IDLE
			RX_State[USART_Channel] = IDLE;
			// Clear the Receive Interrupt Flag
			USART[USART_Channel]->USART_CR1 &= USART_CR1_RXNEIE_DS;
			// Check the RX Callback function
			if (RX_Cbf[USART_Channel])
			{
				// Call it
				RX_Cbf[USART_Channel]();
			}
		}
	}
}
/************************************************************************************/
USART_tenuErrorStatus USART_enuInit(USART_tstrConfig_t * USART_Cfg)
{
	USART_tenuErrorStatus LocalErrorStatus = USART_enuOK;

	u32 LocalBuffer = 0;

	/* =========================== Setting AF ============================ */
	/* Setting Alternate Function with the Channel Number */
	/* USART1 & USART2 on AF : 7
	 * USART6		   on AF : 8
	 * ===================================================================== */

	if ( (USART_Cfg->USART_Channel == USART_enuUSART1) || (USART_Cfg->USART_Channel == USART_enuUSART2))
	{
		// Set the Alternate Function : 7 For TX and RX Ports/Pins
		GPIO_enuSetAlternateFunction(USART_Cfg->USART_Pins.USART_TX.GPIO_Port, USART_Cfg->USART_Pins.USART_TX.GPIO_Pin,GPIO_enu_AF_7);
		GPIO_enuSetAlternateFunction(USART_Cfg->USART_Pins.USART_RX.GPIO_Port, USART_Cfg->USART_Pins.USART_RX.GPIO_Pin,GPIO_enu_AF_7);
	}

	else if (USART_Cfg->USART_Channel == USART_enuUSART6)
	{
		// Set the Alternate Function : 8 For TX and RX Ports/Pins
		GPIO_enuSetAlternateFunction(USART_Cfg->USART_Pins.USART_TX.GPIO_Port, USART_Cfg->USART_Pins.USART_TX.GPIO_Pin,GPIO_enu_AF_8);
		GPIO_enuSetAlternateFunction(USART_Cfg->USART_Pins.USART_RX.GPIO_Port, USART_Cfg->USART_Pins.USART_RX.GPIO_Pin,GPIO_enu_AF_8);
	}

	// Initialize TX,RX Pins at GPIO_Init
	GPIO_enuInit(&USART_Cfg->USART_Pins.USART_TX);
	GPIO_enuInit(&USART_Cfg->USART_Pins.USART_RX);

	/* Enable TX & RX from the Config file */
	USART[USART_Cfg->USART_Channel]->USART_CR1 |= USART_CR1_TE_SET;
	USART[USART_Cfg->USART_Channel]->USART_CR1 |= USART_CR1_RE_SET;

	/* User Configurations */

	// Data Length
	LocalBuffer = USART[USART_Cfg->USART_Channel]->USART_CR1;
	LocalBuffer &= USART_CR1_DATABITS_CLR;
	LocalBuffer |= USART_Cfg->USART_DataBits;
	USART[USART_Cfg->USART_Channel]->USART_CR1 = LocalBuffer;

	// Parity Control
	LocalBuffer = USART[USART_Cfg->USART_Channel]->USART_CR1;
	LocalBuffer &= USART_CR1_PS_CLR;
	LocalBuffer |= USART_Cfg->USART_ParityControl;
	USART[USART_Cfg->USART_Channel]->USART_CR1 = LocalBuffer;

	// Parity Type
	LocalBuffer = USART[USART_Cfg->USART_Channel]->USART_CR1;
	LocalBuffer &= USART_CR1_DS;
	LocalBuffer |= USART_Cfg->USART_ParityType;
	USART[USART_Cfg->USART_Channel]->USART_CR1 = LocalBuffer;

	// Stop bits
	LocalBuffer = USART[USART_Cfg->USART_Channel]->USART_CR2;
	LocalBuffer &= USART_STOP_CLR_MASK;
	LocalBuffer |= USART_Cfg->USART_StopBits;
	USART[USART_Cfg->USART_Channel]->USART_CR2 = LocalBuffer;

	// Over Sampling
	LocalBuffer = USART[USART_Cfg->USART_Channel]->USART_CR1;
	LocalBuffer &= USART_CR1_OVERSAMPLE_DIV_16;
	LocalBuffer |= USART_Cfg->USART_StopBits;
	USART[USART_Cfg->USART_Channel]->USART_CR1 = LocalBuffer;

	// BaudRate
	USART_voidBaudRate_USART_Calculation(USART_Cfg);

	/* Enable USART */
	USART[USART_Cfg->USART_Channel]->USART_CR1 |= USART_CR1_EN;

	/* Enable TX & RX Interrupts from NVIC */
	NVIC_enuEnableIRQ(NVIC_VECTOR_USART1);

	/* ========================== States =========================== */
	// Make TX,RX States to be IDLE
	TX_State[USART_Cfg->USART_Channel] = IDLE;
	RX_State[USART_Cfg->USART_Channel] = IDLE;

	/* Testing */
	USART[USART_Cfg->USART_Channel]->USART_SR = 0;

	return LocalErrorStatus;
}
/************************************************************************************/
USART_tenuErrorStatus USART_enuSendAsynchZeroCpy (USART_enuChannels USART_Channel, u8 * Data_Buffer, u32 Data_Size , Callback_t Cpy_Cbf)
{
	USART_tenuErrorStatus LocalErrorStatus = USART_enuOK;

	// Checking TX State , if IDLE => It's Ready to Send
	if (TX_State[USART_Channel] == IDLE)
	{
		TX_State[USART_Channel]  = BUSY;

		TX_Buffer[USART_Channel] = Data_Buffer;
		TX_Size[USART_Channel]   = Data_Size;
		TX_Index[USART_Channel]  = 0;
		TX_Cbf[USART_Channel]    = Cpy_Cbf;

		// Send the Data from the Buffer into the DR
		USART[USART_Channel]->USART_DR = TX_Buffer[USART_Channel][TX_Index[USART_Channel]];
		// Enable TXC Interrupt
		USART[USART_Channel]->USART_CR1 |= USART_CR1_TCIE_EN;
		// Increment TX index
		TX_Index[USART_Channel]++;
	}
	else
	{
		LocalErrorStatus = USART_enuBUSY;
	}
	return LocalErrorStatus;
}
/************************************************************************************/
USART_tenuErrorStatus USART_enuReceiveAsynchZeroCpy (USART_enuChannels USART_Channel, u8 * Received_Buffer, u32 Data_Size , Callback_t Cpy_Cbf)
{
	USART_tenuErrorStatus LocalErrorStatus = USART_enuOK;

	// Checking RX State , if IDLE => It's Ready to Receive
	if (RX_State[USART_Channel] == IDLE)
	{
		RX_State[USART_Channel]  = BUSY;

		RX_Buffer[USART_Channel] = Received_Buffer;
		RX_Size[USART_Channel]   = Data_Size;
		RX_Index[USART_Channel]  = 0;
		RX_Cbf[USART_Channel]    = Cpy_Cbf;

		// Enable RXC Interrupt
		USART[USART_Channel]->USART_CR1 |= USART_CR1_RXNEIE_EN;
	}
	else
	{
		LocalErrorStatus = USART_enuBUSY;
	}

	return LocalErrorStatus;
}
/************************************************************************************/
u8 USART_u8GetCurrentStatus (void)
{
	return RX_State[0];
}
/************************************************************************************/
/* =========================== Handlers ====================================== */
void USART1_IRQHandler (void)
{
	USART_voidHandler(USART_enuUSART1);
}
/************************************************************************************/
void USART2_IRQHandler (void)
{
	USART_voidHandler(USART_enuUSART2);
}
/************************************************************************************/
void USART6_IRQHandler (void)
{
	USART_voidHandler(USART_enuUSART6);
}
/************************************************************************************/
