
#include <MKL25Z4.h>
#include <stdint.h>

#define RED_LED 18
#define SW1 20

void main(void)
{
	//configure red LED
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[RED_LED]  = (PORTB->PCR[RED_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
				| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTB->PDDR |= (1<<RED_LED);
	
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
			PTB->PDOR &= ~(1<<RED_LED);
		}
		//else
		else
		{
			PTB->PDOR |= (1<<RED_LED);
		}
	}   
}
