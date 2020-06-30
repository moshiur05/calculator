#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

enum number_system_ number_system = real_;
int offset = 0;
extern struct calc_stack_ calc_stack;
extern struct num_stack_ num_stack;
enum action_ *action = NULL;

int is_equal_str(const char *str1, const char *str2)
{
	int det = 0;
	for(int i = 0; str1[i] != '\0'; ++i)
	{
		det += (str1[i] != str2[i]);
	}
	return !det;
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
			printf("Ans = %lf\n", *((double *)calc_stack.ptr));
			break;
		case complex_ :
			printf("Ans = %lf + %lf i\n", creal(*((complex double *)calc_stack.ptr)), cimag(*((complex double *)calc_stack.ptr)));
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
	free(calc_stack.ptr);
	calc_stack.ptr = NULL;

	num_stack.index = -1;
	calc_stack.index = -1;
}

void run_calc()
{
	char *input = NULL;
	while(!is_equal_str((input = get_line()), "exit"))
	{
		if(choose_number_system(input) == EXIT_SUCCESS){continue;}
		gen_num_stack(input);
		gen_action(input);
		gen_result();
		reset_memory();
	}
}
