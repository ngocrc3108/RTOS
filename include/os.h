#ifndef __OS_H__
#define __OS_H__

#include <stdint.h>

typedef struct {
    uint32_t SP;
    uint32_t R4;
    uint32_t R5;
    uint32_t R6;
    uint32_t R7;
    uint32_t R8;
    uint32_t R9;
    uint32_t R10;
    uint32_t R11;
    uint32_t PRIMASK;
    uint32_t FAULTMASK;
    uint32_t BASEPRI;
    uint32_t CONTROL;
} os_task_context_t;

typedef struct {
    uint32_t task_address; 
    uint32_t stack_size;
    os_task_context_t context;
} os_task_t;

extern os_task_context_t* current_context;
os_task_context_t* os_find_next_task();
void os_add_task(uint32_t task_address, uint32_t stack_size);
void os_start();

void __asm_os_switch_context();
void __asm_os_start(uint32_t task_address, uint32_t stack_address);

#endif
