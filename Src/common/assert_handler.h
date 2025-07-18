#ifndef ASSERT_HANDLER_H
/* Assert on microcontroller to turn off motors during a fault*/
#define ASSERT(expression)                                                                         \
    do {                                                                                           \
        if (!(expression)) {                                                                       \
            assert_handler();                                                                      \
        }                                                                                          \
    } while (0)
#define ASSERT_INTERRUPT(expression)                                                               \
    do {                                                                                           \
        if (!(expression)) {                                                                       \
            while (1)                                                                              \
                ;                                                                                  \
        }                                                                                          \
    } while (0)

void assert_handler(void);

#endif // ASSERT_HANDLER_H