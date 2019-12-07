/*
Name: James Medici
Date: 11/4/19

Description:
copwdt was not working for assignment 3
*/
#include <copwdt.h>
#include <rgbled.h>
#include <stdint.h>

void wait()
{
	volatile uint32_t wait = 480000;
	while(wait--);
}

void main()
{
	initialize_copwdt();
	initialize_rgbled();

	
	toggle_blue_led();
	wait();
	toggle_blue_led();
	wait();
	toggle_blue_led();
	wait();
	
	turn_off_blue_led();
	
	while(1)
	{
		toggle_green_led();
		wait();
		wait();
		wait();
		wait();
		wait();
		feed_the_watchdog();
	}
}