/*
Name: James Medici
Date: 11/4/19

Description:
testing systick timer for asssignment 3
*/
#include <systick.h>
#include <rgbled.h>
#include <MKL25Z4.h>
#include <stdint.h>

void main()
{
	__disable_irq();
	initialize_systick();
	initialize_rgbled();
	__enable_irq();
	
	uint32_t count = 0;
	set_led_to(GREEN);
	while(1)
	{
		__asm("wfi");
		if( !systick_has_fired() )
				continue;
			
		//loop body	
		count++;
		if( count >= 500)
		{
			count = 0;
			toggle_red_led();
		}
	}
}