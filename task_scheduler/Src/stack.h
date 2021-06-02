/*
 * stack.h
 *
 *  Created on: Jun 1, 2021
 *      Author: keith
 */

#ifndef STACK_H_
#define STACK_H_

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_stack_start);
void init_task_stack();
void print_stack_info();


#endif /* STACK_H_ */
