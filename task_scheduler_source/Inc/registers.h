#include <stdint.h>

#ifndef REGISTERS_H
#define REGISTERS_H

#define SCB_BASE 0xe000ed00
typedef struct SCB {
    uint32_t CPUID;
    uint32_t ICSR; 
    uint32_t VTOR; 
    uint32_t AIRCR; 
    uint32_t SCR; 
    uint32_t CCR; 
    uint32_t SHPR1; 
    uint32_t SHPR2; 
    uint32_t SHPR3; 
    uint32_t SHCSR; 
    uint32_t CFSR; 
    uint32_t MMSR; 
    uint32_t BFSR; 
    uint32_t UFSR; 
    uint32_t HFSR; 
    uint32_t MMAR; 
    uint32_t BFAR; 
    uint32_t AFSR; 
}SCB_t;

typedef struct FaultStack {
   uint32_t reg0, reg1, reg2, reg3, reg12, link, progC, XPSR; 
}FaultStack_t;

#endif
