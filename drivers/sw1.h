/*
Name: James Medici
Date: 10/5/19

Description:
Driver for repurposed reset switch on Kinetis board
*/

#ifndef SW1_H
#define SW1_H

#include <MKL25Z4.h>
#include <stdbool.h>

#define SW1 20
#define debounce_time 10

void initialize_sw1();

_Bool sw1_is_pressed();
_Bool sw1_is_not_pressed();

void wait_until_sw1_pressed_then_released();
void wait_until_sw1_released_then_pressed();

#endif
