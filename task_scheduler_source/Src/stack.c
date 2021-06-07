#include <stdint.h>
#include <stdio.h>
#include "main.h"

extern TCB_t user_tasks[MAX_TASKS];
extern void idle_task();
extern void task1_handler();
extern void task2_handler();
extern void task3_handler();
extern void task4_handler();

void print_stack_info()
{
    printf("SRAM start              : %x\n", SRAM_START);
    printf("SRAM size               : %d\n", SIZE_SRAM);
    printf("SRAM end                : %x\n", SRAM_END);
    printf("Scheduler stack size    : %d\n", SIZE_SCHED_STACK);
    printf("Task Stack size         : %d\n", SIZE_TASK_STACK);
    printf("Task 1 stack start      : %x\n", T1_STACK_START);
    printf("Task 2 stack start      : %x\n", T2_STACK_START);
    printf("Task 3 stack start      : %x\n", T3_STACK_START);
    printf("Task 4 stack start      : %x\n", T4_STACK_START);
    printf("Scheduler task start    : %x\n", SCHED_STACK_START);

}

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack)
{
	//first argument passed to this function is r0
	//__asm volatile ("MSR MSP,R0");
     __asm volatile("MSR MSP,%0": :  "r" (sched_top_of_stack)  :   );
	 //branch indirect back to main, which is stored in LR
     __asm volatile("BX LR");

}

/* this function stores dummy stack contents for each task */

void init_tasks_stack(void)
{
	//task 0 is idle and always in run state
	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;
	user_tasks[3].current_state = TASK_READY_STATE;
	user_tasks[4].current_state = TASK_READY_STATE;

	//addresses of each task's psp
	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;
	user_tasks[3].psp_value = T3_STACK_START;
	user_tasks[4].psp_value = T4_STACK_START;

	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = task1_handler;
	user_tasks[2].task_handler = task2_handler;
	user_tasks[3].task_handler = task3_handler;
	user_tasks[4].task_handler = task4_handler;


	uint32_t *pPSP;
	//loop through pPSP and assign regiset value
	for(int i = 0 ; i < MAX_TASKS ;i++)
	{
		//initialize pPSP to addr of each task. should be 0x400 of 1024 KB apart
		pPSP = (uint32_t*) user_tasks[i].psp_value;

		//XSR
		pPSP--;
		*pPSP = DUMMY_XPSR;//0x01000000

		//PC address of task handler. must be odd
		pPSP--; //PC
		*pPSP = (uint32_t) user_tasks[i].task_handler;

		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;

		//r0 through r12
		for(int j = 0 ; j < 13 ; j++)
		{
			pPSP--;
		    *pPSP = 0;

		}
		//store value of psp
		user_tasks[i].psp_value = (uint32_t)pPSP;


	}

}

