#include "../include/core.h"

void* handle_start_sending(void *args) {
    ThreadArgs *thread_args = (ThreadArgs*)args;
    while (*(thread_args->thread_live) == true) {
        for (unsigned int i = 0; i < MAX_SIZE_POST_OFFICES; ++i) {
            if (thread_args->work_post_offices[i] == true) {
                move_max_priority_letter_from_postoffice(thread_args->post_offices, thread_args->work_post_offices, \
                                                    i, thread_args->output_file, thread_args->mutex_data);
            }
        }
        sleep(10);
    }
    return NULL;
}

void* start_interactive_console(void *args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    printf("-- инфо: запускается консоль взаимодействия для домохозяек с моей программой\n");

    printf("Добро пожаловать в почту Вовы Рыбина!\n");
    int choice = 0;
    error_code_t error = SUCCESS;
    do {
        print_info();
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case (ADD_POSTOFFICE): {
                error = handle_add_postoffice(thread_args->post_offices, thread_args->work_post_offices, \
                                                thread_args->output_file, thread_args->mutex_data);
                if (error != SUCCESS) {
                    *(thread_args->thread_live) = false;
                    return NULL;
                }
                break;
            }
            case (DELETE_POSTOFFICE): {
                error = handle_delete_postoffice(thread_args->post_offices, thread_args->work_post_offices, \
                                                thread_args->output_file, thread_args->mutex_data);
                if (error != SUCCESS) {
                    *(thread_args->thread_live) = false;
                    return NULL;
                }
                break;
            }
            case (ADD_LETTER): {
                error = handle_add_letter(thread_args->post_offices, thread_args->work_post_offices, \
                                    thread_args->output_file, thread_args->vector_all_letters, thread_args->mutex_data);
                if (error != SUCCESS) {
                    *(thread_args->thread_live) = false;
                    return NULL;
                }
                break;
            }
            case (GET_LETTER): {
                handle_get_letter(thread_args->work_post_offices, thread_args->vector_all_letters, \
                                    thread_args->output_file, thread_args->mutex_data);
                if (error != SUCCESS) {
                    *(thread_args->thread_live) = false;
                    return NULL;
                }
                break;
            }
            case (PRINT_ALL_LETTERS): {
                print_all_letters(thread_args->vector_all_letters, thread_args->mutex_data); 
                if (error != SUCCESS) {
                    *(thread_args->thread_live) = false;
                    return NULL;
                }
                break;
            }
            case (READ_DATA_FROM_INPUT_FILE): {
                // считать данные из файла
                error = read_data_from_input_file(thread_args->post_offices, thread_args->work_post_offices, \
                                thread_args->input_file, thread_args->mutex_data);
                if (error != SUCCESS) {
                    *(thread_args->thread_live) = false;
                    return NULL;
                }
                break;
            }
            case (EXIT): {
                break;
            }
            default: {
                printf("-- ошибка: неизвестная команда\n");
                printf("-- подсказка: вводите число команды\n");
                break;
            }
        }
    } while (choice != EXIT);

    *(thread_args->thread_live) = false;
    return NULL;
}

void start_mail_application(int argc, char *argv[]) {
    // валидация входных данных
    error_code_t error = validate_count_arguments(argc);
    if (error != SUCCESS) return;

    printf("-- инфо: идет запуск программы\n");

    // обработка входных данных
    FILE* input_file;
    FILE* output_file;
    error = create_input_output_files(&input_file, &output_file, argc, argv);
    if (error != SUCCESS) return;
   
    // создание основной структуры данных
    PostOffice post_offices[MAX_SIZE_POST_OFFICES]; // массив отделений
    bool work_post_offices[MAX_SIZE_POST_OFFICES]; // массив, в котором помечены работающие и неработающие отделения
    Vector_LetterPtr vector_all_letters = create_vector_impl(); // вектор всех писем

    pthread_t interaction_with_user, sending_letters;
    pthread_mutex_t mutex_data = PTHREAD_MUTEX_INITIALIZER;

    ThreadArgs args;
    args.post_offices = post_offices;
    args.work_post_offices = work_post_offices;
    args.input_file = input_file;
    args.output_file = output_file;
    args.vector_all_letters = &vector_all_letters;
    args.mutex_data = &mutex_data;
    bool thread_live = true;
    args.thread_live = &thread_live;

    pthread_create(&interaction_with_user, NULL, start_interactive_console, &args);
    pthread_create(&sending_letters, NULL, handle_start_sending, &args);

    pthread_join(interaction_with_user, NULL);
    pthread_join(sending_letters, NULL);

    pthread_mutex_destroy(&mutex_data);
}
