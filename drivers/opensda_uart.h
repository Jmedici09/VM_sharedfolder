#ifndef OPENSDA_UART_H
#define OPENSDA_UART_H

#include <stdbool.h>
#include <stdint.h>

// Use "minicom -s"
// "serial port setup"
// "A -  /dev/ttyACM0" // name of kinetis board

// "dmesg -w" command

void initialize_opensda_uart();
_Bool send_byte_to_opensda_uart( uint8_t data);
_Bool get_byte_from_opensda_uart( uint8_t *data);
_Bool opensda_uart_rx_ready();
_Bool opensda_uart_tx_ready();

void uart_blocking_send(char *payload);

#endif