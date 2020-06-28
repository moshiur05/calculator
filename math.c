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

double add(double, double);
complex double cadd(complex double, complex double);
double substract(double, double);
complex double csubstract(complex double, complex double);
double multiply(double, double);
complex double cmultiply(complex double, complex double);
double divide(double, double);
complex double cdivide(complex double, complex double);
double sec(double);
complex double csec(complex double);
double cosec(double);
complex double ccosec(complex double);
double cot(double);
complex double ccot(complex double);
double asec(double);
complex double casec(complex double);
double acosec(double);
complex double cacosec(complex double);
double acot(double);
complex double cacot(complex double);

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
