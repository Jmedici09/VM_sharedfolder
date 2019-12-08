

#include <i2c0.h>
#include <rgbled.h>

#define DEVICE (0x0D<<1) 

void main()
{
	
	
	
	initialize_rgbled();
	initialize_i2c0();
	
	
	uint8_t i2cdata;
	int16_t xaccel;
	uint8_t color=0;
	
	turn_on_red_led();
	
	i2cdata = i2c0_read_byte( DEVICE , 0x0D);
	if( i2cdata == (0x1A) )
		turn_on_blue_led();
	
	i2c0_write_byte( DEVICE, 0x2a, 0x01);
	i2cdata = i2c0_read_byte( DEVICE , 0x2a);
	if( i2cdata == (0x01) )
		turn_on_green_led();
	
	while(1){
		
		i2cdata = i2c0_read_byte( DEVICE , 0x00);
		if( i2cdata & (1<<0) )
		{
			xaccel = i2c0_read_byte( DEVICE , 0x01) << 8;
			if(xaccel < 0 )
				turn_on_blue_led();
			else
				turn_off_blue_led();
			
			
			
		}
		
	}
}

