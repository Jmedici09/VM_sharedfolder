/*
Name: James Medici & Jeffery Lieberman
Date: 12/10/19

Description:
*put description here*

LIBS="copwdt.o systick.o pwm_rgbled.o sw1.o i2c0.o rgbled.o" make Final.srec
cp Final.srec /media/student/FRDM-KL25Z/

*/
#include <copwdt.h>
#include <systick.h>
#include <pwm_rgbled.h>
#include <sw1.h>
#include <i2c0.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include <stdbool.h>

#define DEVICE (0x1D<<1) 

void PORTA_IRQHandler();

uint8_t polled_x_value;
uint8_t current_x_value;

void main()
{
	__disable_irq();
	initialize_copwdt();
	initialize_systick();
	initialize_pwm_rgbled();
	initialize_sw1_with_interrupts();
	__enable_irq();
	
	
	i2c0_write_byte( DEVICE, 0x2a, 0x01);
	
	turn_on_pwm_green_led();
	set_pwm_blue_level( 128 );
	while(1)
	{
		__asm("wfi");
		if( !systick_has_fired() )
				continue;
			
		//loop body	
		
		polled_x_value = i2c0_read_byte( DEVICE , 0x01);
		
		set_pwm_red_level( current_x_value );
		
		
			
		feed_the_watchdog();
	}
}

void PORTA_IRQHandler(){
	current_x_value = polled_x_value;
	
}