#include "io.h"
#include "../common/defines.h"
#include "stdint.h"
#include "stm32l4xx.h"

/*
- Use the bit pattern of the port enums assigned to the
io_e pins to get their port and pin numbers
- The pin number is represented by the last 4 bits of the bits (15 is the largest pin no)
- The port number is represented by the 4 bits directly before the 4 pin bits
*/
#define IO_PORT_OFFSET (4U)
#define IO_PORT_MASK (0xFu << IO_PORT_OFFSET)
#define IO_PIN_MASK (0xFu)

#define IO_PORT_CNT (3U)
#define IO_PIN_PER_PORT_CNT (16U)

static inline uint8_t io_get_port(io_e io)
{
    return (io & IO_PORT_MASK) >> IO_PORT_OFFSET;
}
static inline uint8_t io_get_pin_idx(io_e io)
{
    return (io & IO_PIN_MASK);
}
/*- Array of GPIO ports, the ports are defined as struct pointers in the header files
  - Used an array of the ports to allow for cleaner code and no switch statments
  - Added only 3 ports since only A,B and C are being used in the sumo bot*/
static GPIO_TypeDef *const gpio_port_regs[IO_PORT_CNT] = { GPIOA, GPIOB, GPIOC };

void io_configure(io_e io, const struct io_config *config)
{
    io_port_init(io);
    io_set_mode(io, config->mode);
    io_set_output_type(io);
    io_set_pupd(io, config->pupd); // no pupd for output
    if (config->mode != IO_MODE_INPUT) {
        io_set_output_speed(io, config->speed);
    }
}
void io_port_init(io_e io)
{
    const uint8_t port = io_get_port(io);

    RCC->AHB2ENR |= (0x1 << port);
}

void io_set_mode(io_e io, io_mode_e mode)
{

    const uint8_t pin = io_get_pin_idx(io);
    const uint8_t port = io_get_port(io);

    GPIO_TypeDef *GPIO = gpio_port_regs[port];

    GPIO->MODER &= ~(0x3 << (2 * pin));
    GPIO->MODER |= (mode << (2 * pin));
};

void io_set_output_type(io_e io) // always set output type as push pull
{
    const uint8_t pin = io_get_pin_idx(io);
    const uint8_t port = io_get_port(io);

    GPIO_TypeDef *GPIO = gpio_port_regs[port];
    GPIO->OTYPER &= ~(0x1 << pin);
}
void io_set_pupd(io_e io, io_pupd_e pupd)
{
    const uint8_t pin = io_get_pin_idx(io);
    const uint8_t port = io_get_port(io);

    GPIO_TypeDef *GPIO = gpio_port_regs[port];
    GPIO->PUPDR &= ~(0x3 << (2 * pin));
    GPIO->PUPDR |= (pupd << (2 * pin));
}
void io_set_output_speed(io_e io, io_ouput_speed_e speed)
{
    const uint8_t pin = io_get_pin_idx(io);
    const uint8_t port = io_get_port(io);

    GPIO_TypeDef *GPIO = gpio_port_regs[port];
    GPIO->OSPEEDR &= ~(0x3 << (2 * pin));
    GPIO->OSPEEDR |= (speed << (2 * pin));
}
void io_set_output(io_e io, io_out_e out)
{
    const uint8_t pin = io_get_pin_idx(io);
    const uint8_t port = io_get_port(io);

    GPIO_TypeDef *GPIO = gpio_port_regs[port];

    switch (out) {
    case IO_OUT_HIGH:
        GPIO->ODR |= (0x1 << pin);
        break;
    case IO_OUT_LOW:
        GPIO->ODR &= ~(0x1 << pin);
        break;
    }
}

io_in_e io_get_input(io_e io)
{
    const uint8_t pin = io_get_pin_idx(io);
    const uint8_t port = io_get_port(io);

    const GPIO_TypeDef *GPIO = gpio_port_regs[port];
    const uint8_t input = GPIO->IDR & (0x1 << pin);
    return input ? IO_IN_HIGH : IO_IN_LOW;
}
