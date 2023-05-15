#include "RCC.h"
#include "STK_Interface.h"
#include "GPIO.h"

#include "Scheduler_Interface.h"

#include "LED.h"

/* Prototypes for Application Tasks */
void App1_Task(void);
void App2_Task(void);

/* Main Function */
void main (void)
{
	/* RCC Init */
	RCC_enuEnablePeripheralClk(RCC_enuAHB1_GPIOA,RCC_enuAHB1_GPIOA);

	/* Init LED */
	LED_enuLEDInit();
	/* Init Scheduler */
	Sched_enuInit();
	/* Start Sched */
	Sched_enuStart();

	while (1)
	{

	}
}

/* Toggling LED0 */
void App1_Task(void)
{
	u8 LocalState1 = 0;

	GPIO_enuGetPinValue(GPIO_enuPort_A,GPIO_enuPin_0,&LocalState1);
	LED_enuSetLEDValue(LED_enuLED0,LocalState1^1);
}

/* Toggling LED1 */
void App2_Task(void)
{
	 u8 LocalState2 = 0;

	GPIO_enuGetPinValue(GPIO_enuPort_A,GPIO_enuPin_1,&LocalState2);
	LED_enuSetLEDValue(LED_enuLED1,LocalState2^1);
}

