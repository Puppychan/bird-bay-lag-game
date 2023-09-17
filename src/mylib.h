#include "uart.h"
#include "../gcclib/stddef.h"
#define ARM_TIMER_BASE 0x20003000 // This is for Raspberry Pi 1. You'd need to change this for other versions.

#define SYSTEM_TIMER_COUNTER_LOW (*(volatile unsigned int *)0x3F003004)


void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);
void delay(unsigned int milliseconds);

void welcomeMessage();
void clear();
void displayPrompt();

int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, int n);
int strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char* strtok(char* str, const char* delimiters);
void to_upper(char *str);