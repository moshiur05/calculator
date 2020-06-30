#include "definitions.h"
#include <math.h>
#include <complex.h>
#include <stdlib.h>

void exec_svar_func(double (*funcr)(double), complex double (*funcc)(complex double))
{
	extern enum number_system_ number_system;
	extern struct calc_stack_ calc_stack;
	extern int offset;

	void *numptr = malloc((size_t)offset);
	switch(number_system)
	{
		case real_ :
			*((double *)numptr) = funcr(((double *)calc_stack.ptr)[calc_stack.index]);
			break;
		case complex_ :
			*((complex double*)numptr) = funcc(((complex double*)calc_stack.ptr)[calc_stack.index]);
			break;
	}
	calc_stack.pop();
	calc_stack.push(numptr);
	free(numptr);
	return;
}

void exec_dvar_func(double (*funcr)(double, double), complex double (*funcc)(complex double, complex double))
{
	extern enum number_system_ number_system;
	extern int offset;
	extern struct calc_stack_ calc_stack;

	void *numptr = malloc((size_t)offset);
	switch(number_system)
	{
		case real_ :
			*((double *)numptr) = funcr(((double *)calc_stack.ptr)[calc_stack.index], ((double *)calc_stack.ptr)[calc_stack.index - 1]);
			break;
		case complex_ :
			*((complex double *)numptr) = funcc(((complex double *)calc_stack.ptr)[calc_stack.index], ((complex double *)calc_stack.ptr)[calc_stack.index - 1]);
			break;
	}
	calc_stack.pop();
	calc_stack.pop();
	calc_stack.push(numptr);
	free(numptr);
	return;
}

double add(double num1, double num2){return num1 + num2;}
double substract(double num1, double num2){return num1 - num2;}
double multiply(double num1, double num2){return num1*num2;}
double divide(double num1, double num2){return num1/num2;}
double sec(double num){return 1/cos(num);}
double cosec(double num){return 1/sin(num);}
double cot(double num){return 1/tan(num);}
double asec(double num){return acos(1/num);}
double acosec(double num){return asin(1/num);}
double acot(double num){return atan(1/num);}
complex double cadd(complex double num1, complex double num2){return num1 + num2;}
complex double csubstract(complex double num1, complex double num2){return num1 - num2;}
complex double cmultiply(complex double num1, complex double num2){return num1*num2;}
complex double cdivide(complex double num1, complex double num2){return num1/num2;}
complex double csec(complex double num){return 1/ccos(num);}
complex double ccosec(complex double num){return 1/csin(num);}
complex double ccot(complex double num){return 1/ctan(num);}
complex double casec(complex double num){return cacos(1/num);}
complex double cacosec(complex double num){return casin(1/num);}
complex double cacot(complex double num){return catan(1/num);}
complex double cabs_(complex double num){return (complex double)(cabs(num));}

void do_action(int i)
{
	extern enum action_ *action;
	extern int offset;
	extern struct calc_stack_ calc_stack;
	extern struct num_stack_ num_stack;
	switch(action[i])
	{
		case NUMBER :
			calc_stack.push((void *)((char *)num_stack.ptr + offset*num_stack.index++));
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
		case ABS :
			exec_svar_func(fabs, cabs_);
		case EXP :
			exec_svar_func(exp, cexp);
			break;
		case LN :
			exec_svar_func(log, clog);
			break;
		case POW :
			exec_dvar_func(pow, cpow);
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
