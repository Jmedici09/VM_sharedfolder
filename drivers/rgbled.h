/*
Name: James Medici
Date: 10/5/19

Description:
Driver for tri-color led on Kinetis Board
*/

#ifndef RGBLED_H
#define RGBLED_H

#include <MKL25Z4.h>
#include <stdbool.h>

void initialize_red_led();
void initialize_green_led();
void initialize_blue_led();

void initialize_rgbled(); 

/// Change LED state
void change_red_led_state_to(uint8_t led_state);
void change_green_led_state_to(uint8_t led_state);
void change_blue_led_state_to(uint8_t led_state);

void toggle_red_led();
void toggle_green_led();
void toggle_blue_led();

void turn_on_red_led();
void turn_on_green_led();
void turn_on_blue_led();

void turn_off_red_led();
void turn_off_green_led();
void turn_off_blue_led();

enum COLOR_TYPE {BLACK, WHITE, CYAN, MAGENTA, YELLOW, RED, GREEN, BLUE, OFF};
void set_led_to(enum COLOR_TYPE color);
void turn_off_led();  // set led to BLACK


/// Check LED state
_Bool red_led_is_on();
_Bool green_led_is_on();
_Bool blue_led_is_on();	

enum COLOR_TYPE current_led_color();
_Bool led_is(enum COLOR_TYPE); // check to see if led is the inputed color

#endif
