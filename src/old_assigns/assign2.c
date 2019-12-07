/*
Name: James Medici
Date: 10/5/19

Purpose: Assignment 2

Description:
Assignment 1 implemented using drivers. 
Turns on LED to random value when button is pressed.
*/
#include <rgbled.h>
#include <sw1.h>

void main()
{
	//create variable random to hold counter variable (keep uninitialized as extra entropy)
	uint8_t random_counter;

	//configure LED
	initialize_rgbled();
	
	//configure sw1
	initialize_sw1();

	while(1)
	{
		//if sw1 is not pressed 
		if( sw1_is_not_pressed()) 
		{
			//increment random 
			random_counter += 1;
		}
		//else
		else
		{
			//set red led state based on bit 0 of random
			change_red_led_state_to(((random_counter & (1<<0))>>0));
				
			//set green led state based on bit 1 of random
            change_green_led_state_to(((random_counter & (1<<1))>>1));

			//set blue led state based on bit 2 of random         
			change_blue_led_state_to(((random_counter & (1<<2))>>2));
			
		}		
	}   
}