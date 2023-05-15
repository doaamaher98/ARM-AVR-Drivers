/*
 * App.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Doaa Maher
 */

#include "LED.h"
#include "SW.h"

void App1_Task(void)
{
//	LED_enuLEDToggle(LED_enuLED_Warning,LED_enuLED_ON);
	LED_enuSetLEDValue(LED_enuLED_Warning,LED_enuLED_ON);
}

void App2_Task(void)
{
//	LED_enuLEDToggle(LED_enuLED_Alarm);
//	LED_enuSetLEDValue(LED_enuLED_Alarm,LED_enuLED_ON);
}

void App3_Task(void)
{
	u8 Switch_State = 0;

	Switch_State = Switch_u8GetSwitchState(Switch_enu_On);

	if (Switch_State == Switch_enuPressed)
	{
		LED_enuSetLEDValue(LED_enuLED_Alarm,LED_enuLED_ON);
	}
	else if (Switch_State == Switch_enuReleased)
	{
		LED_enuSetLEDValue(LED_enuLED_Alarm,LED_enuLED_OFF);
	}
}
