#include "timer.h"
#include "rcc.h"
#include "nvic.h"

void timer_init(timer_register_t* timer)
{
    RCC->APB1ENR |= (0x01 << timer_get_timer_offset(timer)); // enable timer clock
    timer->ARR = 0xff;
    timer->PSC = 0xff;
    timer->CNT = 0;
}

void timer_start(timer_register_t* timer)
{
    timer->CR1 |= 0x01; // enable counter
}

void timer_enable_interrupt(timer_register_t* timer)
{
    timer->DIER |= 0x01; // enable interrupt
    nvic_enable_iqr(timer_get_timer_offset(timer) + 28);
}