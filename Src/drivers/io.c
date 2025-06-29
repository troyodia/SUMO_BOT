#include "io.h"
#include "../common/defines.h"

void io_port_init(io_e io)
{
    UNUSED(io);
}

void io_set_mode(io_e io, io_mode_e mode)
{
    UNUSED(io);
    UNUSED(mode);
};

void io_set_output_type(io_e io, io_output_type_e output_type)
{
    UNUSED(io);
    UNUSED(output_type);
}
void io_set_pupd(io_e io, io_pupd_e pupd)
{
    UNUSED(io);
    UNUSED(pupd);
}
void io_set_output_speed(io_e io, io_ouput_speed_e speed)
{
    UNUSED(io);
    UNUSED(speed);
}
io_in_e io_get_input(io_e io)
{
    UNUSED(io);
    return IO_IN_HIGH;
}
