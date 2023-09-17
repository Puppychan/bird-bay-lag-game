#include "mylib.h"

// for random number generator
static uint32_t current_seed = 123456789;  // A seed to start

/* Function to wait for some msec: the program will stop there */
void wait_msec(unsigned int n) {
    register unsigned long f, t, r, expiredTime;

    // Get the current counter frequency (Hz)
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));

    // Read the current counter value
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));

    // Calculate expire value for counter
    expiredTime = t + (f * n) / 1000;
    do {
        asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    } while (r < expiredTime);
}


/* Function to start a timer (set = 1) or wait for it to expire (set = 0) */
void set_wait_timer(int set, unsigned int msVal) {
    // set = 1: Sets the timer, calculates when the delay should expire, but then returns immediately without waiting.
    // set = 0: Waits (or blocks) until the previously set time has expired.
    static unsigned long expiredTime = 0; //declare static to keep value
    register unsigned long r, f, t;

    if (set) { /* SET TIMER */
        // Get the current counter frequency (Hz)
        asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));

        // Read the current counter
        asm volatile ("mrs %0, cntpct_el0" : "=r"(t));

        // Calculate expired time:
        expiredTime = t + (f * msVal) / 1000;
    }
    else { /* WAIT FOR TIMER TO EXPIRE */
        do {
            asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
        } while (r < expiredTime);
    }
}

int get_current_time() {
    register unsigned long r;
    asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    return r;
}

// https://stackoverflow.com/questions/6417113/c-custom-random-function
// https://cplusplus.com/reference/cstdlib/srand/
// Initialize the random number generator with a seed
void srand_custom(uint32_t seed) {
    current_seed = seed;
}

// Get a pseudo-random number
uint32_t rand(void) {
    current_seed = (A * current_seed + C) % M;
    return current_seed;
}

uint32_t rand_range(uint32_t min_num, uint32_t max_num) {
    if (min_num > max_num) {
        // Swap them if out of order
        uint32_t temp = min_num;
        min_num = max_num;
        max_num = temp;
    }

    uint32_t range = max_num - min_num + 1;

    return min_num + (rand() % range);
}

