#include "../include/core.h"


error_code_t start_interactive_console(PostOffice *post_offices, bool *work_post_offices, FILE *input_file, \
                                        FILE *output_file, Vector_LetterPtr* vector_all_letters) {
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
                error = handle_add_postoffice(post_offices, work_post_offices, output_file); 
                break;
            }
            case (DELETE_POSTOFFICE): {
                error = handle_delete_postoffice(post_offices, work_post_offices, output_file);
                break;
            }
            case (ADD_LETTER): {
                error = handle_add_letter(post_offices, work_post_offices, output_file, vector_all_letters);
                break;
            }
            case (GET_LETTER): {
                handle_get_letter(work_post_offices, vector_all_letters, output_file);
                break;
            }
            case (PRINT_ALL_LETTERS): {
                print_all_letters(vector_all_letters);
                break;
            }
            case (START_SENDING): {
                handle_start_sending(post_offices, work_post_offices, output_file);
                break;
            }
            case (READ_DATA_FROM_INPUT_FILE): {
                // считать данные из файла
                error = read_data_from_input_file(post_offices, work_post_offices, input_file);
                if (error != SUCCESS) return error;
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

    return SUCCESS;
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

    error = start_interactive_console(post_offices, work_post_offices, input_file, output_file, &vector_all_letters);
}
