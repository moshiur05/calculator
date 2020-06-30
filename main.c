void run_calc(void);
int choose_number_system(char *);

int main(int argc, char **argv)
{
	if(argc == 2){choose_number_system(argv[1]);}
	run_calc();
	return 0;
}
