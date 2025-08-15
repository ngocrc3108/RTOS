#ifndef __NVIC_H__
#define __NVIC_H__

#include <stdint.h>

#define NVIC_BASE 0xE000E100

void __asm_set_privilege(uint32_t level);

static inline void nvic_enable_iqr(uint32_t iqr_number)
{
    __asm_set_privilege(1);
    *(uint32_t*)(NVIC_BASE) = (1 << iqr_number);
    __asm_set_privilege(0);
}

#endif