/*
 * Scheduler_Cfg.c
 *
 *  Created on: Mar 28, 2023
 *      Author: Doaa Maher
 */

/* This file is not used at the moment */

#include "Scheduler_Interface.h"

extern void App1_Task(void);
extern void App2_Task(void);
extern void App3_Task(void);
//extern void App4_Task(void);
extern void Switch_voidTask (void);

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
				.Task_Periodicity_MS = 300,
				.Task_Priority 		 = 2,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = App2_Task,
		}
		,
		[Sched_enuApplication3] =
		{
				.Task_Periodicity_MS = 5,
				.Task_Priority 		 = 3,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = App3_Task,
		}
		,

		[Sched_enuApplication4] =
		{
				.Task_Periodicity_MS = 5,
				.Task_Priority 		 = 4,
				.Task_FirstDelay_MS  = 0,
				.Task_Cbf			 = Switch_voidTask,
		}


};


