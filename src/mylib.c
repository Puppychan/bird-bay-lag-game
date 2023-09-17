#include "mylib.h"
#include "../gcclib/stddef.h"

/* Function to wait for some msec: the program will stop there */
void wait_msec(unsigned int n) {
    register unsigned long f, t, r, expiredTime;

    // Get the current counter frequency (Hz)
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));

    // Read the current counter value
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));

    // Calculate expire value for counter
    expiredTime = t + ((f / 1000) * n) / 1000;
    do {
        asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    } while (r < expiredTime);
}


/* Function to start a timer (set = 1) or wait for it to expire (set = 0) */
void set_wait_timer(int set, unsigned int msVal) {
    static unsigned long expiredTime = 0; //declare static to keep value
    register unsigned long r, f, t;

    if (set) { /* SET TIMER */
        // Get the current counter frequency (Hz)
        asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));

        // Read the current counter
        asm volatile ("mrs %0, cntpct_el0" : "=r"(t));

        // Calculate expired time:
        expiredTime = t + ((f / 1000) * msVal) / 1000;
    }
    else { /* WAIT FOR TIMER TO EXPIRE */
        do {
            asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
        } while (r < expiredTime);
    }
}
void delay(unsigned int milliseconds) {
    volatile unsigned int start_time = SYSTEM_TIMER_COUNTER_LOW;
    // Timer frequency is 1MHz, so wait for the count to go up by 1000 * milliseconds
    while (SYSTEM_TIMER_COUNTER_LOW - start_time < 1000 * milliseconds) {
        // Just wait
    }
}


void welcomeMessage()
{
    uart_puts("\n\n\n"); 
	//Basic font of ascii art
    uart_puts("\033[33md88888b d88888b d88888b d888888b .d888b.   j88D  .d888b.  .d88b.  \n");
	uart_puts("\033[33m88'     88'     88'     `~~88~~' VP  `8D  j8~88  88' `8D .8P  88. \n");
	uart_puts("\033[33m88ooooo 88ooooo 88ooooo    88       odD' j8' 88  `V8o88' 88  d'88 \n");
	uart_puts("\033[33m88~~~~~ 88~~~~~ 88~~~~~    88     .88'   V88888D    d8'  88 d' 88 \n");
	uart_puts("\033[33m88.     88.     88.        88    j88.        88    d8'   `88  d8' \n");
	uart_puts("\033[33mY88888P Y88888P Y88888P    YP    888888D     VP   d8'     `Y88P'  \n");
    uart_puts("\n");                                                                     
    uart_puts("\n");   
    uart_puts("\033[34md8888b.  .d8b.  d8888b. d88888b    .d88b.  .d8888.                \n");
	uart_puts("\033[34m88  `8D d8' `8b 88  `8D 88'       .8P  Y8. 88'  YP                \n");
	uart_puts("\033[34m88oooY' 88ooo88 88oobY' 88ooooo   88    88 `8bo.                  \n");
	uart_puts("\033[34m88~~~b. 88~~~88 88`8b   88~~~~~   88    88   `Y8b.                \n");
	uart_puts("\033[34m88   8D 88   88 88 `88. 88.       `8b  d8' db   8D                \n");
	uart_puts("\033[34mY8888P' YP   YP 88   YD Y88888P    `Y88P'  `8888Y'           \n");
    uart_puts("\n");     
    uart_puts("\033[37m     Developed by Group 13\n\n\n\n");
	uart_puts("\033[0m"); //Reset to default color
	displayPrompt();
}

void clear()
{
    uart_puts("\033[2J");
    uart_puts("\033[H");
}

void displayPrompt()
{
    uart_puts("MyOS> ");
}

int strcmp(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        i++;
    }
    // If one string is shorter than the other
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}

int strncmp(const char *str1, const char *str2, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Compare the characters
        if (str1[i] != str2[i])
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        // If we reached the end of either string, stop comparing
        if (str1[i] == '\0' || str2[i] == '\0')
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
    }
    //loop completes, the strings equal 'n' characters
    return 0;
}

int strlen(const char *str)
{
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char *strcpy(char *dest, const char *src)
{
    char *original_dest = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  // Null-terminate the destination string
    return original_dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    // If src has fewer than n characters, fill remainder of dest with null bytes
    for ( ; i < n; ++i)
    {
        dest[i] = '\0';
    }

    return dest;
}

char* strtok(char* str, const char* delimiters) {
    static char* next_token = 0;

    if (str) {
        next_token = str;
    }

    if (!next_token) {
        return 0;
    }

    char* current_token = next_token;

    while (*next_token) {
        char* d = (char*) delimiters;
        while (*d) {
            if (*next_token == *d) {
                *next_token = '\0';
                next_token++;
                return current_token;
            }
            d++;
        }
        next_token++;
    }

    return current_token;
}

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

