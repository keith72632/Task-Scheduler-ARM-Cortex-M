#include <stdint.h>

#ifndef STACK_H
#define STACK_H

void print_stack_info();
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);

#endif