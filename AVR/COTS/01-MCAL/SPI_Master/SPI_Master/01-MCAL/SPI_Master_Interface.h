/*
 * SPI_Master_Interface.h
 *
 * Created: 4/14/2023 7:50:55 AM
 *  Author: engdo
 */ 

#include "Std_Types.h"

#ifndef SPI_MASTER_INTERFACE_H_
#define SPI_MASTER_INTERFACE_H_

#define			F_CPU		(1000000UL)

#define MOSI	5
#define SS		4
#define SCK		7

void SPI_voidInit(void);
void SPI_voidSendByte(u8 Data);
u8 SPI_u8ReadByte(void);
u8 SPI_u8TransceiveData(u8 Data);

#endif /* SPI_MASTER_INTERFACE_H_ */