#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

enum {real_, complex_} number_system;

int is_equal_str(const char *str1, const char *str2);
char *get_line(void);

int main(int argc, char **argv)
{
	if(is_equal_str(argv[1], "real")){number_system = real_;}
	else if(is_equal_str(argv[1], "complex")){number_system = complex_;}
	else {return 1;}

	char *input;
	while(!is_equal_str((input = get_line()), "exit"))
	{
		;
	}

	return 0;
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
	while((str[size - 1] = getchar()) != '\n')
	{
		str = (char *)realloc((void *)str, ++size);
	}
	return str;
}
