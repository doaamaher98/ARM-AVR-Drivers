/*
 * main.c
 *
 *  Created on: Mar 18, 2023
 *      Author: engdo
 */

/* Make prescaler = 64
 * Sys freq = 1msec
 * Required tick time = 1ms
 * TICK_TIME = PRESC/SYS_FREQ = 64/8 = 8usec
 * Compare match =>  Required_time / TICK_TIME = 1000us/8us = 125
 *  1- CTC Mode
 *  2- Set Compare match value = 125
 *  3- Prescaler/64
 *  4- CTC Interrupt Enable.
 *
 */
#include "../00-LIB/Bit_Math.h"

#include "../01-MCAL/DIO.h"

#include "../02-Services/Scheduler_Interface.h"

#include "../03-HAL/LED.h"

void Task1 (void);
void Task2 (void);

void main(void)
{
	DIO_enuInit();

	SchedulerTaskInfo_tstr_t Task1_t,Task2_t,Task3_t;

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


