/*
 * Scheduler_Cfg.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Doaa Maher
 */

#include "Scheduler_Cfg.h"

extern void Task1 (void);
extern void Task2 (void);
extern void Task3 (void);
extern void SwitchTask(void);

const SchedulerTaskInfo_tstr_t Task_Info[SCHED_TASKS_NUM]=
{
		[0]=
		{
				.Task_Name = "Application1",
				.Task_Periodicity = 100,
				.Task_Priority = 0,
				.Task_Cbf = Task1

		},
		[1]=
		{
				.Task_Name = "Application2",
				.Task_Periodicity = 200,
				.Task_Priority = 1,
				.Task_Cbf = Task2
		},
		[2]=
		{
				.Task_Name = "Application3",
				.Task_Periodicity = 5,
				.Task_Priority = 2,
				.Task_Cbf = SwitchTask
		},
		[3]=
		{
				.Task_Name = "Application4",
				.Task_Periodicity = 20,
				.Task_Priority = 3,
				.Task_Cbf = Task3
		}
};
