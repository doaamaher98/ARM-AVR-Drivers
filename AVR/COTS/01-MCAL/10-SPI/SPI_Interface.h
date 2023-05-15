/*
 * SPI_Interface.h
 *
 *  Created on: Apr 1, 2023
 *      Author: engdo
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "../00-LIB/Std_Types.h"

/* ==================== Pre-Processor ===================== */
#define				SPI_DS					0
#define				SPI_EN					1

#define				SPI_INTERRUPT_DS		0
#define				SPI_INTERRUPT_EN		1

#define				SPI_DATA_ORDER_LSB		0
#define				SPI_DATA_ORDER_MSB		1

#define				SPI_MCU_SLAVE			0
#define				SPI_MCU_MASTER			1

#define				SPI_POLARITY_LOW		0
#define				SPI_POLARITY_HIGH		1

#define				SPI_DATA_SAMPLED_FIRST	0
#define				SPI_DATA_SETUP_FIRST	1

#define				SPI_INTERRUPT			12
// ISR
#define				SPI_ISR(SPI_INTERRUPT)		void __vector_##SPI_INTERRUPT (void)  __attribute__((signal));\
												void __vector_##SPI_INTERRUPT (void)
/* =================== User-defined ========================= */
// Error Status
typedef enum
{
	SPI_enuOK=0,
	SPI_enuNOK,
	SPI_enuDataCollision,


}SPI_enuErrorStatus;

// SPI Control Register [SPCR]
typedef enum
{
	SPI_enuSPR0=0,
	SPI_enuSPR1,
	SPI_enuCPHA,
	SPI_enuCPOL,
	SPI_enuMSTR,
	SPI_enuDORD,
	SPI_enuSPE,
	SPI_enuSPIE
}SPI_tenuSPCR;

// SPI Status Register [SPSR]
typedef enum
{
	SPI_enuSPI2X=0,
	SPI_enuWCOL=6,
	SPI_enuSPIF,
}SPI_tenuSPSR;


// SPI Data Register [SPDR]
typedef enum
{
	SPI_enuLSB=0,
	SPI_enuMSB=7,
}SPI_tenuSPDR;

// SPI Clock Rate Selection [Prescaler]
typedef enum
{
	SPI_enuPrescaler_4=0,
	SPI_enuPrescaler_16,
	SPI_enuPrescaler_64,
	SPI_enuPrescaler_128,
	SPI_enuPrescaler_2,
	SPI_enuPrescaler_8,
	SPI_enuPrescaler_32,
	SPI_enuPrescaler_64_,
}SPI_tenuPrescaler;

/* ======================= APIs =============================== */
SPI_enuErrorStatus SPI_enuInit (void);

SPI_enuErrorStatus SPI_enuMasterInit (void);
SPI_enuErrorStatus SPI_enuSlaveInit  (void);

/* As Sending & Receiving are done together at SPI */
u8 SPI_u8Transcieve (u8 Cpy_u8Data);


#endif /*SPI_INTERFACE_H_ */
