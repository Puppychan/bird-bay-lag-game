// -----------------------------------uart.c -------------------------------------

#include "uart.h"

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
	register unsigned int r;

	/* initialize UART */
	*AUX_ENABLE |= 1;	// enable UART1, AUX mini uart (AUXENB)
	*AUX_MU_CNTL = 0;	// stop transmitter and receiver
	*AUX_MU_LCR = 3;	// 8-bit mode (also enable bit 1 to be used for RBP3)
	*AUX_MU_MCR = 0;	// RTS (request to send)
	*AUX_MU_IER = 0;	// disable interrupts
	*AUX_MU_IIR = 0xc6; // clear FIFOs
	*AUX_MU_BAUD = 270; // 115200 baud   (system_clk_freq/(baud_rate*8) - 1)

	/* map UART1 to GPIO pins */
	r = *GPFSEL1;
	r &= ~((7 << 12) | (7 << 15)); // Clear bits 12-17 (gpio14, gpio15)
	r |= (2 << 12) | (2 << 15);	   // Set value 2 (select ALT5: UART1)
	*GPFSEL1 = r;

	/* enable GPIO 14, 15 */
	*GPPUD = 0; // No pull up/down control
	r = 150;
	while (r--)
	{
		asm volatile("nop");
	}									// waiting 150 cycles
	*GPPUDCLK0 = (1 << 14) | (1 << 15); // enable clock for GPIO 14, 15
	r = 150;
	while (r--)
	{
		asm volatile("nop");
	}				// waiting 150 cycles
	*GPPUDCLK0 = 0; // flush GPIO setup

	*AUX_MU_CNTL = 3; // Enable transmitter and receiver (Tx, Rx)
}

/**
 * Send a character
 */
void uart_sendc(unsigned char c)
{
	/* wait until transmitter is empty */
	do
	{
		asm volatile("nop");
	} while (!(*AUX_MU_LSR & 0x20));

	/* write the character to the buffer */
	*AUX_MU_IO = c;
}

/**
 * Receive a character
 */
char uart_getc()
{
	char c;

	/* wait until data is ready (one symbol) */
	do {
		asm volatile("nop");
	} while ( !(*AUX_MU_LSR & 0x01) );

	/* read it and return */
	c = (char)(*AUX_MU_IO);

	/* convert carriage return to newline */
	return (c == '\r' ? '\n' : c);
}

/**
 * Display a string
 */
void uart_puts(char *s)
{
	while (*s)
	{
		/* convert newline to carriage return + newline */
		if (*s == '\n')
			uart_sendc('\r');
		uart_sendc(*s++);
	}
}

/**
 * Display a binary value in hexadecimal
 */
void uart_hex(unsigned int d)
{
	unsigned int n;
	int c;

	uart_puts("0x");
	for (c = 28; c >= 0; c = c - 4)
	{
		// Get highest 4-bit nibble
		n = (d >> c) & 0xF;

		// 0-9 => '0'-'9', 10-15 => 'A'-'F'
		n += (n > 9) ? (-10 + 'A') : '0';
		uart_sendc(n);
	}
}

/**
 * Display a value in decimal by
 */
void uart_dec(int num)
{
	char str[33] = "";
	int i, rem, len = 0, n;

    n = num;
    while (n != 0){
        len++;
        n /= 10;
    }

    if (num == 0)
    	len = 1;

    for (i = 0; i < len; i++){
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';

    uart_puts(str);
}

//Check if the user has just inputted a new key
unsigned int uart_isReadByteReady(){
	return (*AUX_MU_LSR & 0x01);
}


/* New function: Check and return if no new character, don't wait */
unsigned char getUart(){
    unsigned char ch = 0;
    if (uart_isReadByteReady())
    	ch = uart_getc();
    return ch;
}


/* Function to wait for some msec: the program will stop there */
void wait_msec(unsigned int n) {
	// 100000: 0.1s = 100ms
	// 
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