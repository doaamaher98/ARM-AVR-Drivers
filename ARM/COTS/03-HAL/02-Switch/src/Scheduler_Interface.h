/*
 * Scheduler_Interface.h
 *
 *  Created on: Mar 25, 2023
 *      Author: Doaa Maher
 */

#ifndef SCHEDULER_INTERFACE_H_
#define SCHEDULER_INTERFACE_H_

#include "Std_Types.h"

#include "Scheduler_Cfg.h"

/* ================================== Pre-Processor Types  ================================== */

/* =================================== User defined types ================================== */
// Error Status
typedef enum
{
	Sched_enuOK=0,
	Sched_enuNOK,

}Scheduler_tenuErrorStatus;

// enum for Application Names
typedef enum
{
	Sched_enuApplication1=0,
	Sched_enuApplication2,
	Sched_enuApplication3,
	Sched_enuApplication4,
//	Sched_enuApplication5,
//	Sched_enuApplication6,
	Sched_enuNumberOfApplications
}Scheduler_tenuRunnableApplications;

// Runnable Status
typedef enum
{
	Sched_enuDormant=0,
	Sched_enuReady,
	Sched_enuWaiting,
	Sched_enuRunning,
	Sched_enuISR,
	Sched_enuSuspended,
	Sched_enuTerminated
}Scheduler_tenuRunnableStatus;

// Callback function definition
typedef void (*Sched_TaskCbf_t) (void);

// Struct for Runnable Tasks
typedef struct
{
	char *Task_Name;									// Runnable task name
	u32 Task_Periodicity_MS;							// Repeated every ... time?
	u8  Task_Priority;
	u16	Task_FirstDelay_MS;
	Sched_TaskCbf_t Task_Cbf;
}Sched_tstrTask_t;


/* ======================================= APIs ======================================== */
/* ===================================================================================== */
/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Initializing the Scheduler 				                    			*/
/********************************************************************************************/
Scheduler_tenuErrorStatus Sched_enuInit(void);

/********************************************************************************************/
/* Inputs        : void																		*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Starting the Scheduler	                                     			*/
/********************************************************************************************/
Scheduler_tenuErrorStatus Sched_enuStart (void);

/********************************************************************************************/
/* Inputs        : 																			*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Adding a Task to runnable state	 [Creating Task]              			*/
/********************************************************************************************/
Scheduler_tenuErrorStatus Sched_enuAddRunnable(Sched_tstrTask_t * runnable_task);

/********************************************************************************************/
/* Inputs        : 																			*/
/* Return        : Error Status (To ensure function Safety)                                 */
/* Functionality : Pausing a Runnable Task			                              			*/
/********************************************************************************************/
Scheduler_tenuErrorStatus Sched_enuSuspendRunnable (Sched_tstrTask_t * runnable_task, u32 Cpy_u32PauseTimeMS);

/********************************************************************************************/
void Sched_voidSuspendTask(u8 Cpy_u8Priority);
void Sched_voidResumeTask(u8 Cpy_u8Priority);
void Sched_voidDeleteTask(u8 Cpy_u8Priority);

/********************************************************************************************/

#endif /* SCHEDULER_INTERFACE_H_ */
