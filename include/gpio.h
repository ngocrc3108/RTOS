#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

#define GPIO_A_BASE 0x40010800
#define GPIO_C_BASE 0x40011000

typedef struct gpio_t
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
} gpio_t;

#define GPIO_A ((gpio_t*)GPIO_A_BASE)
#define GPIO_C ((gpio_t*)GPIO_C_BASE)

void gpio_init();
void gpio_write_pin(gpio_t* port, uint8_t pin, uint8_t value);
uint8_t gpio_read_pin(gpio_t* port, uint8_t pin);

#endif