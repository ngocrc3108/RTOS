#include "gpio.h"

int main()
{
    gpio_init();

    while(1)
    {
        for(uint32_t count = 0; count < 0xfffff; count++);
        gpio_write_pin(GPIO_C, 13, !gpio_read_pin(GPIO_C, 13));
    }
}