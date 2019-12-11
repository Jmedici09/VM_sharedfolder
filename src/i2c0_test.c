#include <i2c0.h>
#include <rgbled.h>
#include <opensda_uart.h>


#define DEVICE (0x1D<<1) 
#define NumTohex( value ) ((value < 10) ? (value + '0') : (value - 10 + 'A'));

static void uart_send_start();
static void to_hex( uint8_t value , char *hex );
static void uart_send_i2c_data( uint8_t i2cdata );


// LIBS="sw1.o rgbled.o opensda_uart.o i2c0.o" make i2c0_test.srec
// cp i2c0_test.srec /media/student/FRDM-KL25Z/


void main()
{
	initialize_opensda_uart();
	initialize_rgbled();
	initialize_i2c0();
	
	
	uint8_t i2cdata = 20;
	int16_t xaccel;
	//uint8_t color=0;
	
	
	uart_send_start();
	
	/////////////////////////////////////	
	char i2cdata_hex[7] = "0xGG\n\r"; // not a valid hex value
	uart_blocking_send(i2cdata_hex);
	i2cdata_hex[3] = ((i2cdata & 0x0f) < 10) ? ((i2cdata & 0x0f) + '0') : ((i2cdata & 0x0f) - 10 + 'A');
	i2cdata_hex[2] = ((i2cdata >> 4) < 10) ? ((i2cdata >> 4) + '0') : ((i2cdata >> 4) - 10 + 'A');
	uart_blocking_send(i2cdata_hex);

	//////////////////////////////////////
	
	//uart_send_i2c_data( i2cdata );
	
	turn_on_red_led();
	
	i2cdata = i2c0_read_byte( DEVICE , 0x0D);
	if( i2cdata == (0x1A) )
		uart_blocking_send("Device Found\n\r\a");
	
	i2cdata_hex[3] = 'G'; 
	i2cdata_hex[2] = 'G'; 	
	i2cdata_hex[3] = ((i2cdata & 0x0f) < 10) ? ((i2cdata & 0x0f) + '0') : ((i2cdata & 0x0f) - 10 + 'A');
	i2cdata_hex[2] = ((i2cdata >> 4) < 10) ? ((i2cdata >> 4) + '0') : ((i2cdata >> 4) - 10 + 'A');
	uart_blocking_send("Current Value:");
	uart_blocking_send(i2cdata_hex);
	
	//uart_send_i2c_data( i2cdata );
	
	i2c0_write_byte( DEVICE, 0x2a, 0x01);
	i2cdata = i2c0_read_byte( DEVICE , 0x2a);
	if( i2cdata == (0x01) )
		uart_blocking_send("Device On\n\r\a");
	
	i2cdata_hex[3] = 'G'; 
	i2cdata_hex[2] = 'G'; 	
	i2cdata_hex[3] = ((i2cdata & 0x0f) < 10) ? ((i2cdata & 0x0f) + '0') : ((i2cdata & 0x0f) - 10 + 'A');
	i2cdata_hex[2] = ((i2cdata >> 4) < 10) ? ((i2cdata >> 4) + '0') : ((i2cdata >> 4) - 10 + 'A');
	uart_blocking_send("Current Value: 0x2a");
	uart_blocking_send(i2cdata_hex);
	
	
	set_led_to( BLACK );
	
	while(1){
		
		i2cdata = i2c0_read_byte( DEVICE , 0x00);
		/* i2cdata_hex[3] = 'G'; 
		i2cdata_hex[2] = 'G'; 	
		i2cdata_hex[3] = ((i2cdata & 0x0f) < 10) ? ((i2cdata & 0x0f) + '0') : ((i2cdata & 0x0f) - 10 + 'A');
		i2cdata_hex[2] = ((i2cdata >> 4) < 10) ? ((i2cdata >> 4) + '0') : ((i2cdata >> 4) - 10 + 'A');
		uart_blocking_send("Current Value of 0x00:");
		uart_blocking_send(i2cdata_hex); */
		
		if( i2cdata & (1<<0) )
		{
			xaccel = i2c0_read_byte( DEVICE , 0x01) << 8;
			i2cdata  = xaccel >> 8;
			
			i2cdata_hex[3] = 'G'; 
			i2cdata_hex[2] = 'G'; 	
			i2cdata_hex[3] = ((i2cdata & 0x0f) < 10) ? ((i2cdata & 0x0f) + '0') : ((i2cdata & 0x0f) - 10 + 'A');
			i2cdata_hex[2] = ((i2cdata >> 4) < 10) ? ((i2cdata >> 4) + '0') : ((i2cdata >> 4) - 10 + 'A');
			uart_blocking_send("Current Value of 0x01:");
			uart_blocking_send(i2cdata_hex);
			
			
			if(xaccel < 0 )
				set_led_to( BLUE );
			else
				set_led_to( BLACK );	
		}		
	}
}

static void uart_send_start()
{
	uart_blocking_send("\n\rstart\n\r\a");
}

static void to_hex( uint8_t value , char *hex )
{
	hex = "0xGG\n\r"; // not a valid hex value
	
	*(hex + 3) = ((value & 0x0f) < 10) ? ((value & 0x0f) + '0') : ((value & 0x0f) - 10 + 'A');
	
	turn_on_green_led();
	*(hex + 2) = ((value >> 4) < 10) ? ((value >> 4) + '0') : ((value >> 4) - 10 + 'A');
	
}

static void uart_send_i2c_data( uint8_t i2cdata )
{
	char i2cdata_hex[6] = "0xGG\n\r"; // not a valid hex value
	//i2cdata_hex[2] = NumTohex(  );
	to_hex( i2cdata , i2cdata_hex );
	turn_on_blue_led();
	uart_blocking_send(i2cdata_hex);
}