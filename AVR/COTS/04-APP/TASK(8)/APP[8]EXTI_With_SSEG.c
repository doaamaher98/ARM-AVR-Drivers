
#include "Std_Types.h"
#include "Delay.h"

#include "DIO.h"
#include "LED.h"
#include "PUSH_BUTTON.h"
#include "SSEGMENT.h"

#include "EXT_INT.h"

// Global var
u8 LocalIterator=-1;

/************* Function Prototypes *******************/
void SSEG_INC(void)
{
	LocalIterator++; 
	 if (LocalIterator == 10)
		LocalIterator =0;
		
	 HAL_SSEG_Display(DIO_enuPORTA,LocalIterator);
}

void SSEG_DEC(void)
{
	LocalIterator--;
	
	if (LocalIterator == 0)
		LocalIterator = 9;
		
	HAL_SSEG_Display(DIO_enuPORTA,LocalIterator);
}

/****************************************************/

int main (void)
{
	// DIO Init Function
	DIO_enuInit();

	/* Enabling Global Interrupt */
	GIE_enuInit_EnableGIE();
	
	/* Enabling INT0 & INT1 */
	EXT_INT0_Enable();
	EXT_INT1_Enable();
	
	/* EXT_INTS Initializations */
	EXT_INT_INIT();
	
	/* Callback functions to call the functions */
	EXT_INT0Callback_Set(SSEG_INC);
	EXT_INT1Callback_Set(SSEG_DEC);
	
	// 0 By Default
	HAL_SSEG_Display(DIO_enuPORTA,0);
	
	while (1)
	{
		
	}
}