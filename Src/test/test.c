#include "../drivers/io.h"
#include "../drivers/mcu_init.h"
#include "../common/assert_handler.h"
#include "../common/trace.h"
#include "../drivers/led.h"
#include "../common/defines.h"
#include "../drivers/uart.h"
#include "../drivers/ir_remote.h"
static const io_e io_pins[] = { IO_I2C_SDA,           IO_I2C_SCL,
                                IO_LD_FRONT_LEFT,     IO_LD_BACK_LEFT,
                                IO_UART_TX,           IO_UART_RX,
                                IO_LD_FRONT_RIGHT,    IO_XSHUT_LEFT,
                                IO_XSHUT_FRONT_LEFT,  IO_XSHUT_RIGHT,
                                IO_XSHUT_FRONT_RIGHT, IO_XSHUT_FRONT,
                                IO_LD_BACK_RIGHT,     IO_RANGE_SENSOR_INT_FRONT,
                                IO_MOTOR_LEFT_CH1,    IO_MOTOR_LEFT_CH2,
                                IO_MOTOR_RIGHT_CH1,   IO_MOTOR_RIGHT_CH2,
                                IO_MOTOR_PWM_LEFT,    IO_MOTOR_PWM_RIGHT,
                                IO_IR_REMOTE,         IO_TEST_LED };
static void test_setup(void)
{
    mcu_init();
}
SUPPRESS_UNUSED
static void test_assert(void)
{
    test_setup();
    ASSERT(0);
}

SUPPRESS_UNUSED
static void test_blink_led(void)
{
    test_setup();
    led_init();
    volatile int j;
    led_state_e led_state = LED_STATE_OFF;
    while (1) {
        led_state = (led_state == LED_STATE_OFF) ? LED_STATE_ON : LED_STATE_OFF;
        led_set(LED_TEST, led_state);
        BUSY_WAIT_ms(80)
    }
}
SUPPRESS_UNUSED
static void test_uart_interrupt(void)
{
    test_setup();
    uart_init();
    volatile int j;
    while (1) {
        // printf("Hello boy %d\n", 20);
        _putchar('h');
        _putchar('h');
        _putchar('h');
        _putchar('h');
        _putchar('\n');
        BUSY_WAIT_ms(60);
    }
}
SUPPRESS_UNUSED
static void test_trace(void)
{
    test_setup();
    trace_init();
    volatile int j;
    while (1) {
        TRACE("TEST TRACE %d", 1);
        BUSY_WAIT_ms(60);
    }
}
SUPPRESS_UNUSED
static void test_nucleo_board_io_pins_output(void)
{
    test_setup();

    const struct io_config output_config = { .mode = IO_MODE_OUPUT,
                                             .pupd = IO_NO_PUPD,
                                             .speed = IO_SPEED_VERY_HIGH,
                                             .type = IO_TYPE_PP,
                                             .af = IO_AF_NONE };
    volatile unsigned int i;
    volatile unsigned int j;
    for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
        io_configure(io_pins[i], &output_config);
    }
    while (1) {
        for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
            io_set_output(io_pins[i], IO_OUT_HIGH);
            BUSY_WAIT_ms(80) io_set_output(io_pins[i], IO_OUT_LOW);
        }
    }
}
SUPPRESS_UNUSED
static void test_nucleo_board_io_pins_input(void)
{
    test_setup();
    led_init();

    const struct io_config input_config = { .mode = IO_MODE_INPUT,
                                            .pupd = IO_PORT_PU,
                                            .speed = IO_SPEED_LOW,
                                            .type = IO_TYPE_PP,
                                            .af = IO_AF_NONE };
    volatile unsigned int i;
    volatile unsigned int j;

    for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
        if (io_pins[i] == IO_TEST_LED) { // pin for nucleo board onboard led
            continue;
        } else {
            io_configure(io_pins[i], &input_config);
        }
    }
    // have to dotest this in sequence of the array
    for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
        if (io_pins[i] == IO_TEST_LED) { // pin for nucleo board onboard led
            continue;
        }
        led_set(LED_TEST, LED_STATE_ON);
        // Wait for user to connect pull down to escape the loop
        while (io_get_input(io_pins[i]) == IO_IN_HIGH) {
            BUSY_WAIT_ms(80)
        }
        led_set(LED_TEST, LED_STATE_OFF);
        // wait for user to disconnect pulldown for pin to go HIGH again and leave the loop
        while (io_get_input(io_pins[i]) == IO_IN_LOW) {
            BUSY_WAIT_ms(80)
        }
    }
    // led flashes after all input pins are tested in order
    while (1) {
        led_set(LED_TEST, LED_STATE_ON);
        BUSY_WAIT_ms(80)

            led_set(LED_TEST, LED_STATE_OFF);
        BUSY_WAIT_ms(80)
    }
}

SUPPRESS_UNUSED
static void io_PA_8_isr(void)
{
    led_set(LED_TEST, LED_STATE_ON);
}

SUPPRESS_UNUSED
static void io_PB_3_isr(void)
{
    led_set(LED_TEST, LED_STATE_OFF);
}

SUPPRESS_UNUSED
static void test_io_interrupt(void)
{
    test_setup();
    const struct io_config input_config = { .mode = IO_MODE_INPUT,
                                            .pupd = IO_PORT_PU,
                                            .speed = IO_SPEED_LOW,
                                            .type = IO_TYPE_PP,
                                            .af = IO_AF_NONE };
    io_configure((io_e)IO_PA_8, &input_config);
    io_configure((io_e)IO_PB_3, &input_config);
    led_init();

    io_interrupt_config((io_e)IO_PB_3, io_PB_3_isr, IO_FALLING_TRIGGER, IO_EXTI_N_3);
    io_enable_interrupt(IO_EXTI_3_LINE);
    io_interrupt_config((io_e)IO_PA_8, io_PA_8_isr, IO_FALLING_TRIGGER, IO_EXTI_N_0);
    io_enable_interrupt(IO_EXTI_9_5_LINE);

    while (1)

        ;
}
SUPPRESS_UNUSED
static void test_ir_remote(void)
{
    test_setup();
    trace_init();
    ir_remote_init();
    volatile int j = 0;
    while (1) {
        TRACE("Command: %s", ir_get_cmd_str(ir_remote_get_cmd()));
        BUSY_WAIT_ms(40)
    }
}
int main()
{
    TEST();
    ASSERT(0);
}