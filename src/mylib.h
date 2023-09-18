#include "uart.h"
#include "../gcclib/stddef.h"

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

void reverse(char str[], int length);
char* citoa(int num, char* str, int base);