#include "uart.h"
#include "../gcclib/stdint.h"

// LCG Parameters
#define A 1664525
#define C 1013904223
#define M 0xFFFFFFFF 

#define ARM_TIMER_BASE 0x20003000 // This is for Raspberry Pi 1. You'd need to change this for other versions.

#define SYSTEM_TIMER_COUNTER_LOW (*(volatile unsigned int *)0x3F003004)


void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);
int get_current_time();
void srand_custom(uint32_t s);
uint32_t rand(void);
uint32_t rand_range(uint32_t min_num, uint32_t max_num);
