#include "printf.h"

char get_printf_zero_flag(char** string) {
    // function to get zero flag
    // return ' ' if no zero flag
    char zero_flag = ' ';
    // check for zero flag
    if (**string == '0') {
        // if have zero flag -> set zero flag
        zero_flag = '0';
        // move to next character
        (*string)++;
    }
    return zero_flag;
}
int get_printf_width(char** string) {
    // function to get width
    int width = 0;
    // if content is not a number -> return 0
    while (**string >= '0' && **string <= '9') {
        // convert to int
        width = width * 10 + (**string - '0');
        (*string)++;
    }
    return width;
}
void copy_to_buffer(char* src, char* buffer, int* index, int start, int width, char zero_flag) {
    // function to copy temp_buffer to buffer
    // Add negative sign before 0 flag
    if (src[start + 1] == '-' && zero_flag == '0') {
        buffer[(*index)++] = '-';
        start++;
        width--;
    }
    // Validate whether need to add zero flag
    while (start >= MAX_PRINT_SIZE - width) {
        // Add zero flag if needed
        src[start--] = zero_flag;
    }

    // Add temp_buffer to buffer
    for (int i = start + 1; i < MAX_PRINT_SIZE; i++)
        buffer[(*index)++] = src[i];
}
int printf_char(char c, char* temp_buffer) {
    // function to convert char to string to display
    int temp_index = MAX_PRINT_SIZE - 1;
    // Add c to main string
    temp_buffer[temp_index--] = c;
    return temp_index;
}
void printf_string(char* s, int width, char* buffer, int* index) {
    // function to convert string to display

    // if s is null -> set s to "(null)"
    if (s == NULL) {
        s = "(null)";
    }

    // Init length of string
    int length = 0;
    // Init pointer to string
    char* p = s;
    // Get length of string
    while (*p != 0) {
        length++;
        p++;
    }

    // Add width to main string
    for (int i = 0; i < width - length; i++)
        buffer[(*index)++] = ' ';

    // Add s to main string
    while (*s != 0) {
        buffer[(*index)++] = *s;
        s++;
    }
}
int printf_decimal(int x, char* temp_buffer, int temp_index) {
    // function to convert decimal to string to display
    // validate whether x is negative
    int is_negative = 0;
    if (x < 0) {
        // convert to positive
        is_negative = 1;
        x = -x;
    }

    // Convert x to string
    do {
        // Convert each digit to character
        // % 10 to take the digit - + '0' to convert to ascii char
        temp_buffer[temp_index--] = (x % 10) + '0';
        // Divide by 10 to get next digit (remove the last digit)
        x /= 10;
    } while (x != 0);

    // Add negative sign if needed
    if (is_negative) {
        temp_buffer[temp_index--] = '-';
    }

    return temp_index;
}
int printf_hex(unsigned int x, char* temp_buffer) {
    // function to convert hex to string to display
    // Convert x to string
    int temp_index = MAX_PRINT_SIZE - 1;
    do {
        // take digit from right to left
        char digit = x % 16; // already converted to int (currently in int type)
        if (digit < 10)
            // if < 10 -> just convert to ascii char
            temp_buffer[temp_index] = digit + '0';
        else
            // if >= 10 -> convert to lowercase character
            // Eg: 13 -> 3 -> 'd'
            temp_buffer[temp_index] = digit - 10 + 'a';

        temp_index--;
        x /= 16;
    } while (x != 0);

    return temp_index;
}
int printf_float(double x, int precision, char* temp_buffer) {
    // function to convert float to string to display
    // Convert x to string
    // make sure loop through all digits (max number - 256)
    int temp_index = MAX_PRINT_SIZE - 1;

    // get decimal and fractional part
    int int_part = (int)x;
    double frac_part = x - int_part;
    if (frac_part < 0)
        frac_part = -frac_part;

    // generate the fractional part
    // if have precision only
    if (precision > 0) {
        // multiply by 10^precision to convert to integer
        for (int i = 0; i < precision; i++) {
            frac_part *= 10;
        }
        // convert to integer
        int frac_int = (int)frac_part;
        // print out the fractional part
        temp_index = printf_decimal(frac_int, temp_buffer, temp_index);
    }

    // if have precision -> print out '.'
    if (precision > 0)
        temp_buffer[temp_index--] = '.';

    //  Print the integer part
    temp_index = printf_decimal(int_part, temp_buffer, temp_index);
    return temp_index;
}


