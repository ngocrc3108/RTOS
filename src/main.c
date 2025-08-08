#include "gpio.h"

int main()
{
    gpio_init();

    while(1)
    {
        for(uint32_t count = 0; count < 0xfffff; count++);
        GPIO_C->ODR = ~GPIO_C->ODR;
    }
}