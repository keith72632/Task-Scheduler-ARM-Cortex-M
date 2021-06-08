/*
 * faults.c
 *
 *  Created on: Jun 7, 2021
 *      Author: keith
 */

#include <stdint.h>
#include <stdio.h>
#include "registers.h"
 
extern SCB_t *SCB;

void enable_processor_faults(void)
{

	SCB->SHCSR |= (1 << 16) | (1 << 17) | (1 << 18);
	#if 0
	uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

	*pSHCSR |= ( 1 << 16); //mem manage
	*pSHCSR |= ( 1 << 17); //bus fault
	*pSHCSR |= ( 1 << 18); //usage fault
	#endif
}

//2. implement the fault handlers
__attribute__((naked)) void HardFault_Handler(void)
{
	__asm volatile("MRS R0,MSP");
	__asm volatile("B HardFault_Handler_C");
}

void HardFault_Handler_C(uint32_t *stack)
{
	printf("Exception : Hardfault\n");
	printf("r0 = %p\n", stack);
	while(1);
}


//MemManage Fault
__attribute__((naked)) void MemManage_Handler(void)
{
	__asm volatile("MRS R0,MSP");
	__asm volatile("B MemManage_Handler_C");
}

__attribute__((naked)) void MemManage_Handler_C(uint32_t *stack)
{
	printf("Exception : MemManage\n");
	//uint32_t *pMMSR = (uint32_t*)0xE000ED28;
	printf("MMSR = %lx\n", (SCB->MMSR) & 0xffff);
	printf("R0 = %p\n", stack);
	while(1);
}


//Bus Fault
__attribute__((naked)) void BusFault_Handler(void)
{
	__asm volatile("MRS R0,MSP");
	__asm volatile("B BusFault_Handler_C");
}

void BusFault_Handler_C(uint32_t *stack)
{
	printf("Exception : BusFault\n");
	uint32_t *pBFSR = (uint32_t *)0xE000ED29;
	//try using this with 0xe000ed28 & 0xffff0000
	printf("BFSR = %lx\n", (*pBFSR) & 0xffff);
	printf("r0 = %p\n", stack);
	while(1);
}

//Usage fault
__attribute__((naked)) void UsageFault_Handler(void)
{
	__asm ("MRS R0,MSP");
	__asm ("B UsageFault_Handler_C");
}
void UsageFault_Handler_C(uint32_t *pBaseStackFrame)
{
	uint32_t *pUFSR = (uint32_t *)0xe000ed2a;
	printf("Exception: UsageFault\n");
	printf("UFSR = %lx\n", (*pUFSR) & 0xffff);
	printf("MSP = %p\n", pBaseStackFrame);
	while(1);
}
