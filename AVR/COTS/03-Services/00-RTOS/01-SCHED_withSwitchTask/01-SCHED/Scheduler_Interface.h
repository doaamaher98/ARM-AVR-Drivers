/*
 * Scheduler_Interface.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Doaa Maher
 */

#ifndef SCHEDULER_INTERFACE_H_
#define SCHEDULER_INTERFACE_H_

#include "../00-LIB/Std_Types.h"

#include "Scheduler_Private.h"

/* =============================== Pre-Processor =============================== */


/* ================================= User-defined ================================== */
// Error Status
typedef enum
{
	Sched_enuOK=0,
	Sched_enuNOK
}Scheduler_enuErrorStatus;


// Call back function definition
typedef void (*Scheduler_Cbf) (void);

// Task Structure, used whenever a new task is created
typedef struct
{
	u8 * Task_Name;
	u32 Task_Periodicity;
	u8 Task_Priority;
	u32 Task_FirstDelay;
	Scheduler_Cbf Task_Cbf;
}SchedulerTaskInfo_tstr_t;



/* ============================== APIs ======================================== */
void Sched_voidInit (void);

Scheduler_enuErrorStatus Sched_enuCreateTask (SchedulerTaskInfo_tstr_t * App_task);

void Sched_enuStart (void);



#endif /* SCHEDULER_INTERFACE_H_ */
