#ifndef INTER_DRIVER_H
#def INTER_DRIVER_H

#include <stdint.h>

uint8_t store_read;

void PORTA_IRQHandler();
uint8_t pull_read();

#endif