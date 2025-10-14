#ifndef FRACTION_H
#define FRACTION_H



#include "math_function.h"



long long* reducing_a_fraction(const long long numerator, const long long denominator, error_code_t* error);
void numerator_and_denominator_from_fraction(const double number, long long*numerator, long long*denominator, error_code_t* error);


#endif