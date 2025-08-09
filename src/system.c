#include <stdint.h>
#include "gpio.h"

#define SRAM_START_ADDRESS 0x20000000

/* get symbol address (value) by &, the type here does not matter */
extern void* __data_start_address;
extern void* __data_size;

int main();
static void Default_handler(void);
static void Reset_handler() __attribute__((section (".reset_handler")));

uint32_t vector_table[] __attribute__((section (".vector_table"))) = {
    (0x20000000 + 20 * 1024),
    (uint32_t)(&Reset_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    0,
    0,
    0,
    0,
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    0,
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
    (uint32_t)(&Default_handler),
};

void Default_handler(void)
{
    while(1);
}

void Reset_handler()
{
    for(uint64_t i = 0; i < (uint32_t)(&__data_size); i++)
    {
        ((uint8_t*)SRAM_START_ADDRESS)[i] = ((uint8_t*)&__data_start_address)[i];
    }

    main();
}