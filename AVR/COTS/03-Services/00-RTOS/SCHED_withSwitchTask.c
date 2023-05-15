/*
 * main.c
 *
 *  Created on: Mar 18, 2023
 *      Author: engdo
 */


#include "../00-LIB/Bit_Math.h"

#include "../01-MCAL/DIO.h"

#include "../02-Services/Scheduler_Interface.h"

#include "../03-HAL/LED.h"
#include "../03-HAL/PUSH_BUTTON.h"

void Task1 (void);
void Task2 (void);
void Task3 (void);

void main(void)
{
	DIO_enuInit();

	Sched_voidInit();
	Sched_enuStart();

	while (1)
	{

	}
}

void Task1 (void)
{
	static u8 LocalLEDState = 0;

	DIO_enuGetPin(DIO_enuPin0,&LocalLEDState);

	TGL_BIT(LocalLEDState,DIO_enuPin0);
}

void Task2 (void)
{
	static u8 LocalLEDState = 0;

	DIO_enuGetPin(DIO_enuPin1,&LocalLEDState);

	TGL_BIT(LocalLEDState,DIO_enuPin1);
}

void Task3 (void)
{
	static u8 LocalLEDState = 0;

	LocalLEDState = Get_PUSH_BUTTON_State(DIO_enuPin8,&LocalLEDState);
	if (LocalLEDState == PUSH_BUTTON_enuPressed)
	{
		HAL_LED_ON(DIO_enuPin2);
	}
	else if (LocalLEDState == PUSH_BUTTON_enuReleased)
	{
		HAL_LED_OFF(DIO_enuPin2);
	}
}

