/*
 * Scheduler.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Doaa Maher
 */

#include "STK_Interface.h"
#include "Scheduler_Interface.h"

// Another struct for the Task State
typedef struct
{
	Sched_tstrTask_t * Task_Info;
	u32 RemainingTimeMS;
	Scheduler_tenuRunnableStatus Task_Status;
}Sched_tstrRunnable_t;

// Array of structure of Tasks : [higher priority comes first]
Sched_tstrRunnable_t Runnable_Tasks [SCHED_NUMBER_OF_TASKS] = {NULL_PTR} ;

// extern Array of Runnable Configurations.
extern Sched_tstrTask_t Runnable_Applications [1];

// A Flag to indicate that the task has finished
static Sched_Flag = 0;

// Prototype for sched handler [ISR]
static void Scheduler_Handle (void);
static void Scheduler_Handle_FirstDelay (void);
static void systick_cbf(void);

/******************************************************************************************/
Scheduler_tenuErrorStatus Sched_enuInit(void)
{
	Scheduler_tenuErrorStatus LocalErrorStatus = Sched_enuOK;

	/* Initializing Systick timer */
	STK_enuInit();
	/* Initialize your Tick Time */
	STK_enuSetPeriodMS(STK_enuHSI, STK_enuAHB, SCHED_TICK_TIME_MS);
	/* Enable Systick Interrupt */
	STK_enuEnableInterrupt();

	STK_enuSetCallback(systick_cbf);

	/* Initializing */
	u8 LocalIterator =0;

	for (LocalIterator=0; LocalIterator < SCHED_NUMBER_OF_TASKS ; LocalIterator++)
	{
		Runnable_Tasks[LocalIterator].Task_Info = &Runnable_Applications[LocalIterator];
		Runnable_Tasks[LocalIterator].RemainingTimeMS = Runnable_Applications[LocalIterator].Task_Periodicity_MS;
	}

	return LocalErrorStatus;
}
/******************************************************************************************/
Scheduler_tenuErrorStatus Sched_enuStart (void)
{
	Scheduler_tenuErrorStatus LocalErrorStatus = Sched_enuOK;

	/* Start the Timer */
	STK_enuStartTimer();

	/* Infinite Loop */
	while (1)
	{
		/* Asking if a new tick has came */
		if (Sched_Flag)
		{
			Scheduler_Handle();
			/* Lowering the flag */
			Sched_Flag = 0;
		}
	}

	return LocalErrorStatus;
}

/******************************************************************************************/
/* To detect CPU LOAD */
static void systick_cbf(void)
{
	if (Sched_Flag == 0)
	{
		Sched_Flag = 1;
	}
	else
	{
#warning "CPU LOAD EXCEEDED 100%"
	}
}
/******************************************************************************************/
// ISR : To say which task should be next to get executed = "ordering the tasks", comes every tick.
static void Scheduler_Handle (void)
{
	u8 LocalIterator = 0;

	for (LocalIterator=0; LocalIterator < SCHED_NUMBER_OF_TASKS ; LocalIterator ++)
	{
		/* Check if the tasks reached their periodicity */
		if (Runnable_Tasks[LocalIterator].Task_Info->Task_Cbf)
		{
			if (Runnable_Tasks[LocalIterator].RemainingTimeMS == 0)
			{
				/* Execute the Task */
				Runnable_Tasks[LocalIterator].Task_Info->Task_Cbf();
				/* Set the Remaining time to be the periodicity */
				Runnable_Tasks[LocalIterator].RemainingTimeMS = Runnable_Tasks[LocalIterator].Task_Info->Task_Periodicity_MS;
			}

			/* Subtract Remaining time from TICK */
			Runnable_Tasks[LocalIterator].RemainingTimeMS -= SCHED_TICK_TIME_MS;
		}
	}
}
/******************************************************************************************/
// ISR : with first delay
//static void Scheduler_Handle_FirstDelay (void)
//{
//	u8 LocalIterator = 0;
//
//	static u16 TickCount = 0;			// Increments each time to be compared with the periodicity
//
//	for (LocalIterator=0 ; LocalIterator < SCHED_NUMBER_OF_TASKS ; LocalIterator++)
//	{
//		/* Check for null pointer & if task is ready */
//		if ((Runnable_Tasks[LocalIterator].Task_Status == Sched_enuReady)  && (Runnable_Tasks[LocalIterator].Task_Info->Task_Cbf != NULL_PTR))
//		{
//			/* Check for first delay, if it's = 0, then it's ready to get executed! */
//			if ((Runnable_Tasks[LocalIterator].Task_Info->Task_FirstDelay_MS) == 0)
//			{
//
//				Runnable_Tasks[LocalIterator].Task_Info->Task_Cbf();
//			}
//			/* if first delay wasn't = 0, then decrement it */
//			else
//			{
//				Runnable_Tasks[LocalIterator].Task_Info->Task_FirstDelay_MS --;
//			}
//		}
//	}
//}
/******************************************************************************************/
void Sched_voidSuspendTask(u8 Cpy_u8Priority)
{
	Runnable_Tasks[Cpy_u8Priority].Task_Status = Sched_enuSuspended;
}
/******************************************************************************************/

void Sched_voidResumeTask(u8 Cpy_u8Priority)
{
	Runnable_Tasks[Cpy_u8Priority].Task_Status = Sched_enuReady;
}
/******************************************************************************************/

void Sched_voidDeleteTask(u8 Cpy_u8Priority)
{
	Runnable_Tasks[Cpy_u8Priority].Task_Info->Task_Cbf = NULL_PTR;
}
/******************************************************************************************/
