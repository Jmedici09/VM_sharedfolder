#include <copwdt.h>
#include <systick.h>

#include <i2c0.h>
#include <rgbled.h>

void main()
{
	
	
	__disable_irq();
	initialize_copwdt();
	initialize_systick();
	initialize_rgbled();
	initialize_i2c0();
	__enable_irq();
	
	uint8_t data;
	
	turn_on_red_led();
	
	i2c0_read_byte ( (0x1D<<1) , 0x0D , &data);
	if( data == (0x1A) )
		turn_on_blue_led();
	while(1){
		__asm("wfi");
		if( !systick_has_fired() )
				continue;
		
		feed_the_watchdog();
	}
}

