#include "string.h"

int str_compare(const char* str1, const char* str2) {
    // compare two strings
    // function returns 0 if strings are equal

    // loop through each character in the strings
    // until reach the end of the strings
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    // return the ASCII difference after converting char* to unsigned char*
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}