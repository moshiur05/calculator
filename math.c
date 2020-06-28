#include "stacks_and_enums.h"
#include <math.h>
#include <complex.h>
#include <stdlib.h>

void exec_svar_func(double (*funcr)(double), complex double (*funcc)(complex double))
{
	extern enum number_system_ number_system;
	extern struct calculation_stack_ calculation_stack;
	extern int offset;

	void *numptr = malloc((size_t)offset);
	switch(number_system)
	{
		case real_ :
			*((double *)numptr) = funcr(((double *)calculation_stack.ptr)[calculation_stack.index]);
			break;
		case complex_ :
			*((complex double*)numptr) = funcc(((complex double*)calculation_stack.ptr)[calculation_stack.index]);
			break;
	}
	calculation_stack.pop();
	calculation_stack.push(numptr);
	free(numptr);
	return;
}

void exec_dvar_func(double (*funcr)(double, double), complex double (*funcc)(complex double, complex double))
{
	extern enum number_system_ number_system;
	extern int offset;
	extern struct calculation_stack_ calculation_stack;

	void *numptr = malloc((size_t)offset);
	switch(number_system)
	{
		case real_ :
			*((double *)numptr) = funcr(((double *)calculation_stack.ptr)[calculation_stack.index], ((double *)calculation_stack.ptr)[calculation_stack.index - 1]);
			break;
		case complex_ :
			*((complex double *)numptr) = funcc(((complex double *)calculation_stack.ptr)[calculation_stack.index], ((complex double *)calculation_stack.ptr)[calculation_stack.index - 1]);
			break;
	}
	calculation_stack.pop();
	calculation_stack.pop();
	calculation_stack.push(numptr);
	free(numptr);
	return;
}

double add(double num1, double num2){return num1 + num2;}
complex double cadd(complex double num1, complex double num2){return num1 + num2;}
double substract(double num1, double num2){return num1 - num2;}
complex double csubstract(complex double num1, complex double num2){return num1 - num2;}
double multiply(double num1, double num2){return num1*num2;}
complex double cmultiply(complex double num1, complex double num2){return num1*num2;}
double divide(double num1, double num2){return num1/num2;}
complex double cdivide(complex double num1, complex double num2){return num1/num2;}
double sec(double num){return 1/cos(num);}
complex double csec(complex double num){return 1/ccos(num);}
double cosec(double num){return 1/sin(num);}
complex double ccosec(complex double num){return 1/csin(num);}
double cot(double num){return 1/tan(num);}
complex double ccot(complex double num){return 1/ctan(num);}
double asec(double num){return acos(1/num);}
complex double casec(complex double num){return cacos(1/num);}
double acosec(double num){return asin(1/num);}
complex double cacosec(complex double num){return casin(1/num);}
double acot(double num){return atan(1/num);}
complex double cacot(complex double num){return catan(1/num);}

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
			exec_dvar_func(add, cadd);
			break;
		case SUBSTRACT :
			exec_dvar_func(substract, csubstract);
			break;
		case MULTIPLY :
			exec_dvar_func(multiply, cmultiply);
			break;
		case DIVIDE :
			exec_dvar_func(divide, cdivide);
			break;
		case EXP :
			exec_svar_func(exp, cexp);
			break;
		case LN :
			exec_svar_func(log, clog);
			break;
		case POW :
			exec_dvar_func(pow, cpow);
			break;
		case LOG :
			break;
		case COS :
			exec_svar_func(cos, ccos);
			break;
		case SIN :
			exec_svar_func(sin, csin);
			break;
		case TAN :
			exec_svar_func(tan, ctan);
			break;
		case SEC :
			exec_svar_func(sec, csec);
			break;
		case COSEC :
			exec_svar_func(cosec, ccosec);
			break;
		case COT :
			exec_svar_func(cot, ccot);
			break;
		case ACOS :
			exec_svar_func(acos, cacos);
			break;
		case ASIN :
			exec_svar_func(asin, casin);
			break;
		case ATAN :
			exec_svar_func(atan, catan);
			break;
		case ASEC :
			exec_svar_func(asec, casec);
			break;
		case ACOSEC :
			exec_svar_func(acosec, cacosec);
			break;
		case ACOT :
			exec_svar_func(acot, cacot);
			break;
		case EXIT :
			break;
	}
}
