/*
 * SPI_Slave_Interface.h
 *
 * Created: 4/14/2023 7:49:23 AM
 *  Author: engdo
 */ 


#ifndef SPI_SLAVE_INTERFACE_H_
#define SPI_SLAVE_INTERFACE_H_

#include "Std_Types.h"

#define MISO	6
#define SS		4
#define SCK		7

void SPI_voidInit(void);
void SPI_voidSendByte(u8 Data);
u8 SPI_u8ReadByte(void);
u8 SPI_u8TransceiveData(u8 Data);




#endif /* SPI_SLAVE_INTERFACE_H_ */