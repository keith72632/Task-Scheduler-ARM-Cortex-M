#include <stdio.h>
#include "main.h"

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
