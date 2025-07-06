#ifndef IO_H
#define IO_H
// ENUMS
typedef enum
{
    IO_PA_0,
    IO_PA_1,
    IO_PA_2,
    IO_PA_3,
    IO_PA_4,
    IO_PA_5,
    IO_PA_6,
    IO_PA_7,
    IO_PA_8,
    IO_PA_9,
    IO_PA_10,
    IO_PA_11,
    IO_PA_12,
    IO_PA_13,
    IO_PA_14,
    IO_PA_15,
    IO_PB_0,
    IO_PB_1,
    IO_PB_2,
    IO_PB_3,
    IO_PB_4,
    IO_PB_5,
    IO_PB_6,
    IO_PB_7,
    IO_PB_8,
    IO_PB_9,
    IO_PB_10,
    IO_PB_11,
    IO_PB_12,
    IO_PB_13,
    IO_PB_14,
    IO_PB_15,
    IO_PC_0,
    IO_PC_1,
    IO_PC_2,
    IO_PC_3,
    IO_PC_4,
    IO_PC_5,
    IO_PC_6,
    IO_PC_7,
    IO_PC_8,
    IO_PC_9,
    IO_PC_10,
    IO_PC_11,
    IO_PC_12,
    IO_PC_13,
    IO_PC_14,
    IO_PC_15,
    IO_PD_2 = 50,
    IO_PH_0 = 112,
    IO_PH_1
} io_ports_e;
typedef enum
{
    // PA
    IO_LD_FRONT_LEFT = IO_PA_0,
    IO_LD_BACK_LEFT = IO_PA_1,
    IO_UNUSED_1 = IO_PA_2,
    IO_UNUSED_2 = IO_PA_3,
    IO_LD_FRONT_RIGHT = IO_PA_4,
    IO_TEST_LED = IO_PA_5,
    IO_XSHUT_FRONT_LEFT = IO_PA_6,
    IO_XSHUT_RIGHT = IO_PA_7,
    IO_IR_REMOTE = IO_PA_8,
    IO_XSHUT_LEFT = IO_PA_9,
    IO_UNUSED_3 = IO_PA_10,
    IO_UNUSED_4 = IO_PA_11,
    IO_UNUSED_5 = IO_PA_12,
    IO_UNUSED_6 = IO_PA_13,
    IO_UNUSED_7 = IO_PA_14,
    IO_UNUSED_8 = IO_PA_15,
    // PB
    IO_LD_BACK_RIGHT = IO_PB_0,
    IO_RANGE_SENSOR_INT_FRONT = IO_PB_1,
    IO_UNUSED_9 = IO_PB_2,
    IO_UNUSED_10 = IO_PB_3,
    IO_UNUSED_11 = IO_PB_4,
    IO_UNUSED_12 = IO_PB_5,
    IO_UART_TX = IO_PB_6,
    IO_UART_RX = IO_PB_7,
    IO_UNUSED_13 = IO_PB_8,
    IO_UNUSED_14 = IO_PB_9,
    IO_MOTOR_LEFT_CH1 = IO_PB_10,
    IO_MOTOR_LEFT_CH2 = IO_PB_11,
    IO_MOTOR_RIGHT_CH1 = IO_PB_12,
    IO_MOTOR_RIGHT_CH2 = IO_PB_13,
    IO_UNUSED_15 = IO_PB_14,
    IO_UNUSED_16 = IO_PB_15,

    // PC
    IO_I2C_SCL = IO_PC_0,
    IO_I2C_SDA = IO_PC_1,
    IO_UNUSED_17 = IO_PC_2,
    IO_UNUSED_18 = IO_PC_3,
    IO_XSHUT_FRONT_RIGHT = IO_PC_4,
    IO_XSHUT_FRONT = IO_PC_5,
    IO_MOTOR_PWM_LEFT = IO_PC_6,
    IO_MOTOR_PWM_RIGHT = IO_PC_7,
    IO_UNUSED_19 = IO_PC_8,
    IO_UNUSED_20 = IO_PC_9,
    IO_UNUSED_21 = IO_PC_10,
    IO_UNUSED_22 = IO_PC_11,
    IO_UNUSED_23 = IO_PC_12,
    IO_UNUSED_24 = IO_PC_13,
    IO_UNUSED_25 = IO_PC_14,
    IO_UNUSED_26 = IO_PC_15,
    // PD
    IO_UNUSED_27 = IO_PD_2,
    // PH
    IO_UNUSED_28 = IO_PH_0,
    IO_UNUSED_29 = IO_PH_1,

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
typedef enum
{
    IO_OUT_LOW,
    IO_OUT_HIGH,
} io_out_e;
typedef enum
{
    IO_TYPE_PP, // push pull
    IO_TYPE_OD // open drain
} io_out_type_e;
// STRUCT
struct io_config
{
    io_mode_e mode;
    io_pupd_e pupd;
    io_ouput_speed_e speed;
    io_out_type_e type;
};

// FUNCTIONS
void io_init(void);
void io_configure(io_e io, const struct io_config *config);
void io_port_init(io_e io);
void io_set_mode(io_e io, io_mode_e mode);
void io_set_output_type(io_e io, io_out_type_e type);
void io_set_pupd(io_e io, io_pupd_e pupd);
void io_set_output_speed(io_e io, io_ouput_speed_e speed);
void io_set_output(io_e io, io_out_e out);
io_in_e io_get_input(io_e io);
#endif // IO_H