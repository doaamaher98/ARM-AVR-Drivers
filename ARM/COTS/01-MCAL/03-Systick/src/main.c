#include "RCC.h"
#include "STK_Interface.h"

#include "GPIO.h"
#include "LED.h"

/*** ISR ***/
void func1(void)
{
	u8 LocalValue=0;

	GPIO_enuGetPinValue(GPIO_enuPort_A,LED_enuLED1,&LocalValue);

	// Toggling LED
	LED_enuSetLEDValue(LED_enuLED1,LocalValue ^ 1);
}

void main(void)
{
	RCC_enuEnablePeripheralClk(RCC_enuAHB1,RCC_enuAHB1_GPIOA);

	STK_enuInit();
	LED_enuLEDInit();

//	STK_enuSetCounts(10);
	STK_enuEnableInterrupt();

	LED_enuSetLEDValue(LED_enuLED0,LED_enuLED_ON);
	STK_enuSetPeriodMS(STK_enuHSI,STK_enuAHB_8,500);

	STK_enuSetCallback(&func1);

	STK_enuStartTimer();

	while(1)
	{

	}
}
