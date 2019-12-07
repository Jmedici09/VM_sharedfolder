/*
Name: James Medici
Date: 11/3/19

Description:
Driver for system timer. Uses interupts 
*/

#include <systick.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef SYSTICK_PERIOD
#define SYSTICK_PERIOD 1000 // in us
#endif

#define SYSTICK_TOP_VAL ((SYS_CLOCK/SYSTICK_PERIOD))
#if (SYSTICK_TOP_VAL > (1<<24 - 1))
#error SYSTICK_PERIOD is too large
#endif
#define SYSTICK_TOP ((uint32_t) SYSTICK_TOP_VAL)

static volatile _Bool systick_irq;

void initialize_systick()
{
	//Configure CTRL
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
					SysTick_CTRL_ENABLE_Msk |
					SysTick_CTRL_TICKINT_Msk;
	//Set Period in LOAD
	SysTick->LOAD = SYSTICK_TOP_VAL;
	
	
}

_Bool systick_has_fired()
{
	if( systick_irq )
	{
		systick_irq=0;
		return true;
	}	
	return false;
}

/* _Bool systick_has_not_fired()
{
	return !systick_has_fired();
	
} */

void SysTick_Handler()
{
	systick_irq=1;
}