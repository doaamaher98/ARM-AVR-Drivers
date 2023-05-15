#include "RCC_Driv.h"
#include "GPIO.h"
#include "STK_Interface.h"

#include "LED.h"
#include "SW.h"

#include "Scheduler_Interface.h"

#include "LCD_Interface.h"

void main (void)
{
	RCC_enuEnableSysClk(RCC_enu_HSI);
	RCC_enuSelectSysClk(RCC_enu_HSI);

	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOA);
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOB);
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOC);

	LED_enuLEDInit();
//	Switch_enuInit();

//	LCD_enuInit_8Bits();

	Sched_enuInit();
	Sched_enuStart();

	while(1)
	{

	}
}
