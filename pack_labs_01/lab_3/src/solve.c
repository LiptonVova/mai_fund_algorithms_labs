#include "../include/solve.h"
#include <math.h>
#include <stdlib.h>
#include <stddef.h>



double* solve_quadratic_equation(double e, double a, double b, double c) {
    double * result = malloc(sizeof(double) * 2);

    if (fabs(a) < e) {
        if (fabs(b) < e) {
            if (fabs(c) < e) {
                result[0] = 1.0/0.0; // INF 
                result[1] = 1.0/0.0; 
            }
            else {
                result[0] = NAN;
                result[1] = NAN;
            }
        }
        else {
            double x = -c/b;
            result[0] = x;
            result[1] = x;
        }

        return result;
    }

    double d = b * b - 4 * a * c;
    if (d < e) {
        result[0] = NAN;
        result[1] = NAN;
    }

    else if (fabs(d) < e) {
        double x = -b/(2 * a);
        result[0] = x;
        result[1] = x;
    }

    else {
        double sqrt_d = sqrt(d);
        double x1 = (-b + sqrt_d) / (2 * a);
        double x2 = (-b - sqrt_d) / (2 * a);

        if (x2 > x1) {
            double temp = x1;
            x1 = x2;
            x2 = temp;
        }

        result[0] = x1;
        result[1] = x2;
    }

    return result;
}

int check_right_triangle(double e, double a, double b, double c) {
    double max_number;
    double other_num_1, other_num_2;
    if ( (c - a) >= e && (c - b) >= e) {
        max_number = c;
        other_num_1 = a;
        other_num_2 = b;
    }

    else if ( (b - a) >= e && (b - c) >= e) {
        max_number = b;
        other_num_1 = a;
        other_num_2 = c;
    }

    else {
        max_number = a;
        other_num_1 = b;
        other_num_2 = c;
    }

    return ( fabs(other_num_1 * other_num_1 + other_num_2 * other_num_2 - max_number * max_number) < e );
}