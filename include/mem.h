#ifndef __MEM_H__
#define __MEM_H__

#include <stdint.h>

void* malloc(uint32_t size);
void* calloc(uint32_t nmemb, uint32_t size);
void free(void* address);

static inline uint32_t align_memory_size(uint32_t size)
{
    return (size & 0xfffffffc) + 4;
}

#endif