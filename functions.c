#include "stacks_and_enums.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

enum number_system_ number_system = real_;
int offset = 0;
void push_(void *);
void pop_(void);
struct calculation_stack_ calculation_stack = {NULL, -1, push_, pop_};
struct num_stack_ num_stack = {NULL, -1};
enum action_ *action = NULL;

int is_equal_str(const char *str1, const char *str2)
{
	int i = 0;
	for(int i = 0; str1[i] != '\0'; ++i)
	{
		i += (str1[i] != str2[i]);
	}
	return !i;
}

int choose_number_system(char *str)
{
	extern int offset;
	if(is_equal_str(str, "real"))
	{
		number_system = real_;
		offset = (int)sizeof(double);
	} else if(is_equal_str(str, "complex"))
	{
		number_system = complex_;
		offset = (int)sizeof(complex double);
	} else
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void push_(void *numptr)
{
	if(number_system == real_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, (++calculation_stack.index + 1)*(sizeof(double)));
		((double *)calculation_stack.ptr)[calculation_stack.index] = *((double *)numptr);
	} else if(number_system == complex_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, (++calculation_stack.index + 1)*(sizeof(complex double)));
		((complex double *)calculation_stack.ptr)[calculation_stack.index - 1] = *((complex double *)numptr);
	}
	return;
}

void pop_(void)
{
	if(number_system == real_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, calculation_stack.index*(sizeof(double)));
	} else if(number_system == complex_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, calculation_stack.index*(sizeof(complex double)));
	}
	--calculation_stack.index;
	return;
}

char *get_line(void)
{
	static char *str = NULL;
	free(str);
	int size = 1;
	str = (char *)malloc(size);
	printf("=> ");
	while((str[size - 1] = getchar()) != '\n')
	{
		str = (char *)realloc((void *)str, ++size);
	}
	str[size - 1] = '\0';
	return str;
}

size_t gen_num_stack_size(char *);
void gen_num_stack(char * input)
{
	num_stack.ptr = malloc(gen_num_stack_size(input));
	return;
}

size_t gen_action_array_size(char *);
void gen_action(char *input)
{
	action = (enum action_ *)malloc(gen_action_array_size(input));
	return;
}

void do_action(int);
void gen_result(void)
{
	for(int i = 0; action[i] != EXIT; ++i)
	{
		do_action(i);
	}

	switch(number_system)
	{
		case real_ :
			printf("Ans = %lf\n", *((double *)calculation_stack.ptr));
			break;
		case complex_ :
			printf("Ans = %lf + %lf i\n", creal(*((complex double *)calculation_stack.ptr)), cimag(*((complex double *)calculation_stack.ptr)));
			break;
	}
	return;
}

void reset_memory(void)
{
	free(num_stack.ptr);
	num_stack.ptr = NULL;
	free((void *)action);
	action = NULL;
	free(calculation_stack.ptr);
	calculation_stack.ptr = NULL;

	num_stack.index = -1;
	calculation_stack.index = -1;
}
