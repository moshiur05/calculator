#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

int compare_str(const char *, const char *);
char *get_line(void);

int main(int argc, char **argv)
{
	enum {real_num, complex_num} number_system;
	if(compare_str(argv[1], "real")){number_system = real_num;}
	else if(compare_str(argv[1], "complex")){number_system = complex_num;}
	else{return 1;}
	
	char *input = get_line();
	while(compare_str(input, "exit"))
	{
		;
	}
	
	return 0;
}
