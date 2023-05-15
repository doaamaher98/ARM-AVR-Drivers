/*
 * Scheduler_Cfg.c
 *
 *  Created on: Mar 28, 2023
 *      Author: Doaa Maher
 */

/* This file is not used at the moment */

#include "Scheduler_Interface.h"
#include "LCD_Interface.h"
#include "LED.h"

extern void LED_Switch_Application(void);
extern void LCD_voidTask(void);
extern void LCD_voidRunnable(void);
//extern void App4_Task(void);
//extern void Switch_voidTask (void);

Sched_tstrTask_t Runnable_Applications [SCHED_NUMBER_OF_TASKS] =
{
		[Sched_enuApplication1] =
		{
				.Task_Periodicity_MS = 500,
				.Task_Priority 		 = 1,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = LED_Switch_Application,
		}
		,

		[Sched_enuApplication2] =
		{
				.Task_Periodicity_MS = 2,
				.Task_Priority 		 = 2,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = LCD_voidTask,
		}
		,
		[Sched_enuApplication3] =
		{
				.Task_Periodicity_MS = 300,
				.Task_Priority 		 = 3,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = LCD_voidRunnable,
		}
};


