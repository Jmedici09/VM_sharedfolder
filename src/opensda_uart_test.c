#include <opensda_uart.h>

void main()
{
	uint8_t data = 'a';
	initialize_opensda_uart();
	
	send_byte_to_opensda_uart(data);
	while(1){
		if( get_byte_from_opensda_uart(&data) )
		{
			send_byte_to_opensda_uart(data+1);
			while(!opensda_uart_tx_ready());
			send_byte_to_opensda_uart('\n');
		}
		
		//send_byte_to_opensda_uart(data);
	}
}
