#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

enum {real_, complex_} number_system;

enum action_
{
	EXIT,
	NUMBER,
	ADD,
	SUBSTRACT,
	MULTIPLY,
	DIVIDE,
	EXP,
	LN,
	POW,
	LOG,
	COS,
	SIN,
	TAN,
	SEC,
	COSEC,
	COT,
	ACOS,
	ASIN,
	ATAN,
	ASEC,
	ACOSEC,
	ACOT
} *action = NULL;

void push_(void *);
void pop_(void);
struct
{
	void *ptr;
	int size;
	void (*push)(void *);
	void (*pop)(void);
} calculation_stack = {NULL, 0, push_, pop_};

struct
{
	void *ptr;
	int index;
} num_stack = {NULL, 0};

int choose_number_system(char *);
int is_equal_str(const char *str1, const char *str2);
char *get_line(void);
size_t get_num_stack_size(char *);
int get_num_action(char *);
void get_num_stack(char *);
void get_action(char *);
void get_result(void);
void free_memory(void);

int main(int argc, char **argv)
{
	if(choose_number_system(argv[1]) == EXIT_FAILURE){return EXIT_FAILURE;}
	char *input;
	while(!is_equal_str((input = get_line()), "exit"))
	{
		if(choose_number_system(input) == EXIT_SUCCESS){continue;}
		num_stack.ptr = malloc(get_num_stack_size(input));
		action = (enum action_ *)malloc(get_num_action(input)*sizeof(enum action_));
		get_num_stack(input);
		get_action(input);
		get_result();
		free_memory();
	}

	return 0;
}

int choose_number_system(char *str)
{
	if(is_equal_str(str, "real"))
	{
		number_system = real_;
	} else if(is_equal_str(str, "complex"))
	{
		number_system = complex_;
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
		calculation_stack.ptr = realloc(calculation_stack.ptr, ++calculation_stack.size*(sizeof(double)));
		((double *)calculation_stack.ptr)[calculation_stack.size - 1] = *((double *)numptr);
	} else if(number_system == complex_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, ++calculation_stack.size*(sizeof(complex double)));
		((complex double *)calculation_stack.ptr)[calculation_stack.size - 1] = *((complex double *)numptr);
	}
	return;
}

void pop(void)
{
	if(number_system == real_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, --calculation_stack.size*(sizeof(double)));
	} else if(number_system == complex_)
	{
		calculation_stack.ptr = realloc(calculation_stack.ptr, --calculation_stack.size*(sizeof(complex double)));
	}
	return;
}

int is_equal_str(const char *str1, const char *str2)
{
	int i = 0;
	for(int i = 0; str1[i] != '\0'; ++i)
	{
		i += (str1[i] != str2[i]);
	}
	return !i;
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

void free_memory(void)
{
	free(num_stack.ptr);
	num_stack.ptr = NULL;
	free((void *)action);
	action = NULL;
	free(calculation_stack.ptr);
	calculation_stack.ptr = NULL;
}
