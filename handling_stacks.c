#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

extern int offset;
extern enum number_system_ number_system;
void push_calc_stack(void *);
void pop_calc_stack(void);
struct calc_stack_ calc_stack = {NULL, -1, push_calc_stack, pop_calc_stack};
void push_num_stack(void *);
struct num_stack_ num_stack = {NULL, -1, push_num_stack};

void push_calc_stack(void *numptr)
{
	if(number_system == real_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, (++calc_stack.index + 1)*(sizeof(double)));
		((double *)calc_stack.ptr)[calc_stack.index] = *((double *)numptr);
	} else if(number_system == complex_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, (++calc_stack.index + 1)*(sizeof(complex double)));
		((complex double *)calc_stack.ptr)[calc_stack.index - 1] = *((complex double *)numptr);
	}
	return;
}

void pop_calc_stack(void)
{
	if(number_system == real_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, calc_stack.index*(sizeof(double)));
	} else if(number_system == complex_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, calc_stack.index*(sizeof(complex double)));
	}
	--calc_stack.index;
	return;
}

void push_num_stack(void *numptr)
{
	if(number_system == real_)
	{
		num_stack.ptr = realloc(num_stack.ptr, (++num_stack.index + 1)*sizeof(double));
		((double *)num_stack.ptr)[num_stack.index] = *((double *)numptr);
	} else if(number_system == complex_)
	{
		num_stack.ptr = realloc(num_stack.ptr, (++num_stack.index + 1)*sizeof(complex double));
		((complex double *)num_stack.ptr)[num_stack.index] = *((complex double *)numptr);
	}
	return;
}
