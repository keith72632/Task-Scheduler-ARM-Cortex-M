#include <stdint.h>

#ifndef REGISTERS_H
#define REGISTERS_H

#define SCB_BASE 0xe000ed00
//System Control Block
typedef struct SCB {
    uint32_t CPUID;
    uint32_t ICSR; //Interrupt Status Control Register. Base + 0x04
    uint32_t VTOR; //Vector Table Offset Register. Base + 0x08
    uint32_t AIRCR; //Application Interrupt and Reset Control Register. Base + 0x0C
    uint32_t SCR; //System Control Register. Base + 0x10
    uint32_t CCR; //Configuration and Control Register. Base + 0x14
    uint32_t SHPR1; //System Handler and Priority Register 1. Base + 0x18
    uint32_t SHPR2; //System Handler and Priority Register 2. Base + 0x1C 
    uint32_t SHPR3; //System Handler and Priority Regsiter 3. Base + 0x20
    uint32_t SHCSR; //System Handler and Control Regsiter. Base + 0x24
    uint32_t CFSR; //Control Fault Status Register. bit[0-7] = MMSR. bit[8-15] = BFSR. bit[16-31] = USFR
    //uint32_t MMSR;
    //uint32_t BFSR;
    //uint32_t UFSR;
    uint32_t HFSR; //Hard Fault Status Register. Base + 0x2C
    uint32_t padding;
    uint32_t MMFAR; //Memory Manage Fault Address Register. Base + 0x34
    uint32_t BFAR; //Bus Fault Address Register. Base + 0x38 ???
    uint32_t AFSR; //Auxillary Fault Status Register. Base + 0x3C
}__attribute__((aligned))SCB_t;

typedef struct FaultStack {
   uint32_t reg0, reg1, reg2, reg3, reg12, link, progC, XPSR; 
}FaultStack_t;

#endif
