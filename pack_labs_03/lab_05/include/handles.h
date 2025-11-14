#ifndef HANDLES_H
#define HANDLES_H

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>


#include "config.h"
#include "validate.h"


error_code_t handle_add_postoffice(PostOffice *post_offices, bool *work_post_offices, \
                                FILE *output_file, pthread_mutex_t *mutex_data);

error_code_t handle_delete_postoffice(PostOffice *post_offices, bool *work_post_offices, FILE *output_file, \
                                    Vector_LetterPtr *vector_all_letters, pthread_mutex_t *mutex_data);

error_code_t handle_add_letter(PostOffice *post_offices, bool *work_post_offices, FILE *output_file, \
                                Vector_LetterPtr* vector_all_letters, pthread_mutex_t *mutex_data);

void handle_get_letter(PostOffice *post_offices, bool *work_post_offices, Vector_LetterPtr *vector_all_letters, \
                                FILE *output_file, pthread_mutex_t *mutex_data);


#endif