#include <stdio.h>

#ifndef MATH_MODULE
#define MATH_MODULE

struct math_
{
	void (*add)(void);
	void (*substract)(void);
	void (*multiply)(void);
	void (*divide)(void);
	void (*exp)(void);
	void (*ln)(void);
	void (*pow)(void);
	void (*log)(void);
	void (*cos)(void);
	void (*sin)(void);
	void (*tan)(void);
	void (*sec)(void);
	void (*cosec)(void);
	void (*cot)(void);
	void (*acos)(void);
	void (*asin)(void);
	void (*atan)(void);
	void (*asec)(void);
	void (*acosec)(void);
	void (*acot)(void);
};

#endif

#ifndef STACKS
#define STACKS

void push_(void *);
void pop_(void);
struct calculation_stack_
{
	void *ptr;
	int size;
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
