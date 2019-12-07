/*
Name: James Medici
Date: 10/5/19

Description:
Driver for tri-color led on Kinetis Board with PWM

In order to allow for an uint8 level selection, PWM_MAX_LEVEL is set as the top value for the register. 
	This means that if the CnV for a register is set to PWM_ON_LEVEL, then the pwm output will always be high.
	
Red led: TPM 2 Ch0
Green led: TPM 2 Ch1
Blue led: TPM 0 Ch1
*/

#include <pwm_rgbled.h>
#include <MKL25Z4.h>
#include <stdint.h>

#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 1


static void initialize_pwm_red_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[RED_LED]  = (PORTB->PCR[RED_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(3); // mux 3
	PTB->PDDR |= (1<<RED_LED);
}
static void initialize_pwm_green_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[GREEN_LED]  = (PORTB->PCR[GREEN_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(3); 
	PTB->PDDR |= (1<<GREEN_LED);
}	
static void initialize_pwm_blue_led()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[BLUE_LED]  = (PORTD->PCR[BLUE_LED]&~(PORT_PCR_MUX_MASK|PORT_PCR_IRQC_MASK)) | PORT_PCR_MUX(4);  // mux 4
	PTD->PDDR |= (1<<BLUE_LED);
}
static void initialize_pwm()
{
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;	
	TPM0->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(0);	
	TPM0->MOD = PWM_MAX_LEVEL-1; 
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_ELSA(1) | TPM_CnSC_ELSB(0) | // active low pulses
							 TPM_CnSC_MSA(0) | TPM_CnSC_MSB(1);
	turn_off_pwm_blue_led();						 
	
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;	
	TPM2->SC = TPM_SC_CPWMS(0) | TPM_SC_PS(0);	
	TPM2->MOD = PWM_MAX_LEVEL-1; 
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_ELSA(1) | TPM_CnSC_ELSB(0) | 
							 TPM_CnSC_MSA(0) | TPM_CnSC_MSB(1);
	turn_off_pwm_red_led();
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_ELSA(1) | TPM_CnSC_ELSB(0) | 
							 TPM_CnSC_MSA(0) | TPM_CnSC_MSB(1);
	turn_off_pwm_green_led();
							 
	TPM0->SC |= TPM_SC_CMOD(01);
	TPM2->SC |= TPM_SC_CMOD(01);
}

void initialize_pwm_rgbled()
{
	initialize_pwm();
	initialize_pwm_red_led();
	initialize_pwm_green_led();
	initialize_pwm_blue_led();
}

void set_pwm_red_level( uint8_t level )
{
	//TPM2->CONTROLS[0].CnV = level-1; 
	TPM2->CONTROLS[0].CnV = level; 
}
void set_pwm_green_level( uint8_t level )
{
	TPM2->CONTROLS[1].CnV = level; 
}
void set_pwm_blue_level( uint8_t level )
{	
	TPM0->CONTROLS[1].CnV = level; 
}

void turn_on_pwm_red_led()
{
	set_pwm_red_level( PWM_ON_LEVEL );
}
void turn_on_pwm_green_led()
{
	set_pwm_green_level( PWM_ON_LEVEL );
}
void turn_on_pwm_blue_led()
{
	set_pwm_blue_level( PWM_ON_LEVEL );
}

void turn_off_pwm_red_led()
{
	set_pwm_red_level( PWM_OFF_LEVEL );
}
void turn_off_pwm_green_led()
{
	set_pwm_green_level( PWM_OFF_LEVEL );
}
void turn_off_pwm_blue_led()
{
	set_pwm_blue_level( PWM_OFF_LEVEL );
}

void set_pwm_rgbled_levels_to( uint8_t red_level, uint8_t green_level, uint8_t blue_level)
{
	set_pwm_red_level( red_level );
	set_pwm_green_level( green_level );
	set_pwm_blue_level( blue_level );
}

void set_pwm_rgbled_color_to(enum COLOR_TYPE color)
{
	switch(color)
	{
		case BLACK:
			set_pwm_rgbled_levels_to( PWM_OFF_LEVEL, PWM_OFF_LEVEL, PWM_OFF_LEVEL);
			break;
		case WHITE:
			set_pwm_rgbled_levels_to( PWM_ON_LEVEL, PWM_ON_LEVEL, PWM_ON_LEVEL);
			break;
		case CYAN:
			set_pwm_rgbled_levels_to( PWM_OFF_LEVEL, PWM_ON_LEVEL, PWM_ON_LEVEL);
			break;
		case MAGENTA:
			set_pwm_rgbled_levels_to( PWM_ON_LEVEL, PWM_OFF_LEVEL, PWM_ON_LEVEL);
			break;
		case YELLOW:
			set_pwm_rgbled_levels_to( PWM_ON_LEVEL, PWM_ON_LEVEL, PWM_OFF_LEVEL);
			break;
		case RED:
			set_pwm_rgbled_levels_to( PWM_ON_LEVEL, PWM_OFF_LEVEL, PWM_OFF_LEVEL);
			break;
		case GREEN:
			set_pwm_rgbled_levels_to( PWM_OFF_LEVEL, PWM_ON_LEVEL, PWM_OFF_LEVEL);
			break;
		case BLUE:
			set_pwm_rgbled_levels_to( PWM_OFF_LEVEL, PWM_OFF_LEVEL, PWM_ON_LEVEL);
			break;
		case OFF:
			set_pwm_rgbled_levels_to( PWM_OFF_LEVEL, PWM_OFF_LEVEL, PWM_OFF_LEVEL);
			break;
		default:
			set_pwm_rgbled_levels_to( PWM_ON_LEVEL, PWM_ON_LEVEL, PWM_ON_LEVEL);
			break;
	}
}
void turn_off_pwm_led()  // set led to BLACK
{
	set_pwm_rgbled_color_to(OFF);
}
