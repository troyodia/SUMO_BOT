#include "assert_handler.h"
#include "defines.h"
#include "stm32l4xx.h"

#define BREAKPOINT __asm volatile("bkpt #0");

void assert_handler(void)
{
    BREAKPOINT

    /* Accessing registers directly to config TEST LED to prevent
    calling functions that have assertions, this prevents recursive assertions*/
    RCC->AHB2ENR |= 0x1;

    GPIOA->MODER &= ~(0x3 << (2 * 5));
    GPIOA->MODER |= (0x1 << (2 * 5));
    GPIOA->OTYPER &= ~(0x1 << 5);
    GPIOA->OSPEEDR &= ~(0x3 << (2 * 5));
    GPIOA->OSPEEDR |= (0x3 << (2 * 5));

    volatile int j;
    while (1) {
        GPIOA->ODR ^= (0x1 << 5);
        BUSY_WAIT_ms(120)
    };
}