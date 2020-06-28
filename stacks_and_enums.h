#include <stdio.h>

#ifndef STACKS
#define STACKS

void push_(void *);
void pop_(void);
struct calculation_stack_
{
	void *ptr;
	int index;
	void (*push)(void *);
	void (*pop)(void);
};

struct num_stack_
{
	void *ptr;
	int index;
};
#endif

#ifndef ENUMS
#define ENUMS
enum number_system_ {real_, complex_};

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
};
#endif
