#include "../include/output.h"
#include <stdio.h>
#include <math.h>


void print_usage() {
    char * usage = "./main.out [flag] [arguments]";
    char * flagQ = "-q, /q";
    char * flagM = "-m, /m";
    char * flagT = "-t, /t";
    char * descriptionQ = "arguments: four float numbers";
    char * descriptionM = "arguments: two int numbers";
    char * descriptionT = "arguments: four float numbers";
    printf("%s\n\n", usage);
    printf("flags and arguments: \n");

    printf("%s %20s\n", flagQ, descriptionQ);
    printf("%s %20s\n", flagM, descriptionM);
    printf("%s %20s\n", flagT, descriptionT);
}


void print_quadratic_equation(double* result, int precision, double a, double b, double c) {
    printf("Уравнение: (%.*f)x^2 + (%.*f)x + (%.*f) = 0\n", precision, a, precision, b, precision, c);
    if (isnan(result[0])) {
        printf("Корней в действительных числах нет\n\n");
    }
    else if (isinf(result[0])) {
        printf("Уравнение имеет бесконечное количество решений\n\n");
    }
    else {
        printf("Корни : x1 = %.*f, x2 = %.*f\n\n", precision, result[0], precision, result[1]);
    }
}