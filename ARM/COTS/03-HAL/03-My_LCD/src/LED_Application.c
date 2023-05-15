/*
 * LED_Application.c
 *
 *  Created on: Apr 6, 2023
 *      Author: Doaa Maher
 */

#include "GPIO.h"
#include "LED.h"
#include "SW.h"

void LED_Switch_Application (void)
{
//	u8 Switch_State = 0;
//
//	Switch_State = Switch_u8GetSwitchState(Switch_enu_On);
//
//	if (Switch_State == Switch_enuPressed)
//	{
//		LED_enuSetLEDValue(LED_enuLED_Warning,LED_enuLED_ON);
//	}
//	else if (Switch_State == Switch_enuReleased)
//	{
//		LED_enuSetLEDValue(LED_enuLED_Warning,LED_enuLED_OFF);
//	}

	LED_enuLEDToggle(LED_enuLED0,LED_enuLED_ON);
}
