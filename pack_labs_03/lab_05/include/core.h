#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "config.h"
#include "utils.h"
#include "validate.h"
#include "handles.h"


typedef struct {
    PostOffice *post_offices;
    bool *work_post_offices;
    FILE *input_file;
    FILE *output_file;
    Vector_LetterPtr* vector_all_letters;
    pthread_mutex_t* mutex_data;
    bool* thread_live;
} ThreadArgs;


void start_mail_application(int argc, char *argv[]);


#endif