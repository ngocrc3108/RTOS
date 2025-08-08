#include "gpio.h"
#include "rcc.h"

void gpio_init()
{
    RCC->APB2ENR = 1 << 4;
    GPIO_C->CRH = (0b0101 << 20);
    GPIO_C->ODR = 0;
}

void gpio_write_pin(gpio_t* port, uint8_t pin, uint8_t value)
{
    port->BSRR = (value == 0) ? (1 << (pin + 16)) : (1 << pin);
}

uint8_t gpio_read_pin(gpio_t* port, uint8_t pin)
{
    return ((port->ODR >> pin) & (uint32_t)0x01);
}