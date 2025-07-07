#include "./drivers/io.h"
#include "./drivers/mcu_init.h"
static void test_setup(void)
{
    mcu_init();
}
static void blink_test_led()
{
    test_setup();
    // const struct io_config led_config = {
    //     .mode = IO_MODE_OUPUT, .pupd = IO_NO_PUPD, .speed = IO_SPEED_LOW, .type = IO_TYPE_PP
    // };
    // io_configure(IO_TEST_LED, &led_config);

    // volatile unsigned int i;
    // io_out_e out = IO_OUT_LOW;

    while (1) {
        // out = (out == IO_OUT_LOW) ? IO_OUT_HIGH : IO_OUT_LOW;
        io_set_output(IO_TEST_LED, IO_OUT_HIGH);
        // for (i = 100000; i > 0; i--) { } // delay
    }
}


// static void test_nucleo_board_io_pins_output(void)
// {
//     const struct io_config output_config = { .mode = IO_MODE_OUPUT,
//                                        .pupd = IO_NO_PUPD,
//                                        .speed = IO_SPEED_VERY_HIGH ,.type =IO_TYPE_PP};
//     volatile unsigned int i;
//     volatile unsigned int j;
//     for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
//         io_configure(io_pins[i], &output_config);
//     }
//     while (1) {
//         for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
//             io_set_output(io_pins[i], IO_OUT_HIGH);
//             for (j = 10000; j > 0; j--) { }; // delay
//             io_set_output(io_pins[i], IO_OUT_LOW);
//         }
//     }
// }
// static void test_nucleo_board_io_pins_input(void)
// {
//     const struct io_config led_config = {
//         .mode = IO_MODE_OUPUT, .pupd = IO_NO_PUPD, .speed = IO_SPEED_VERY_HIGH, .type =
//         IO_TYPE_PP
//     };
//     const struct io_config input_config = {
//         .mode = IO_MODE_INPUT, .pupd = IO_PORT_PU, .speed = IO_SPEED_LOW, .type = IO_TYPE_PP
//     };
//     volatile unsigned int i;
//     volatile unsigned int j;
//     const io_e io_pins[] = { IO_I2C_SDA,           IO_I2C_SCL,
//                              IO_LD_FRONT_LEFT,     IO_LD_BACK_LEFT,
//                              IO_UART_TX,           IO_UART_RX,
//                              IO_LD_FRONT_RIGHT,    IO_XSHUT_LEFT,
//                              IO_XSHUT_FRONT_LEFT,  IO_XSHUT_RIGHT,
//                              IO_XSHUT_FRONT_RIGHT, IO_XSHUT_FRONT,
//                              IO_LD_BACK_RIGHT,     IO_RANGE_SENSOR_INT_FRONT,
//                              IO_MOTOR_LEFT_CH1,    IO_MOTOR_LEFT_CH2,
//                              IO_MOTOR_RIGHT_CH1,   IO_MOTOR_RIGHT_CH2,
//                              IO_MOTOR_PWM_LEFT,    IO_MOTOR_PWM_RIGHT,
//                              IO_IR_REMOTE,         IO_TEST_LED };
//     for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
//         if (io_pins[i] == IO_TEST_LED) { // pin for nucleo board onboard led
//             io_configure(io_pins[i], &led_config);
//         } else {
//             io_configure(io_pins[i], &input_config);
//         }
//     }
//     // have to dotest this in sequence of the array
//     for (i = 0; i < sizeof(io_pins) / sizeof(io_pins[0]); i++) {
//         if (io_pins[i] == IO_TEST_LED) { // pin for nucleo board onboard led
//             continue;
//         }
//         io_set_output(IO_TEST_LED, IO_OUT_HIGH);
//         // Wait for user to connect pull down to escape the loop
//         while (io_get_input(io_pins[i]) == IO_IN_HIGH) {
//             for (j = 10000; j > 0; j--) { }; // delay
//         }
//         io_set_output(IO_TEST_LED, IO_OUT_LOW);
//         // wait for user to disconnect pulldown for pin to go HIGH again and leave the loop
//         while (io_get_input(io_pins[i]) == IO_IN_LOW) {
//             for (j = 10000; j > 0; j--) { }; // delay
//         }
//     }
//     // led flashes after all input pins are tested in order
//     while (1) {
//         io_set_output(IO_TEST_LED, IO_OUT_HIGH);
//         for (j = 10000; j > 0; j--) { }; // delay
//         io_set_output(IO_TEST_LED, IO_OUT_LOW);
//         for (j = 200000; j > 0; j--) { }; // delay
//     }
// }
int main(void)
{
    blink_test_led();
    // test_nucleo_board_io_pins_output();
    // test_nucleo_board_io_pins_input();
    return 0;
}
