/*
Name: James Medici
Date: *date here*

Description:
*put description here*
*/
#include <copwdt.h>
#include <systick.h>
#include <pwm_rgbled.h>
#include <sw1.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include <stdbool.h>


// Should I add startup and loop functions? 
// something which happens once, and one that happens for the rest of the time
// the watchdog can be feed at the end of the startup code
void main()
{
	__disable_irq();
	initialize_copwdt();
	initialize_systick();
	initialize_pwm_rgbled();
	initialize_sw1();
	__enable_irq();
	
	set_pwm_rgbled_color_to( BLACK );
		
	uint8_t count = 0;
	
	while(1)
	{
		__asm("wfi");
		if( !systick_has_fired() )
				continue;
			
		//set_pwm_rgbled_color_to( count );
		set_pwm_red_level( count );
		
		count++;
			
		feed_the_watchdog();
	}
}