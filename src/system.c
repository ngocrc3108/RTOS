#include <stdint.h>
#include "gpio.h"
#include "system.h"
#include "os.h"

int main();
static void Default_handler(void);
static void Reset_handler() __attribute__((section (".reset_handler")));
static void NMI_handler(void);
static void HardFault_handler(void);
static void MemFault_handler(void);
static void BusFault_handler(void);
static void UsageFault_handler(void);

uint32_t vector_table[] __attribute__((section (".vector_table"))) = {
    (SRAM_START_ADDRESS + SRAM_SIZE),
    (uint32_t)(&Reset_handler),
    (uint32_t)(&NMI_handler),
    (uint32_t)(&HardFault_handler),
    (uint32_t)(&MemFault_handler),
    (uint32_t)(&BusFault_handler),
    (uint32_t)(&UsageFault_handler),
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
    (uint32_t)(&__asm_os_switch_context),
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

    for(uint64_t i = 0; i < (uint32_t)(&__bss_size); i++)
    {
        ((uint8_t*)&__bss_start_address)[i] = 0;
    }

    main();
}

void NMI_handler(void)
{
    while(1);
}

void HardFault_handler(void)
{
    while(1);
}

void MemFault_handler(void)
{
    while(1);
}

void BusFault_handler(void)
{
    while(1);
}

void UsageFault_handler(void)
{
    while(1);
}