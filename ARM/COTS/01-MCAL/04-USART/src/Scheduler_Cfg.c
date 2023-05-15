/*
 * Scheduler_Cfg.c
 *
 *  Created on: Mar 28, 2023
 *      Author: Doaa Maher
 */

/* This file is not used at the moment */

#include "Scheduler_Interface.h"

extern void App1_Task(void);
//extern void App2_Task(void);
extern void USART_Task(void);

Sched_tstrTask_t Runnable_Applications [SCHED_NUMBER_OF_TASKS] =
{
		[Sched_enuApplication1] =
		{
				.Task_Periodicity_MS = 500,
				.Task_Priority 		 = 1,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = App1_Task,
		}
		,

		[Sched_enuApplication2] =
		{
				.Task_Periodicity_MS = 1000,
				.Task_Priority 		 = 2,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = USART_Task,
		}

};


