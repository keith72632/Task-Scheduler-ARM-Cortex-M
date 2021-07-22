/*
 * kernel.c
 *
 *  Created on: Jul 22, 2021
 *      Author: keith
 */
#include "faults.h"
#include "main.h"
#include "psp.h"
#include "stack.h"
#include "systick.h"
#include "tasks.h"

void OS_KernelInit()
{
	enable_processor_faults();

	init_scheduler_stack(SCHED_STACK_START);

	init_tasks_stack();

	init_systick_timer(TICK_HZ);

	switch_sp_to_psp();

	task1_handler();
}
