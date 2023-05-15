/*
 * SPI_Config.h
 *
 *  Created on: Apr 1, 2023
 *      Author: engdo
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


/* Options :
 * SPI_EN
 * SPI_DS
 */
#define				SPI_STATE					SPI_EN


/* Options :
 * SPI_INTERRUPT_EN
 * SPI_INTERRUPT_DS
 */
#define				SPI_INTERRUPT_STATE			SPI_INTERRUPT_DS

/* Options :
 * SPI_DATA_ORDER_LSB
 * SPI_DATA_ORDER_MSB
 */
#define				SPI_DATA_ORDER_CONFIG		SPI_DATA_ORDER_LSB


/* Options :
 * SPI_MCU_SLAVE
 * SPI_MCU_MASTER
 */
#define				SPI_MCU_MASTER_SLAVE_SELECT		SPI_MCU_MASTER

/* Options :
 * SPI_POLARITY_LOW
 * SPI_POLARITY_HIGH
 */
#define				SPI_POLARITY_SELECTION			SPI_POLARITY_LOW

/* Options :
 * SPI_DATA_SAMPLED_FIRST
 * SPI_DATA_SETUP_FIRST
 */
#define				SPI_CLOCK_PHASE					SPI_DATA_SAMPLED_FIRST

/* Options :
 * SPI_enuPrescaler_4
 * SPI_enuPrescaler_16
 * SPI_enuPrescaler_64
 * SPI_enuPrescaler_128
 * SPI_enuPrescaler_2
 * SPI_enuPrescaler_8
 * SPI_enuPrescaler_32
 * SPI_enuPrescaler_64_
 */

#define				SPI_PRESCALER_SELECTION			SPI_enuPrescaler_8



#endif /* SPI_CONFIG_H_ */
