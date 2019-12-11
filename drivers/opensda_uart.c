#include <opensda_uart.h>
#include <MKL25Z4.h>
#include <stdbool.h>
#include <stdint.h>

// Use "minicom -s"
// "serial port setup"
// "A -  /dev/ttyACM0" // name of kinetis board

void initialize_opensda_uart()
{
	//clock gating
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	//Enable UART0 Clock
	SIM->SOPT2 |= (SIM_SOPT2_UART0SRC(1) | SIM_SOPT2_PLLFLLSEL(1));
	//MUX Config for TX, RX
	PORTA->PCR[1] = (PORTA->PCR[1] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(2);
	PORTA->PCR[2] = (PORTA->PCR[2] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(2);
	//UART0->BDH = 0;
	UART0->BDL = 26;
	//UART0->C1=0;
	UART0->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK) ; //bits 3 and 2
	//UART0->C3=0;
}
_Bool send_byte_to_opensda_uart( uint8_t data)
{
	if( opensda_uart_tx_ready() )
	{
		UART0->D = data;
		return true;
	}
	return false;
}
_Bool get_byte_from_opensda_uart( uint8_t *data)
{
	if( opensda_uart_rx_ready() )
	{
		*data=UART0->D;
		return true;
	}
	return false;
}
_Bool opensda_uart_rx_ready()
{
	return UART0->S1 & UART_S1_RDRF_MASK;
}
_Bool opensda_uart_tx_ready()
{
	return UART0->S1 & UART_S1_TDRE_MASK;
}

void uart_blocking_send(char *payload)
{
	while(*payload)
	{
		while(!opensda_uart_tx_ready());
		send_byte_to_opensda_uart(*payload);
		payload++;
	}
	while(!opensda_uart_tx_ready());
}