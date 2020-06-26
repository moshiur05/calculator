#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

enum {real_, complex_} number_system;

void push_real(double);
double pop_real(void);
struct
{
	double *ptr;
	int size;
	void (*push)(double);
	double (*pop)(void);
} calculation_stack_real = {NULL, 0, push_real, pop_real};

void push_complex(complex double);
complex double pop_complex(void);
struct
{
	complex double *ptr;
	int size;
	void (*push)(complex double);
	complex double (*pop)(void);
} calculation_stack_complex = {NULL, 0, push_complex, pop_complex};

int choose_number_system(char *);
int is_equal_str(const char *str1, const char *str2);
char *get_line(void);

int main(int argc, char **argv)
{
	if(choose_number_system(argv[1]) == EXIT_FAILURE){return EXIT_FAILURE;}
	char *input;
	while(!is_equal_str((input = get_line()), "exit"))
	{
		if(choose_number_system(input) == EXIT_SUCCESS){continue;}
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

void push_real(double var)
{
	calculation_stack_real.ptr = (double *)realloc(calculation_stack_real.ptr, ++calculation_stack_real.size);
	calculation_stack_real.ptr[calculation_stack_real.size - 1] = var;
	return;
}

double pop_real(void)
{
	double var = calculation_stack_real.ptr[--calculation_stack_real.size];
	calculation_stack_real.ptr = (double *)realloc(calculation_stack_real.ptr, calculation_stack_real.size);
	return var;
}

void push_complex(complex double var)
{
	calculation_stack_complex.ptr = (complex double *)realloc(calculation_stack_complex.ptr, ++calculation_stack_complex.size);
	calculation_stack_complex.ptr[calculation_stack_complex.size - 1] = var;
	return;
}

complex double pop_complex(void)
{
	complex double var = calculation_stack_complex.ptr[--calculation_stack_complex.size];
	calculation_stack_complex.ptr = (complex double *)realloc(calculation_stack_complex.ptr, calculation_stack_complex.size);
	return var;
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
	str = malloc(size);
	printf("=> ");
	while((str[size - 1] = getchar()) != '\n')
	{
		str = (char *)realloc((void *)str, ++size);
	}
	str[size - 1] = '\0';
	return str;
}
