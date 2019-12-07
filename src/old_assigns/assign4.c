/*
Name: James Medici
Date: 11/28/19

Description:
Assignment to set led to pwm value.
An FSM is created depending the state of the button


press_count needs about 11 bits of precision to count to 2000, the highest count needed. 
A 32 bit uint is not needed since a 16 bit press_count overflows at about 65 seconds.
*/

#include <copwdt.h>
#include <systick.h>
#include <pwm_rgbled.h>
#include <sw1.h>
#include <MKL25Z4.h>
#include <stdint.h>


#define COUNT_L0 500
#define COUNT_L1 1000
#define COUNT_L2 1500
#define COUNT_L3 2000

#if (COUNT_L0 >= COUNT_L1) || (COUNT_L1 >= COUNT_L2)  || (COUNT_L2 >= COUNT_L3)
#error Count lengths must increase
#endif


#define LED_LEVEL_INCR 16


enum FSM_SW1_PRESS {sw1_pressed, sw1_not_pressed}
	g_PRESS = sw1_not_pressed;	

enum FSM_CURRENT_LED {led_red, led_green, led_blue, led_none}
	g_CURRENT_LED = led_red;
	
void main()
{
	__disable_irq();
	initialize_copwdt();
	initialize_systick();
	initialize_pwm_rgbled();
	initialize_sw1();
	__enable_irq();
	
	uint16_t press_count = 0;
	
	uint8_t led_levels[4] = {0,0,0,0}; 
	
	
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
				if( press_count < COUNT_L0 )
				{
					set_pwm_rgbled_color_to( WHITE );
				}
				else if( press_count < COUNT_L1 )
				{
					set_pwm_rgbled_color_to( RED );
				}
				else if( press_count < COUNT_L2 )
				{
					set_pwm_rgbled_color_to( GREEN );
				}
				else if( press_count < COUNT_L3 )
				{
					set_pwm_rgbled_color_to( BLUE );
				}
				else
				{
					set_pwm_rgbled_color_to( BLACK );
				}
				
				if ( sw1_is_not_pressed() )
				{
					g_PRESS = sw1_not_pressed;
					
					if( press_count < COUNT_L0 )
					{
						led_levels[g_CURRENT_LED] = led_levels[g_CURRENT_LED] + LED_LEVEL_INCR;
					}
					else if( press_count < COUNT_L1 )
					{
						g_CURRENT_LED = led_red;
					}
					else if( press_count < COUNT_L2 )
					{
						g_CURRENT_LED = led_green;
					}
					else if( press_count < COUNT_L3 )
					{
						g_CURRENT_LED = led_blue;
					}
					else
					{
						led_levels[led_red] = 0;
						led_levels[led_green] = 0;
						led_levels[led_blue] = 0;
					}
				
				}
				break;
			case sw1_not_pressed:
				press_count = 0;
				
				set_pwm_rgbled_levels_to( led_levels[led_red] , led_levels[led_green], led_levels[led_blue] );
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