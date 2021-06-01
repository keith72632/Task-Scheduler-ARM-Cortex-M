/*
 * faults.c
 *
 *  Created on: Jun 1, 2021
 *      Author: keith
 */
#include <stdint.h>
#include <stdio.h>
#include "registers.h"

void enable_processor_faults(uint8_t mem, uint8_t bus, uint8_t usage)
{
    uint32_t *pSHCSR = (uint32_t *)0xE000ED24;
    *pSHCSR |= (mem ? 1 << 16 : 0) | (bus ? 1 << 17 : 0) | (usage ? 1 << 18 : 0);
}

__attribute__((naked)) void HardFault_Handler()
{
    __asm ("MRS R0,MSP");
    __asm ("B HardFault_Handler_C");
}

void HardFault_Handler_C(registers_t *regs)
{
    printf("Hard Fault! PC: %lx\n", regs->progC);
    while(1);
}

__attribute__((naked)) void MemManage_Handler(void)
{
    __asm("MRS R0,MSP");
    __asm("B MemManage_Handler_C");
}

void MemManage_Handler_C(registers_t *regs)
{
    printf("Memory Manage Fault. PC: %lx\n", regs->progC);
    while(1);
}

__attribute__((naked)) void BusFault_Handler(void)
{
    __asm("MRS R0,MSP");
    __asm("B BusFault_Handler_C");
}

void BusFault_Handler_C(registers_t *regs)
{
    printf("Bus Fault. PC: %lx\n", regs->progC);
    while(1);
}

__attribute__((naked)) void UsageFault_Handler(void)
{
    __asm("MRS R0,MSP");
    __asm("B UsageFault_Handler_C");
}

void UsageFault_Handler_C(registers_t *regs)
{
    printf("Bus Fault. PC: %lx\n", regs->progC);
    while(1);
}

