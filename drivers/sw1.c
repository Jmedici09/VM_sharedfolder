/*
Name: James Medici
Date: 10/5/19

Description:
Driver for repurposed reset switch on Kinetis board
*/

#include <sw1.h>

void initialize_sw1()
{

	//configure sw1
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[SW1] = (PORTA->PCR[SW1]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
				| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTA->PDDR &= ~(1<<SW1);
}

_Bool sw1_is_pressed()
{
	return !(PTA->PDIR & (1<<SW1));
}
_Bool sw1_is_not_pressed()
{
	return !sw1_is_pressed();
}

void wait_until_sw1_pressed_then_released()
{
	uint8_t debounce_count = 0;
	while(sw1_is_not_pressed());
	while(debounce_count != debounce_time) debounce_count++;
	while(sw1_is_pressed());
}
void wait_until_sw1_released_then_pressed()
{
	uint8_t debounce_count = 0;
	while(sw1_is_pressed());
	while(debounce_count != debounce_time) debounce_count++;
	while(sw1_is_not_pressed());
}