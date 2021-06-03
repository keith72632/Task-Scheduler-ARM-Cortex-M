/*
 * stack.c
 *
 *  Created on: Jun 1, 2021
 *      Author: keith
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "stack.h"

//all addresses of stack starts. These are unsigned ints, so must be cast to pointers
uint32_t psp_of_task[MAX_TASKS] = {T1_STACK_START, T2_STACK_START, T3_STACK_START, T4_STACK_START};

//all handlers
uint32_t task_handlers[MAX_TASKS];

extern uint8_t current_task;


__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start)
{
    //first argument passed to this function is r0
    //__asm volatile("MSR MSP,R0");
    __asm volatile ("MSR MSP,%0": : "r"(scheduler_stack_start) : );
    //Branch indirect back to main, which is stored in LR
    __asm volatile ("BX LR");
}

void init_task_stack(void)
{
	uint32_t *pPSP;
	//loop through pPSP and assign register value
	for(int i = 0; i < MAX_TASKS; i++)
	{
        //initialize pPSP to addr of each task. should be 0x400 or 1024 KB apart
		pPSP = (uint32_t *)psp_of_task[i];
        printf("Task%d PSP intialized address: %p\n\n", i+1, pPSP);

        //XPSR
        pPSP--;
        *pPSP = 0x01000000;

        //PC. Address of task handler. Must be odd
        pPSP--;
        *pPSP = task_handlers[i];
        printf("Return address of task%d handler(PC): %lx\n\n", i+1, *pPSP); 

        //LR
        pPSP--;
        *pPSP = 0xfffffffd;

        //r0 through r12
        for(int j = 0; j < 13; j++)
        {
            pPSP--;
            *pPSP = i;
        }

        //store value of psp
        psp_of_task[i] = (uint32_t)pPSP;
	}
}

void print_stack_info()
{
    printf("SRAM start              : %x\n", SRAM_START);
    printf("SRAM size               : %d\n", SRAM_SIZE);
    printf("SRAM end                : %x\n", SRAM_END);
    printf("Scheduler stack size    : %d\n", SIZE_SCHED_STACK);
    printf("Task Stack size         : %d\n", SIZE_TASK_STACK);
    printf("Task 1 stack start      : %x\n", T1_STACK_START);
    printf("Task 2 stack start      : %x\n", T2_STACK_START);
    printf("Task 3 stack start      : %x\n", T3_STACK_START);
    printf("Task 4 stack start      : %x\n", T4_STACK_START);
    printf("Scheduler task start    : %x\n", SCHED_STACK_START);

}

__attribute__((naked)) void switch_sp_to_psp(void)
{
	//initialize the psp with task1 stack start
	__asm volatile("PUSH {LR}"); //save lr value incase other functions corrupt it
	__asm volatile("BL get_psp_value"); // Branch with link. this is why is saved the lr
	__asm volatile("MSR PSP,R0");// value in get_psp_value returned as r0. init psp
	__asm volatile("POP {LR}"); //resume lr

	//change sp to psp
	__asm volatile("MOV R0,0x02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");
}

uint32_t get_psp_value(void)
{
	return psp_of_task[current_task];
}

void save_psp_value(uint32_t current_psp_value)
{
    psp_of_task[current_task] = current_psp_value;
}

