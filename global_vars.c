#include "definitions.c"
#include <stdio.h>
#include <stdlib.h>

enum operator_ *operator = NULL;
enum operator_ *expression = NULL;
int expression_index = -1;
enum number_system_ number_system = real_;
int offset = (int)sizeof(double);
void push_calc_stack(void *);
void pop_calc_stack(void);
struct calc_stack_ calc_stack = {NULL, -1, push_calc_stack, pop_calc_stack};
void push_num_stack(void *);
struct num_stack_ num_stack = {NULL, -1, push_num_stack};

void reset_memory(void)
{
	extern struct calc_stack_ calc_stack;
	extern enum operator_ *operator;
	extern struct num_stack_ num_stack;
	extern enum operator_ *expression;
	extern int expression_index;
	free(num_stack.ptr);
	num_stack.ptr = NULL;
	free((void *)operator);
	operator = NULL;
	free(calc_stack.ptr);
	calc_stack.ptr = NULL;
	free((void *)expression);
	expression = NULL;

	num_stack.index = -1;
	calc_stack.index = -1;
	expression_index = -1;
}
