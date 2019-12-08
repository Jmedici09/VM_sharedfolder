#include <opensda_uart.h>

void main()
{
	char data = 'a';
	initialize_opensda_uart();
	
	send_byte_to_opensda_uart(data);
	while(1)
		if( get_byte_from_opensda_uart(&data) )
			send_byte_to_opensda_uart(data);
}
