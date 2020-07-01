#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

void push_calc_stack(void *);
void pop_calc_stack(void);
struct calc_stack_ calc_stack = {NULL, -1, push_calc_stack, pop_calc_stack};
void push_num_stack(void *);
struct num_stack_ num_stack = {NULL, -1, push_num_stack};

void push_calc_stack(void *numptr)
{
	extern enum number_system_ number_system;
	extern int offset;
	if(number_system == real_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, (++calc_stack.index + 1)*offset);
		((double *)calc_stack.ptr)[calc_stack.index] = *((double *)numptr);
	} else if(number_system == complex_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, (++calc_stack.index + 1)*offset);
		((complex double *)calc_stack.ptr)[calc_stack.index] = *((complex double *)numptr);
	}
	return;
}

void pop_calc_stack(void)
{
	extern enum number_system_ number_system;
	extern int offset;
	if(number_system == real_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, calc_stack.index*offset);
	} else if(number_system == complex_)
	{
		calc_stack.ptr = realloc(calc_stack.ptr, calc_stack.index*offset);
	}
	--calc_stack.index;
	return;
}

void push_num_stack(void *numptr)
{
	extern enum number_system_ number_system;
	extern int offset;
	if(number_system == real_)
	{
		num_stack.ptr = realloc(num_stack.ptr, (++num_stack.index + 1)*offset);
		((double *)num_stack.ptr)[num_stack.index] = *((double *)numptr);
	} else if(number_system == complex_)
	{
		num_stack.ptr = realloc(num_stack.ptr, (++num_stack.index + 1)*offset);
		((complex double *)num_stack.ptr)[num_stack.index] = *((complex double *)numptr);
	}
	return;
}
