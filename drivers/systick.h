/*
Name: James Medici
Date: 11/3/19

Description:
Driver for systick timer. This timer controls the speed of the program.
*/

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdbool.h>

void initialize_systick();
_Bool systick_has_fired();
/* _Bool systick_has_not_fired(); */
	

#endif 
