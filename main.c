#include "stacks_and_enums.h"
#include <stdlib.h>

int choose_number_system(char *);
int is_equal_str(const char *str1, const char *str2);
char *get_line(void);
void gen_num_stack(char *);
void gen_action(char *);
void gen_result(void);
void reset_memory(void);

int main(int argc, char **argv)
{
	if(choose_number_system(argv[1]) == EXIT_FAILURE){return EXIT_FAILURE;}
	char *input;
	while(!is_equal_str((input = get_line()), "exit"))
	{
		if(choose_number_system(input) == EXIT_SUCCESS){continue;}
		gen_num_stack(input);
		gen_action(input);
		gen_result();
		reset_memory();
	}

	return 0;
}
