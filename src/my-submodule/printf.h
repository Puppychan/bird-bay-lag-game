
#include "../gcclib/stddef.h"
#include "../gcclib/stdint.h"
#include "../gcclib/stdarg.h"

#include "uart.h"
#define MAX_PRINT_SIZE 256

// helper functions
int get_printf_width(char **string);
char get_printf_zero_flag(char **string);
void copy_to_buffer(char *src, char *buffer, int *index, int start, int width, char zero_flag);

// printf format functions
int printf_char(char c, char *temp_buffer);
void printf_string(char *s, int width, char *buffer, int *index);
int printf_decimal(int x, char *temp_buffer, int temp_index);
int printf_hex(unsigned int x, char *temp_buffer);
int printf_float(double num, int precision, char *temp_buffer);

// printf function
void printf(char *string, ...);

// demo function
void printf_demo();