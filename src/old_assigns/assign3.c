/*
Name: James Medici
Date: 11/3/19

Description:
Assignment to test systick timer. Must also be sure to feed the watchdog.
An FSM is created depending the state of the button
*/

#include <copwdt.h>
#include <systick.h>
#include <rgbled.h>
#include <sw1.h>
#include <MKL25Z4.h>
#include <stdint.h>


#define SHORT_COUNT 500
#define MEDIUM_COUNT 1000
#define LONG_COUNT 2000

#if (SHORT_COUNT > MEDIUM_COUNT) || (MEDIUM_COUNT > LONG_COUNT)
#error Count lengths must increase
#endif

enum FSM_SW1_PRESS {sw1_pressed, sw1_not_pressed}
	g_PRESS = sw1_not_pressed;	

void main()
{
	__disable_irq();
	initialize_copwdt();
	initialize_systick();
	initialize_rgbled();
	initialize_sw1();
	__enable_irq();
	
	// press_count needs about 11 bits of precision to count to 2000, the highest count needed. 
	// A 32 bit uint is not needed since a 16 bit press_count overflows at about 65 seconds.
	uint16_t press_count = 0;
	
	while(1)
	{
		__asm("wfi");
		if( !systick_has_fired() )
				continue;
			
		//loop body
		
		switch( g_PRESS )
		{
			case sw1_pressed:
				press_count++;
				if ( sw1_is_not_pressed() )
				{
					g_PRESS = sw1_not_pressed;
					
					if( press_count < SHORT_COUNT )
					{
						toggle_red_led();
					}
					else if( press_count < MEDIUM_COUNT )
					{
						toggle_green_led();
					}
					else if( press_count < LONG_COUNT )
					{
						toggle_blue_led();
					}
					else
					{
						while(1);
					}
				
				}
				break;
			case sw1_not_pressed:
				press_count = 0;
				if ( sw1_is_pressed() )
				{
					g_PRESS = sw1_pressed;
				}
				break;
			default:
				g_PRESS = sw1_not_pressed;
		}	
		
		feed_the_watchdog();
	}
}