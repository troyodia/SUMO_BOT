#include "mcu_init.h"
#include "io.h"
#include "stm32l4xx.h"

void mcu_init(void)
{
    io_init();
}