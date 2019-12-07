/*
Name: James Medici
Date: 10/5/19

Description:
Driver for tri-color led on Kinetis Board
*/



#include <rgbled.h>

#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 1

void initialize_red_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[RED_LED]  = (PORTB->PCR[RED_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
			| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTB->PDDR |= (1<<RED_LED);
}

void initialize_green_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[GREEN_LED]  = (PORTB->PCR[GREEN_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
			| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTB->PDDR |= (1<<GREEN_LED);
}
	
void initialize_blue_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[BLUE_LED]  = (PORTD->PCR[BLUE_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK))
			| PORT_PCR_MUX(1) | PORT_PCR_IRQC(0);
	PTD->PDDR |= (1<<BLUE_LED);
}
	

void initialize_rgbled()
{
	initialize_red_led();
	initialize_green_led();
	initialize_blue_led();
	turn_off_led();
}



/// Change LED state
void change_red_led_state_to(uint8_t led_state)
{
	PTB->PDOR = (PTB->PDOR & ~(1<<RED_LED))
				|(led_state<<RED_LED);
}
void change_green_led_state_to(uint8_t led_state)
{
	PTB->PDOR = (PTB->PDOR & ~(1<<GREEN_LED))
				|(led_state<<GREEN_LED);	
}
void change_blue_led_state_to(uint8_t led_state)
{
	PTD->PDOR = (PTD->PDOR & ~(1<<BLUE_LED))
				|(led_state<<BLUE_LED);
}

void toggle_red_led()
{
	PTB->PTOR |= (1<<RED_LED);
}
void toggle_green_led()
{
	PTB->PTOR |= (1<<GREEN_LED);
}
void toggle_blue_led()
{
	PTD->PTOR |= (1<<BLUE_LED);
}

void turn_on_red_led()
{
	PTB->PCOR |= (1<<RED_LED);
}
void turn_on_green_led()
{
	PTB->PCOR |= (1<<GREEN_LED);
}
void turn_on_blue_led()
{
	PTD->PCOR |= (1<<BLUE_LED);
}

void turn_off_red_led()
{
	PTB->PSOR |= (1<<RED_LED);
}
void turn_off_green_led()
{
	PTB->PSOR |= (1<<GREEN_LED);
}
void turn_off_blue_led()
{
	PTD->PSOR |= (1<<BLUE_LED);
}

void set_led_to(enum COLOR_TYPE color)
{
	switch(color)
	{
		case BLACK:
			turn_off_red_led();
			turn_off_green_led();
			turn_off_blue_led();
			break;
		case WHITE:
			turn_on_red_led();
			turn_on_green_led();
			turn_on_blue_led();
			break;
		case CYAN:
			turn_off_red_led();
			turn_on_green_led();
			turn_on_blue_led();
			break;
		case MAGENTA:
			turn_on_red_led();
			turn_off_green_led();
			turn_on_blue_led();
			break;
		case YELLOW:
			turn_on_red_led();
			turn_on_green_led();
			turn_off_blue_led();
			break;
		case RED:
			turn_on_red_led();
			turn_off_green_led();
			turn_off_blue_led();
			break;
		case GREEN:
			turn_off_red_led();
			turn_on_green_led();
			turn_off_blue_led();
			break;
		case BLUE:
			turn_off_red_led();
			turn_off_green_led();
			turn_on_blue_led();
			break;
		case OFF:
			turn_off_red_led();
			turn_off_green_led();
			turn_off_blue_led();
			break;
		default:
			turn_on_red_led();
			turn_on_green_led();
			turn_on_blue_led();
			break;
	}
}
void turn_off_led()  // set led to BLACK
{
	set_led_to(OFF);
}


/// Check LED state
_Bool red_led_is_on();
_Bool green_led_is_on();
_Bool blue_led_is_on();	

enum COLOR_TYPE current_led_color();
_Bool led_is(enum COLOR_TYPE); // check to see if led is the inputed color