#ifndef OVERSCANF_H
#define OVERSCANF_H

#include <stdio.h>
#include <stdarg.h>
#include "specifiers.h"
#include "additional_functions.h"

int oversscanf(const char *buffer, const char *format, ...);
int overfscanf(FILE *stream, const char *format, ...);


#endif