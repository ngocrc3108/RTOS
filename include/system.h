#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define SRAM_START_ADDRESS 0x20000000
#define SRAM_SIZE 20 * 1024

/* get symbol address (value) by &, the type here does not matter */
extern void* __data_start_address;
extern void* __data_size;
extern void* __bss_start_address;
extern void* __bss_size;
extern void* __heap_start_address;

#endif