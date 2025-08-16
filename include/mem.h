#ifndef __MEM_H__
#define __MEM_H__

#include <stdint.h>

void* malloc(uint32_t len);
void* my_calloc(uint32_t len);
void free(void* address);

#endif