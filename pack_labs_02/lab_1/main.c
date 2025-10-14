#include "include/check_finite_fraction.h"
#include <stdio.h>

int main() {
    error_code_t error = SUCCESS;
    
    printf("1.\n");
    printf("   Дроби: 0.5, 0.25, 0.125, 0.75, 0.375, 1/3, 1/2\n");
    printf("   Система счисления: 2\n");

    bool* result1 = define_list_of_finite_fraction(2, &error, 7, 0.5, 0.25, 0.125, 0.75, 0.375, 1.0/3, 1.0/2.0);
    printf("   Результат:\n");
    printf("     0.5 - %s\n", result1[0] ? "конечная" : "бесконечная");
    printf("     0.25 - %s\n", result1[1] ? "конечная" : "бесконечная");
    printf("     0.125 - %s\n", result1[2] ? "конечная" : "бесконечная");
    printf("     0.75 - %s\n", result1[3] ? "конечная" : "бесконечная");
    printf("     0.375 - %s\n", result1[4] ? "конечная" : "бесконечная");
    printf("     1/3 - %s\n", result1[5] ? "конечная" : "бесконечная");
    printf("     1/2 - %s\n", result1[6] ? "конечная" : "бесконечная");
    printf("\n");
    free(result1);
    
    printf("2.\n");
    printf("   Дроби: 1.4, 1/3, 0.241, 1/2555555\n");
    printf("   Система счисления: 2555555\n");

    
    bool* result2 = define_list_of_finite_fraction(2555555, &error, 4, 1.4, 1.0/3, 0.241, 1.0/2555555);
    if (result2 != NULL) {
        printf("   Результат:\n");
        printf("     1.4 - %s\n", result2[0] ? "конечная" : "бесконечная");
        printf("     1/3 - %s\n", result2[1] ? "конечная" : "бесконечная");
        printf("     0.241 - %s\n", result2[2] ? "конечная" : "бесконечная");
        printf("     1/2555555 - %s\n", result2[3] ? "конечная" : "бесконечная");
        free(result2);
    }
    printf("\n");
    
    printf("3.\n");
    printf("   Дроби: 0.125, 0.015625, 0.5 1/8\n");
    printf("   Система счисления: 8\n");
    
    bool* result3 = define_list_of_finite_fraction(8, &error, 4, 0.125, 0.015625, 0.5, 1.0/8);
    printf("   Результат:\n");
    printf("     0.125 - %s\n", result3[0] ? "конечная" : "бесконечная");
    printf("     0.015625 - %s\n", result3[1] ? "конечная" : "бесконечная");
    printf("     0.5 - %s\n", result3[2] ? "конечная" : "бесконечная");
    printf("     1/8 - %s\n", result3[3] ? "конечная" : "бесконечная");
    printf("\n");
    free(result3);
    
    printf("4.\n");
    printf("   Дроби: 0.125, 0.25, 0.5, 1/256, 1/5\n");
    printf("   Система счисления: 256\n");
    

    bool* result4 = define_list_of_finite_fraction(256, &error, 4, 0.125, 0.25, 0.5, 1.0/5);
    printf("   Результат:\n");
    printf("     0.125 - %s\n", result4[0] ? "конечная" : "бесконечная");
    printf("     0.25 - %s\n", result4[1] ? "конечная" : "бесконечная");
    printf("     0.5 - %s\n", result4[2] ? "конечная" : "бесконечная");
    printf("     1/5 - %s\n", result4[3] ? "конечная" : "бесконечная");
    printf("\n");
    free(result4);
    
    printf("5.\n");
    printf("   Дроби: 0.11111111111111111111111, 0.1, 0.2, 0.75\n");
    printf("   Система счисления: 10\n");
    
    bool* result5 = define_list_of_finite_fraction(10, &error, 4, 0.11111111111111111111111, 0.1, 0.2, 0.75);
    printf("   Результат:\n");
    printf("     0.11111111111111111111111 - %s\n", result5[0] ? "конечная" : "бесконечная");
    printf("     0.1 - %s\n", result5[1] ? "конечная" : "бесконечная");
    printf("     0.2 - %s\n", result5[2] ? "конечная" : "бесконечная");
    printf("     0.75 - %s\n", result5[3] ? "конечная" : "бесконечная");
    printf("\n");
    free(result5);
    
    return 0;
}