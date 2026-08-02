#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

#define TIM2_BASE 0x40000000

typedef struct timer_register_t
{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t SMCR;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t CCMR1;
    uint32_t CCMR2;
    uint32_t CCER;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
    uint32_t CCR1;
    uint32_t CCR2;
    uint32_t CCR3;
    uint32_t CCR4;
    uint32_t DCR;
    uint32_t DMAR;
} timer_register_t;

#define TIM2 ((timer_register_t*)TIM2_BASE)

void timer_init(timer_register_t* timer);
void timer_enable_interrupt(timer_register_t* timer);
void timer_start(timer_register_t* timer);

static inline uint32_t timer_get_timer_offset(timer_register_t* timer)
{
    return ((uint32_t)timer - (uint32_t)TIM2) / sizeof(timer);
}

#endif