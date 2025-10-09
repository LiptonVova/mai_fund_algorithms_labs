#ifndef TRANSLATE_BASE_TO_TEN_H
#define TRANSLATE_BASE_TO_TEN_H

#include "additional_functions.h"
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

void handle_base_to_ten(error_code_t *error, char* buffer, va_list args, bool upper);

#endif