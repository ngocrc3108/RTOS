#ifndef __RCC_H__
#define __RCC_H__

#include <stdint.h>

#define RCC_BASE 0x40021000

typedef struct rcc_t {
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
} rcc_t;

#define RCC ((rcc_t*)RCC_BASE)

#endif
