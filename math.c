#include "stacks_and_enums.h"

void add__(void);
void substract__(void);
void multiply__(void);
void divide__(void);
void exp__(void);
void ln__(void);
void pow__(void);
void log__(void);
void cos__(void);
void sin__(void);
void tan__(void);
void sec__(void);
void cosec__(void);
void cot__(void);
void acos__(void);
void asin__(void);
void atan__(void);
void asec__(void);
void acosec__(void);
void acot__(void);

struct math_ math = {add__, substract__, multiply__, divide__, exp__, ln__, pow__, log__,
	cos__, sin__, tan__, sec__, cosec__, cot__, acos__, asin__, atan__, asec__, acosec__, acot__};

void do_action(int i)
{
	extern enum action_ *action;
	extern int offset;
	extern struct calculation_stack_ calculation_stack;
	extern struct num_stack_ num_stack;
	switch(action[i])
	{
		case NUMBER :
			calculation_stack.push((void *)((char *)num_stack.ptr + offset*num_stack.index++));
			break;
		case ADD :
			math.add();
			break;
		case SUBSTRACT :
			math.substract();
			break;
		case MULTIPLY :
			math.multiply();
			break;
		case DIVIDE :
			math.divide();
			break;
		case EXP :
			math.exp();
			break;
		case LN :
			math.ln();
			break;
		case POW :
			math.pow();
			break;
		case LOG :
			math.log();
			break;
		case COS :
			math.cos();
			break;
		case SIN :
			math.sin();
			break;
		case TAN :
			math.tan();
			break;
		case SEC :
			math.sec();
			break;
		case COSEC :
			math.cosec();
			break;
		case COT :
			math.cot();
			break;
		case ACOS :
			math.acos();
			break;
		case ASIN :
			math.asin();
			break;
		case ATAN :
			math.atan();
			break;
		case ASEC :
			math.asec();
			break;
		case ACOSEC :
			math.acosec();
			break;
		case ACOT :
			math.acot();
			break;
		case EXIT :
			break;
	}
}
