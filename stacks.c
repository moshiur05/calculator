#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>

void push_calc_stack(void *);
void pop_calc_stack(void);
struct calc_stack_ calc_stack = {NULL, -1, push_calc_stack, pop_calc_stack};
void push_num_stack(void *);
struct num_stack_ num_stack = {NULL, -1, push_num_stack};

void push_calc_stack(void *numptr)
{
	extern int offset;
	calc_stack.ptr = realloc(calc_stack.ptr, (++calc_stack.index + 1)*offset);
	memcpy((void *)((char *)calc_stack.ptr + calc_stack.index*offset), numptr, (size_t)offset);
	return;
}

void pop_calc_stack(void)
{
	extern int offset;
	calc_stack.ptr = realloc(calc_stack.ptr, calc_stack.index*offset);
	--calc_stack.index;
	return;
}

void push_num_stack(void *numptr)
{
	extern int offset;
	num_stack.ptr = realloc(num_stack.ptr, (++num_stack.index + 1)*offset);
	memcpy((void *)((char *)num_stack.ptr + num_stack.index*offset), numptr, (size_t)offset);
	return;
}
