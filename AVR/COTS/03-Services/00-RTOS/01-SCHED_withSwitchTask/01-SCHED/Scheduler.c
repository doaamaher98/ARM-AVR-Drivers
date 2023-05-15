/*
 * Scheduler.c
 *
 *  Created on: Mar 30, 2023
 *      Author: Doaa Maher
 */

#include "../00-LIB/Std_Types.h"
#include "../00-LIB/Bit_Math.h"

#include "TIMER0.h"
#include "GIE.h"

#include "Scheduler_Interface.h"
#include "Scheduler_Cfg.h"

#define 			F_CPU				8000000UL

static u8 GlobalFlag = 0;

/* Struct of Current Task Status */
typedef struct
{
	SchedulerTaskInfo_tstr_t * Task_info;
	u32 RemainingTime;
}Scheduler_tsrtTasks_t;


/* Array of Tasks */
Scheduler_tsrtTasks_t App_Array[SCHED_TASKS_NUM];

static void sched_voidcbf (void);

void Sched_voidInit (void)
{
	/* Initializing GIE */
	GIE_enuInit_EnableGIE();
	/* Initializing TIMER0 */
	TMR0_enuInitPreCompile();
	/* Adjusting timer every tick time */
	TMR0_enuSetCompareMatchValue(SCHED_TICK_TIME_MS);
	/* Calling The Scheduler function which will run in the ISR of the timer */
	TMR0_enuRegisterCallback_CTC(&sched_voidcbf);

	u8 LocalIterator =0;

	for (LocalIterator =0; LocalIterator<SCHED_TASKS_NUM; LocalIterator++ )
	{
		App_Array[LocalIterator].Task_info = &Task_Info;
		App_Array[LocalIterator].RemainingTime = Task_Info[LocalIterator].Task_FirstDelay;
	}
}
/****************************************************************************/
static void sched_voidcbf (void)
{
	if (GlobalFlag == 0)
	{
		GlobalFlag =1;
	}
}
/****************************************************************************/
void Sched_enuStart (void)
{
//	/* Starting the timer */
//	TMR0_enuInitPreCompile();

	while (1)
	{
		if (GlobalFlag == 1)
		{
			voidScheduler();
			GlobalFlag =0;
		}
	}

}
/****************************************************************************/
// Runs the ISR of timer
static void voidScheduler (void)
{
	static u16 LocalTickCounter = 0;
	u8 LocalIterator = 0;

	LocalTickCounter ++;

	/* Checking the tasks periodicity */
	for (LocalIterator=0; LocalIterator < SCHED_TASKS_NUM ; LocalIterator++)
	{
		if (App_Array[LocalIterator].RemainingTime == 0)
		{
			/* Execute Task */
			App_Array[LocalIterator].Task_info->Task_Cbf();
			App_Array[LocalIterator].RemainingTime = Task_Info[LocalIterator].Task_Periodicity;
		}
		else
		{
			App_Array[LocalIterator].RemainingTime -= SCHED_TICK_TIME_MS;
		}
	}
}

/****************************************************************************/



