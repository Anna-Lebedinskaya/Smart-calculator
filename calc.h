#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

double str_to_double(char* str, int* pos_i);
Stack* pars(char* str, double* x);
Stack* get_polish_notation(Stack* top);
double unar_func(char oper, double x);
double binar_func(char oper, double x, double y);
double get_res(Stack* top, int* error);
int main_func(char* str, double* x, double* result);
int credit_func(double sum, int month, double proc, double* payment,
                double* over, double* total, int type);

#endif  // SRC_CALC_H_
