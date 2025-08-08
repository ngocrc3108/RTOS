#include "gpio.h"
#include "rcc.h"

void gpio_init()
{
    RCC->APB2ENR = 1 << 4;
    GPIO_C->CRH = (0b0101 << 20);
    GPIO_C->ODR = 0;
}