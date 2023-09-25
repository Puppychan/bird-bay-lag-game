#include "uart.h"
#include "../gcclib/stddef.h"
#include "../gcclib/stdint.h"

// LCG Parameters
#define A 1664525
#define C 1013904223
#define M 0xFFFFFFFF 

void srand_custom(uint32_t s);
uint32_t rand(void);
uint32_t rand_range(uint32_t min_num, uint32_t max_num);

void welcomeMessage();
void clear();
void displayPrompt();
void wait_msec(unsigned int n);
void set_wait_timer(int set, unsigned int msVal);
int get_current_time();
void srand_custom(uint32_t s);
uint32_t rand(void);
uint32_t rand_range(uint32_t min_num, uint32_t max_num);

int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, int n);
int strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char* strtok(char* str, const char* delimiters);
void to_upper(char *str);

void reverse(char str[], int length);
char* citoa(int num, char* str, int base);