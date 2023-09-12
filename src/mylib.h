#include "uart.h"
#define ARM_TIMER_BASE 0x20003000 // This is for Raspberry Pi 1. You'd need to change this for other versions.

#define SYSTEM_TIMER_COUNTER_LOW (*(volatile unsigned int *)0x3F003004)


void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);
void delay(unsigned int milliseconds);
