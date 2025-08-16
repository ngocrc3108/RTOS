#include "os.h"
#include "timer.h"
#include "rcc.h"
#include "system.h"
#include "mem.h"

#define OS_TIMER    TIM2

os_task_context_t* current_context;
os_task_t task_info[10];
static uint8_t task_info_count = 0;
static uint8_t current_task_index = 0;

os_task_context_t* os_find_next_task()
{
    current_task_index++;
    current_task_index %= task_info_count;
    current_context = &task_info[current_task_index].context;
    return current_context;
}

void os_add_task(uint32_t task_address, uint32_t stack_size)
{
    task_info[task_info_count].task_address = task_address;
    task_info[task_info_count].stack_size = stack_size;
    task_info_count++;
}

void os_start()
{
    /* tasks' stacks are allocated on heap */
    for(int i = 0; i < task_info_count; i++)
    {
        /* allocate (stack_size) bytes of memory on heap, then move stack address into the end of that memory since stack grows downward */
        /* stack must be word aligned - Use of 0b1101 as a register specifier - armv7-M architecture reference manual */
        const uint32_t aligned_stack_size = align_memory_size(task_info[i].stack_size);
        const uint32_t stack_address = (uint32_t)malloc(aligned_stack_size) + aligned_stack_size;

        task_info[i].context.SP = stack_address - 8*4;
        /* Pushes xPSR, PC, r0, r1, r2, r3, r12, and LR on selected stack. */
        /* the stack grows downward */
        ((uint32_t*)task_info[i].context.SP)[7] = 0x01000000; // xPSR
        ((uint32_t*)task_info[i].context.SP)[6] = task_info[i].task_address & 0xfffffffe; // PC
        ((uint32_t*)task_info[i].context.SP)[5] = 0xFFFFFFF9; // LR
        ((uint32_t*)task_info[i].context.SP)[4] = 0x00; // R12
        ((uint32_t*)task_info[i].context.SP)[3] = 0x00; // R3
        ((uint32_t*)task_info[i].context.SP)[2] = 0x00; // R2
        ((uint32_t*)task_info[i].context.SP)[1] = 0x00; // R1
        ((uint32_t*)task_info[i].context.SP)[0] = 0x00; // R0

        task_info[i].context.BASEPRI = 0x00;
        task_info[i].context.CONTROL = 0x00;
        task_info[i].context.FAULTMASK = 0x00;
        task_info[i].context.PRIMASK = 0x00;
    }

    current_task_index = 0;
    current_context = &task_info[current_task_index].context;
    
    // setup interrupt
    timer_init(OS_TIMER);
    timer_enable_interrupt(OS_TIMER);
    timer_start(OS_TIMER);

    __asm_os_start(task_info[current_task_index].task_address, task_info[current_task_index].context.SP + 8*4);
    while(1);
}