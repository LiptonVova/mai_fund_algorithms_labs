#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "config.h"
#include "validate.h"

error_code_t create_input_output_files(FILE **input, FILE **output, int argc, char *argv[]);
error_code_t read_data_from_input_file(PostOffice *post_offices, bool *work_post_offices, FILE *input_file);


bool move_max_priority_letter_from_postoffice(PostOffice *post_offices, bool *work_post_offices, \
                                                unsigned int id_post_office, FILE *output_file);

void print_info();

void print_usage();

void print_letter(Letter *letter);
void print_all_letters(Vector_LetterPtr *vector_all_letters);

#endif