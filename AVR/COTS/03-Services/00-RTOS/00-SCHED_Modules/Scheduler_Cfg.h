/*
 * Scheduler_Cfg.h
 *
 *  Created on: Mar 30, 2023
 *      Author: Doaa Maher
 */

#ifndef SCHEDULER_CFG_H_
#define SCHEDULER_CFG_H_

#include "Scheduler_Interface.h"
// Number of tick time : System Tick, for the Timer0 to generate an interrupt in .. secs
#define					SCHED_TICK_TIME_MS				1

// Number of tasks
#define					SCHED_TASKS_NUM					4

// Array of Tasks
extern const SchedulerTaskInfo_tstr_t Task_Info[SCHED_TASKS_NUM];

#endif /* SCHEDULER_CFG_H_ */
