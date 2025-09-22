#include <stdio.h>
#include <stdlib.h>

#include "include/functions.h"
#include "include/validate.h"


enum {
    SUCCESS,
    ERROR_WRONG_ARGUMENTS,
    ERROR_WRONG_EPSILON,
};


int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Введите точность измерений\n");
        printf("usage: ./main.out epsilon\n");
        return ERROR_WRONG_ARGUMENTS;
    }

    int flag = validate_double(argv[1]);
    if (flag == 0) {
        printf("Введите вещественное число большее нуля\n");
        printf("usage: ./main.out epsilon\n");
        return ERROR_WRONG_EPSILON;
    }


    double eps = atof(argv[1]);

    double a = 0.0, b = 1.0;
    double b_for_answer_c = 0.99999999;

    double answer_a = solve(function_a, eps, a, b);
    double answer_b = solve(function_b, eps, a, b);
    double answer_c = solve(function_c, eps, a, b_for_answer_c);
    double answer_d = solve(function_d, eps, a, b);
    
    printf("интеграл ln(1+x)/x равен %lf\n", answer_a);
    printf("интеграл e^(-x^2/2) равен %lf\n", answer_b);
    printf("интеграл ln(1/(1-x)) равен %lf\n", answer_c);
    printf("интеграл x^x равен %lf\n", answer_d);

}