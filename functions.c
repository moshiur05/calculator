#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>

enum number_system_ number_system = real_;
int offset = 0;
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
	extern enum number_system_ number_system;
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

complex double strtocmplx(char *input, char **endptr)
{
	complex double cmplx_num;
	cmplx_num = strtod(input, endptr);
	cmplx_num += strtod(*endptr, endptr)*1i;
	return cmplx_num;
}

void *getnum_and_update_index(char *input, int *intptr)
{
	extern enum number_system_ number_system;
	static void *vptr = NULL;
	free(vptr);
	char *endptr;
	if(number_system == real_)
	{
		vptr = malloc(sizeof(double));
		*((double *)vptr) = strtod(input, &endptr);
	} else if(number_system == complex_)
	{
		vptr = malloc(sizeof(complex double));
		*((complex double *)vptr) = strtocmplx(input, &endptr);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	*intptr += abs((int)((long int)endptr - (long int)input));
	return vptr;
}

void gen_num_stack(char *input)
{
	extern struct num_stack_ num_stack;
	for(int i = 0; input[i] != '\0'; ++i)
	{
		if(isdigit(input[i]))
		{
			num_stack.push(getnum_and_update_index(input + i, &i));
		}
	}
	num_stack.index = 0;
	return;
}

void gen_action(char *input)
{
	extern enum action_ *action;
	action = (enum action_ *)malloc(3*sizeof(enum action_));
	action[0] = NUMBER;
	action[1] = NUMBER;
	action[2] = ADD;
	action[3] = EXIT;
	return;
}

void do_action(int);
void gen_result(void)
{
	extern enum number_system_ number_system;
	extern enum action_ *action;
	extern struct calc_stack_ calc_stack;
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
	extern struct calc_stack_ calc_stack;
	extern enum action_ *action;
	extern struct num_stack_ num_stack;
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
