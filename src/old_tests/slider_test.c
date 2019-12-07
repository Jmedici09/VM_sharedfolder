#include <copwdt.h>
#include <systick.h>

#include <rgbled.h>
#include <slider.h>

#define THRESHOLD 16000 // this is in the middle
void main()
{
	
	__disable_irq();
	initialize_copwdt();
	initialize_systick();
	initialize_rgbled();
	initialize_slider();
	__enable_irq();
	
	
	while(1)
	{
		
		__asm("wfi");
		if( !systick_has_fired() )
				continue;
			
			
		if( touch_scan() < THRESHOLD )
			turn_off_red_led();
		else
			turn_on_red_led();
		
		feed_the_watchdog();
	}
}