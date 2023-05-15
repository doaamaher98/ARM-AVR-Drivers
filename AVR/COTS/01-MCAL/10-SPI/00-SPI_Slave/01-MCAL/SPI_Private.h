/*
 * SPI_Private.h
 *
 *  Created on: Apr 1, 2023
 *      Author: engdo
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


/* ======================= Memory Mapping ======================= */
#define					SPI_SPDR				*((volatile u8*) 0x2F)
#define					SPI_SPSR				*((volatile u8*) 0x2E)
#define					SPI_SPCR				*((volatile u8*) 0x2D)



#endif /* SPI_PRIVATE_H_ */
