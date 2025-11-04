#ifndef SOLVE_H
#define SOLVE_H

#include <stdio.h>
#include <limits.h>

int handler_min_cc(char* number, int length);
int perevod_min_cc_to_ten_cc(char* number, int length, int min_cc);

int solve(FILE* input, FILE* output);

#endif