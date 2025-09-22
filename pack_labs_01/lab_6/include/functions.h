#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double function_a(double x, double eps);
double function_b(double x, double eps);
double function_c(double x, double eps);
double function_d(double x, double eps);


double solve(double (*f)(double, double), double eps, double a, double b);


#endif