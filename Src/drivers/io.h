#ifndef IO_H
#define IO_H
// ENUMS
typedef enum
{
    IO_I2C_SDA,
    IO_I2C_SCL,
    IO_LD_FRONT_LEFT,
    IO_LD_BACK_LEFT,
    IO_UART_TX,
    IO_UART_RX,
    IO_LD_FRONT_RIGHT,
    IO_XSHUT_LEFT,
    IO_XSHUT_FRONT_LEFT,
    IO_XSHUT_RIGHT,
    IO_XSHUT_FRONT_RIGHT,
    IO_XSHUT_FRONT,
    IO_LD_BACK_RIGHT,
    IO_RANGE_SENSOR_INT_FRONT,
    IO_MOTOR_LEFT_CH1,
    IO_MOTOR_LEFT_CH2,
    IO_MOTOR_RIGHT_CH1,
    IO_MOTOR_RIGHT_CH2,
    IO_MOTOR_PWM_LEFT,
    IO_MOTOR_PWM_RIGHT,
    IO_IR_REMOTE,
    IO_REST_LED
} io_e;

typedef enum
{
    IO_MODE_INPUT,
    IO_MODE_OUPUT,
    IO_MODE_ALTFN,
    IO_MODE_ANALOG
} io_mode_e;

typedef enum
{
    IO_OUTPUT_PP, // push-pull
    IO_OUTPUT_OD // open drain
} io_output_type_e;

typedef enum
{
    IO_NO_PUPD, // no pull up or pull down
    IO_PORT_PU, // pull up
    IO_PORT_PD, // pull down
    IO_RESERVED // reserved
} io_pupd_e;
typedef enum
{
    IO_SPEED_LOW,
    IO_SPEED_MEDIUM,
    IO_SPEED_HIGH,
    IO_SPEED_VERY_HIGH
} io_ouput_speed_e;
typedef enum
{
    IO_IN_LOW,
    IO_IN_HIGH,
} io_in_e;
// STRUCTS
// FUNCTIONS
void io_port_init(io_e io);
void io_set_mode(io_e io, io_mode_e mode);
void io_set_output_type(io_e io, io_output_type_e output_type);
void io_set_pupd(io_e io, io_pupd_e pupd);
void io_set_output_speed(io_e io, io_ouput_speed_e speed);
io_in_e io_get_input(io_e io);
#endif // IO_H