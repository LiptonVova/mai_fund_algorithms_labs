#include "../include/functions.h"
#include <math.h>

double function_a(double x, double eps) {
    if (fabs(x - 0.0) < eps) {
        return 1.0;
    }
    return log(1 + x)/x;
}

double function_b(double x, double eps) {
    return exp(-(x*x) / 2.0);
}

double function_c(double x, double eps) {
    return -log(1 - x);
}

double function_d(double x, double eps) {
    return pow(x, x);
}

double solve(double (*f)(double, double),double eps, double a, double b) {
    double step = b - a;
    double prev_value = 0.5 * (f(a, eps) + f(b, eps)) * step; // полусумма оснований на высоту
    double value = prev_value;
    int n = 1;
    double x;

    do {
        prev_value = value;
        n *= 2;
        value = 0;
        step = (b - a) / n;
        x = 0;
        for (double i = 0; i < n; i++) {
            value += (0.5 * (f(x, eps) + f(x + step, eps)));
            x += step;
        }
        value *= step;
    } while (fabs(value - prev_value) >= eps);

    return value;
}