void printf(char* string, ...) {
    // va_list: type to hold information about variable arguments
    va_list ap;
    // va_start: initialize ap to the beginning of the variable argument list
    va_start(ap, string);
    // temp_buffer: store the temporary string
    char temp_buffer[MAX_PRINT_SIZE];
    // buffer: store the formated string
    char buffer[MAX_PRINT_SIZE];
    int buffer_index = 0;
    while (1) {
        // if end of string -> stop
        if (*string == 0)
            break;
        // if % -> format
        if (*string == '%') {
            string++;

            // Check for zero flag
            char zero_flag = get_printf_zero_flag(&string);
            // check for width
            int width = get_printf_width(&string);

            // get precision
            int precision = 6;
            if (*string == '.') {
                string++;
                precision = get_printf_width(&string);
            }
            // use for validating whether temp_buffer has been copied to buffer
            // if temp_index == -1 -> temp_buffer has not been copied to buffer
            int temp_index = -1;

            switch (*string) {
            case 'c': // character format
                // reset zero flag
                zero_flag = ' ';
                string++;
                // va_arg: retrieve the next argument
                char c = (char)va_arg(ap, int);
                temp_index = printf_char(c, temp_buffer);
                break;
            case 's': // string format
                // reset zero flag
                zero_flag = ' ';
                string++;
                // va_arg: retrieve the next argument
                char* s = va_arg(ap, char*);
                printf_string(s, width, buffer, &buffer_index);
                break;
            case 'd': // decimal format
                string++;
                // va_arg: retrieve the next argument
                int x_decimal = va_arg(ap, int);
                temp_index = printf_decimal(x_decimal, temp_buffer, MAX_PRINT_SIZE - 1);
                break;
            case 'x': // hexa format
                string++;
                // va_arg: retrieve the next argument
                // Hex is displayed as 2 complement number (negative number is displayed as 2 complement - 32 bit number)
                unsigned int x_unsigned = va_arg(ap, unsigned int);
                temp_index = printf_hex(x_unsigned, temp_buffer);
                break;
            case 'f': // float format
                string++;
                // va_arg: retrieve the next argument
                double x_float = va_arg(ap, double);
                // printf_float(x_float, width, zero_flag, precision, buffer, &buffer_index);
                temp_index = printf_float(x_float, precision, temp_buffer);
                break;
            case '%': // print out %
                string++;
                buffer[buffer_index++] = '%';
                break;
            default: // print out the character
                buffer[buffer_index++] = *string;
                string++;
                break;
            }
            // copy temp_buffer to buffer if have not been copied
            if (temp_index != -1) {
                copy_to_buffer(temp_buffer, buffer, &buffer_index, temp_index, width, zero_flag);
            }

        }
        // else -> print out the character
        else {
            buffer[buffer_index++] = *string;
            string++;
        }
        // if overflow -> stop
        if (buffer_index == MAX_PRINT_SIZE - 1)
            break;
    }
    buffer[buffer_index] = '\0'; // Ensure null termination

    // va_end: clean up the variable argument list
    va_end(ap);
    // Print out formated string
    uart_puts(buffer);
}

void printf_demo() {
    // set up serial console
    int posNumber = 12345;
    char character = 'A';
    char* string = "Hello, World!";
    unsigned int hexValue = 0x1234ABCD;
    int hexValue1 = 0x0;
    int hexValue2 = 0x1;
    int hexValue3 = 0x10;
    int hexValue4 = 0x100;
    int hexValue5 = 0x12345678;
    int hexValue6 = 0xABCDEF;
    int hexValue7 = 0xabcdef;
    int hexValue8 = -0x12345678;
    int hexValue9 = 11259375;
    int negNumber = -30; 

    printf("This is a number: %d\n", posNumber);
    printf("This is a number: %d\n", negNumber);
    printf("This is a number 0: %0d\n", negNumber);
    printf("This is a number 4: %4d\n", negNumber);
    printf("This is a number 04: %04d\n", negNumber);
    printf("This is a number: %02d\n", negNumber);

    printf("\n HEXADECIMAL \n");
    printf("This is hex value 0: %x\n", hexValue1);
    printf("This is hex value 1: %x\n", hexValue2);
    printf("This is hex value 16: %x\n", hexValue3);
    printf("This is hex value 256: %x\n", hexValue4);
    printf("This is hex value 305419896: %x\n", hexValue5);
    printf("This is hex value 0xABCDEF: %x\n", hexValue6);
    printf("This is hex value 0xabcdef: %x\n", hexValue7);
    printf("This is negative hex value -305419896: %x\n", hexValue8);
    printf("This is hex value 11259375: %x\n", hexValue9);
    printf("This is a hex value: %x %\n", hexValue);

    printf("\n CHARACTERS \n");
    printf("This is a character: %c\n", character);
    printf("This is a character 4: %4c\n", character);
    printf("This is a character 04: %04c\n", character);
    printf("This is a character .5: %.5c\n", character);

    printf("\n STRING \n");
    printf("This is a string: %s\n", string);
    printf("This is a string 20: %20s\n", string);
    printf("This is a string 4: %4s\n", string);
    printf("This is a string 04: %04s\n", string);
    printf("This is a string .5: %.5s\n", string);

    printf("\n");
    printf("This is a number 4: %4d\n", 30);
    printf("This is a number 000: %000d\n", 30);
    printf("This is a number 00: %00d\n", 30);
    printf("This is a number 0: %0d\n", 30);

    printf("This is a number 04: %04d\n", 30);
    printf("This is a number 03: %03d\n", 30);
    printf("This is a number 003: %003d\n", 30);
    printf("This is a number 02: %02d\n", 30);
    printf("This is a number 1: %1d\n", 30);
    printf("\n");

    printf("This is hex 10 flag: %010x\n", -30);
    printf("This is hex 03 flag: %03x\n", 0x1a);
    printf("This is hex 0 flag: %0x\n", 0x1a);
    printf("This is hex 3 flag: %3x\n", 0x1a);
    printf("\n");

    printf("\n FLOAT \n");
    printf("This is a float: %f\n", 123.456);
    printf("This is a float 02: %02f\n", 30.5);
    printf("This is a float 010: %010f\n", 30.5);
    printf("This is a float 010.2: %010.2f\n", 123.456);
    printf("This is a float 10.2: %10.2f\n", 123.456);
    printf("This is a float .: %.f\n", 123.456);
    printf("\n NEGATIVE FLOAT \n");
    printf("This is a negative float 02: %02f\n", -30.5);
    printf("This is a negative float 010: %010f\n", -30.5);
    printf("This is a negative float 010.2: %010.2f\n", -123.456);
    printf("This is a negative float 10.2: %10.2f\n", -123.456);
    printf("This is a negative float .: %.f\n", -123.456);
    printf("\n");

    // Null string
    printf("This is a null string: %s\n", NULL);

    // Testing negative value in hexadecimal format (it will be printed in two's complement form)
    printf("Negative number in int: %d, in hex: %x - %%\n", negNumber, negNumber);
}