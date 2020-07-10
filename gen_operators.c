#include "definitions.c"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_equal_str(char *, char *);

void get_expression(char *);
void gen_operator_sequence(char *input)
{
	extern enum operator_ *operator, *expression;
	get_expression(input);
	operator = expression;
	return;
}

int get_operator_and_update_index(char *);
void update_expression(enum operator_);
void get_expression(char *input)
{
	int i = 0;
	while(input[i] != '\0')
	{
		i += get_operator_and_update_index(&input[i]);
	}
	update_expression(EXIT);
	return;
}

int get_operator_and_update_index(char *cptr)
{
	extern enum number_system_ number_system;
	int i = 0;
	if(((*cptr == '+') || (*cptr == '-')) && isdigit(cptr[1]))
	{
		update_expression(NUMBER);
		do
		{
			++i;
			++cptr;
		} while(isdigit(*cptr) || *cptr == '.');
		if(number_system == complex_)
		{
			do
			{
				++i;
				++cptr;
			} while(isdigit(*cptr) || *cptr == '.');
			++i;
		}
	} else if(*cptr == '+')
	{
		++i;
		update_expression(ADD);
	} else if(*cptr == '-')
	{
		++i;
		update_expression(SUBSTRACT);
	} else if(*cptr == '*')
	{
		++i;
		update_expression(MULTIPLY);
	} else if(*cptr == '/')
	{
		++i;
		update_expression(DIVIDE);
	} else if(*cptr == '|')
	{
		update_expression(ABS);
	} else if(is_equal_str(cptr, "exp"))
	{
		i += 3;
		update_expression(EXP);
	} else if(is_equal_str(cptr, "ln"))
	{
		i += 2;
		update_expression(LN);
	} else if(is_equal_str(cptr, "pow"))
	{
		i += 3;
		update_expression(POW);
	} else if(is_equal_str(cptr, "cos"))
	{
		i += 3;
		update_expression(COS);
	} else if(is_equal_str(cptr, "sin"))
	{
		i += 3;
		update_expression(SIN);
	} else if(is_equal_str(cptr, "tan"))
	{
		i += 3;
		update_expression(TAN);
	} else if(is_equal_str(cptr, "sec"))
	{
		i += 3;
		update_expression(SEC);
	} else if(is_equal_str(cptr, "cosec"))
	{
		i += 4;
		update_expression(COSEC);
	} else if(is_equal_str(cptr, "cot"))
	{
		i += 3;
		update_expression(COT);
	} else if(is_equal_str(cptr, "acos"))
	{
		i += 4;
		update_expression(ACOS);
	} else if(is_equal_str(cptr, "asin"))
	{
		i += 4;
		update_expression(ASIN);
	} else if(is_equal_str(cptr, "atan"))
	{
		i += 4;
		update_expression(ATAN);
	} else if(is_equal_str(cptr, "asec"))
	{
		i += 4;
		update_expression(ASEC);
	} else if(is_equal_str(cptr, "acosec"))
	{
		i += 6;
		update_expression(ACOSEC);
	} else if(is_equal_str(cptr, "acot"))
	{
		i += 4;
		update_expression(ACOT);
	} else if(*cptr == '(')
	{
		++i;
		update_expression(BRACKET);
	} else if(*cptr == ')')
	{
		++i;
		update_expression(BRACKET);
	} else if(*cptr == ' ')
	{
		++i;
	} else
	{
		printf("Give Valid Expression\n");
		exit(EXIT_FAILURE);
	}
	return i;
}

void update_expression(enum operator_ operator)
{
	extern enum operator_ *expression;
	extern int expression_index;
	expression = (enum operator_ *)realloc((void *)expression, (++expression_index + 1)*sizeof(enum operator_));
	expression[expression_index] = operator;
}
