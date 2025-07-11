#ifndef DEFINES_H
#define DEFINES_H
#define UNUSED(x) (void)(x)
#define SUPPRESS_UNUSED __attribute__((unused))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

// STM32L3 runs at default 4MHz
#define CLOCK_FREQ_4MZ (4000000U)
#define CLOCK_FREQ_PER_ms (CLOCK_FREQ_4MZ / 1000U)
#define BUSY_WAIT_ms(delay_ms)                                                                     \
    for (j = (delay_ms * CLOCK_FREQ_PER_ms); j > 0; j--) {                                         \
    }; // takes the count for how long you want to delay
#endif