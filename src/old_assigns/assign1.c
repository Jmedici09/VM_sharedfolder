#include <MKL25Z4.h>
#include <stdint.h>

#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 1
#define SW1 20

void main(void)
{
	//create variable random to hold counter variable (keep uninitialized as extra entropy)
	uint8_t random_counter;

	//configure red LED
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[RED_LED]  = (PORTB->PCR[RED_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
				| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTB->PDDR |= (1<<RED_LED);
	
	//configure green LED
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[GREEN_LED]  = (PORTB->PCR[GREEN_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
                                | PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTB->PDDR |= (1<<GREEN_LED);
	
	//configure blue LED
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[BLUE_LED]  = (PORTD->PCR[BLUE_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
                                | PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTD->PDDR |= (1<<BLUE_LED);
	
	//configure sw1
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[SW1] = (PORTA->PCR[SW1]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
				| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTA->PDDR &= ~(1<<SW1);

	while(1)
	{
		//if sw1 is not pressed 
		if( PTA->PDIR & (1<<SW1) )
		{
			//increment random 
			random_counter += 1;
		}
		//else
		else
		{
			//set red led state based on bit 0 of random
			PTB->PDOR = (PTB->PDOR & ~(1<<RED_LED))
				|(((random_counter & (1<<0))>>0)<<RED_LED);
	
			//set green led state based on bit 1 of random
                	PTB->PDOR = (PTB->PDOR & ~(1<<GREEN_LED))
				|(((random_counter & (1<<1))>>1)<<GREEN_LED);

			//set blue led state based on bit 2 of random         
			PTD->PDOR = (PTD->PDOR &~(1<<BLUE_LED))
				|(((random_counter & (1<<2))>>2)<<BLUE_LED);
		}
	}   
}
