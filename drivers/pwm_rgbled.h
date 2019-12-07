/*
Name: James Medici
Date: 11/28/19

Description:
Driver for tri-color led on Kinetis Board with PWM
*/

#ifndef PWM_RGBLED_H
#define PWM_RGBLED_H

#include <stdint.h>

#define PWM_ON_LEVEL 0xFF
#define PWM_OFF_LEVEL 0x00

#define PWM_MAX_LEVEL (PWM_ON_LEVEL*16)

/* 
void initialize_pwm_red_led();
void initialize_pwm_green_led();
void initialize_pwm_blue_led();
void initialize_pwm(); */

void initialize_pwm_rgbled();

void set_pwm_red_level( uint8_t level );
void set_pwm_green_level( uint8_t level );
void set_pwm_blue_level( uint8_t level );

void turn_on_pwm_red_led();
void turn_on_pwm_green_led();
void turn_on_pwm_blue_led();

void turn_off_pwm_red_led();
void turn_off_pwm_green_led();
void turn_off_pwm_blue_led();

void set_pwm_rgbled_levels_to( uint8_t red, uint8_t green, uint8_t blue);

enum COLOR_TYPE {BLACK, WHITE, CYAN, MAGENTA, YELLOW, RED, GREEN, BLUE, OFF};
void set_pwm_rgbled_color_to(enum COLOR_TYPE color);
void turn_off_pwm_led();  // set led to BLACK

#endif