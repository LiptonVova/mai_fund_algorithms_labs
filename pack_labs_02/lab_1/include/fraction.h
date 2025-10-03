#ifndef FRACTION_H
#define FRACTION_H



#include "math_function.h"



int* reducing_a_fraction(const int numerator, const int denominator, error_code_t* error);
void numerator_and_denominator_from_fraction(const double number, int*numerator, int*denominator, error_code_t* error);


#endif