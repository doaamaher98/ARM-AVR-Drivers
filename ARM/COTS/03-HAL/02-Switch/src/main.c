#include "RCC_Driv.h"
#include "GPIO.h"
#include "STK_Interface.h"
#include "Scheduler_Interface.h"

#include "LED.h"
#include "SW.h"

//void App1_Task(void);
//void App2_Task(void);
//void App3_Task(void);

//static u8 LocalSwitchState = 0;

void main(void)
{
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOA);

	LED_enuLEDInit();
	Switch_enuInit();

	Sched_enuInit();
	Sched_enuStart();

	while (1);
}
