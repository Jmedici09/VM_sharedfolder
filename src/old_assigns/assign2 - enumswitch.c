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
			//set leds with enum
			switch(random_counter & 7) 
			{
				case 0:
					set_led_to(BLACK);
					break;
				case 7:
					set_led_to(WHITE);
					break;
				case 6:
					set_led_to(CYAN);
					break;
				case 5:
					set_led_to(MAGENTA);
					break;
				case 3:
					set_led_to(YELLOW);
					break;
				case 1:
					set_led_to(RED);
					break;
				case 2:
					set_led_to(GREEN);
					break;
				case 4:
					set_led_to(BLUE);
					break;			
				default:
					set_led_to(BLACK);
					break;
			}
		}
	}   
}