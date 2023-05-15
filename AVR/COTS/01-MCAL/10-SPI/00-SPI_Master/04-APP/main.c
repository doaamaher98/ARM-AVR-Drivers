#include "../00-LIB/Delay.h"

#include "../01-MCAL/DIO.h"
#include "../01-MCAL/SPI_Interface.h"


void main(void)
{
	DIO_enuInit();

	SPI_enuMasterInit();

	while (1)
	{
		SPI_u8Transcieve(1);
		Delay_MS(10);
	}

}
