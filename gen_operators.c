#include "definitions.c"
#include <stdlib.h>

void gen_operator_sequence(char *input)
{
	extern enum operator_ *operator;
	operator = (enum operator_ *)malloc(3*sizeof(enum operator_));
	operator[0] = NUMBER;
	operator[1] = NUMBER;
	operator[2] = ADD;
	operator[3] = EXIT;
	return;
}

void get_operators(char *input)
{
	;
}
