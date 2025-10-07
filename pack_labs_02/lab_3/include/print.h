#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "additional_functions.h"
#include "specifiers.h"


int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(char *buffer, const char *format, ...);

#endif