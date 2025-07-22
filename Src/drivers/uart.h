#ifndef UART_H
#define UART_H
/*Uart driver to print messages to the terminal to aid in debugging*/
void uart_init(void);
void uart_putchar_polling(char c);
void _putchar(char c);
#endif // UART_H
