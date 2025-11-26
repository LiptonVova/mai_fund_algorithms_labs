#include "../include/utils.h"


void pop_from_heap_deleted_letter(PostOffice *post_offices, Letter *letter) {
    // функция удаляет из почтового отделения где сейчас находится это письмо, это письмо

    unsigned int id_letter = letter->id;
    unsigned int id_post_office = letter->id_cur_postoffice;

    Vector_LetterPtr buffer = create_vector_impl();
    while (post_offices[id_post_office].letters.size != 0) {
        Letter *letter = peek_skew_heap_LetterPtr(&post_offices[id_post_office].letters);
        pop_skew_heap_LetterPtr(&post_offices[id_post_office].letters);
        if (letter->id == id_letter) {
            // пропускаем это письмо
            break;
        }
        push_back_vector_LetterPtr(&buffer, letter);
    }

    for (int i = 0; i < buffer.size; ++i) {
        insert_skew_heap_LetterPtr(&post_offices[id_post_office].letters, get_at_vector_LetterPtr(&buffer, i));
    }
}


error_code_t create_input_output_files(FILE **input, FILE **output, int argc, char *argv[]) {
    *input = fopen(argv[1], "r");
    if (!(*input)) {
        printf("-- ошибка: ошибка при открытии файла %s", argv[1]);
        print_usage();
        return ERROR_FILE_OPEN;
    }

    char output_name[100];
    if (argc == 3) {
        strcpy(output_name, argv[2]);
    }
    else {
        srand(time(NULL));

        const int count_symbols = 1 + (rand() % 10); // колво символов в выходном файле
        
        int i = 0;
        for ( ; i < count_symbols; ++i) {
            output_name[i] = 'a' + (rand() % 26);
        }
        output_name[i] = '\0';
        strcat(output_name, ".txt");
    }

    *output = fopen(output_name, "w");
    if (!(*output)) {
        printf("-- ошибка: ошибка при открытии файла %s", output_name);
        print_usage();
        return ERROR_FILE_OPEN;
    }

    return SUCCESS;
}

error_code_t read_data_from_input_file(PostOffice *post_offices, bool *work_post_offices, \
                                        FILE *input_file, pthread_mutex_t *mutex_data) {
    unsigned int sender = 0, receiver = 0;

    pthread_mutex_lock(mutex_data);
    while (!feof(input_file)) {
        fscanf(input_file, "%d-%d", &sender, &receiver);

        error_code_t error = validate_link_sender_receiver(sender, receiver, post_offices, work_post_offices);
        if (error == ERROR_POST_OFFICE_NOT_EXIST || error == ERROR_FORMAT_DATA) {
            pthread_mutex_unlock(mutex_data);
            return error;
        }

        // создаю двунаправленное соединение
        post_offices[sender].links[receiver] = true;
        post_offices[receiver].links[sender] = true;
    }
    pthread_mutex_unlock(mutex_data);
    return SUCCESS;
}


void print_usage() {
    printf("./main.out input_file [log_file]\n");
}

void print_info() {
    printf("Доступные команды: \n");
    printf("\t1. Добавить почтовое отделение\n");
    printf("\t2. Удалить почтовое отделение\n");
    printf("\t3. Добавить письмо\n");
    printf("\t4. Попытка взять письмо из пункта назначения\n");
    printf("\t5. Вывести все письма\n");
    printf("\t6. Считать данные (связи между отделениями) из файла\n");
    printf("\t7. Изменить состояние письма на 'недоставлено'\n");
    printf("\t8. Выход из приложения\n");
}

void print_letter(FILE *output_file, Letter *letter) {
    fprintf(output_file, "== Письмо id %u\n", letter->id);
    fprintf(output_file, "\tТип письма: ");
    switch (letter->type) {
        case (SIMPLE) : {
            fprintf(output_file, "Простое\n");
            break;
        }
        case (URGENT) : {
            fprintf(output_file, "Срочное\n");
            break;
        }
    }

    fprintf(output_file, "\tСостояние письма: ");
    switch (letter->state) {
        case (DELIVERED) : {
            fprintf(output_file, "Доставлено\n");
            break;
        }
        case (NOT_DELIVERED) : {
            fprintf(output_file, "Недоставлено\n");
            break;
        }
        case (IN_THE_PROCCESS_OF_SENDING) : {
            fprintf(output_file, "В процессе доставки\n");
            break;
        }
    }

    fprintf(output_file, "\tПриоритет письма: %d\n", letter->priority);
    fprintf(output_file, "\tid почтового отделения отправителя: %u\n", letter->id_postoffice_sender);
    fprintf(output_file, "\tid почтового отделения получателя: %u\n", letter->id_postoffice_receiver);
    fprintf(output_file, "\tТехнические данные: %s\n", letter->tech_data);
}

void print_all_letters(Vector_LetterPtr *vector_all_letters, FILE *output_file, pthread_mutex_t *mutex_data) {
    pthread_mutex_lock(mutex_data);
    for (int i = 0; i < vector_all_letters->size; ++i) {
        if (i == 0) fprintf(output_file, "[service sending letter]: Все письма: \n");
        print_letter(output_file, get_at_vector_LetterPtr(vector_all_letters, i));
        fflush(output_file);
        print_letter(stdout, get_at_vector_LetterPtr(vector_all_letters, i));
    }
    pthread_mutex_unlock(mutex_data);
}


void log_in_file_send_letter(FILE *output_file, unsigned int letter_id, unsigned int id_from, unsigned int id_to) {
    fprintf(output_file, "[service sending letter]: письмо %u было отправлено из почтового отделения %u в почтовое отделение %u\n", \
                                                                            letter_id, id_from, id_to);
    fflush(output_file);
}



void bfs(PostOffice *post_offices, bool *work_post_offices, unsigned int start_position, int *distance) {
    LinkedList_size_t queue = create_linked_list_stack_queue_impl();

    enqueue_size_t(&queue, start_position);

    distance[start_position] = 0;
    
    while (queue.size != 0) {
        unsigned int v = peek_queue_size_t(&queue); // индекс почтового отделения, в которое сейчас переходим
        dequeue_size_t(&queue);

        bool *links = post_offices[v].links;
        for (int i = 0; i < MAX_SIZE_POST_OFFICES; ++i) {
            if (validate_work_post_office(post_offices, work_post_offices, links, distance, i) == false) {
                // если у нас нет с ним связи или
                // его не существует, переполнено или мы его уже посещали
                continue;
            }
            distance[i] = distance[v] + 1;
            enqueue_size_t(&queue, i);
        }
    }
}


void move_max_priority_letter_from_postoffice(PostOffice *post_offices, bool *work_post_offices, \
                                        unsigned int id_post_office, FILE *output_file, pthread_mutex_t *mutex_data) {
                            
    // сразу блокирую мьютекст на всю логику выполнения перемещения писем
    pthread_mutex_lock(mutex_data);



    Vector_LetterPtr vector_letters = create_vector_impl();

    // письмо с максимальным приоритетом
    Letter *max_letter = NULL;
    while (post_offices[id_post_office].letters.size != 0 ) {
        Letter *letter = peek_skew_heap_LetterPtr(&post_offices[id_post_office].letters);
        pop_skew_heap_LetterPtr(&post_offices[id_post_office].letters);
        push_back_vector_LetterPtr(&vector_letters, letter);
        if (letter->state == IN_THE_PROCCESS_OF_SENDING) {
            max_letter = letter;
            break;
        }
        
    }

    for (int i = vector_letters.size - 1; i >= 0; ++i) {
        Letter *letter = get_at_vector_LetterPtr(&vector_letters, i);

        // возвращаем обратно
        insert_skew_heap_LetterPtr(&post_offices[id_post_office].letters, letter);
    }

    if (max_letter == NULL) {
        // все письма в этом отделении уже доставлены
        fprintf(output_file, "[service sending letter]: в отделении %u нет доступных писем\n", id_post_office);
        fflush(output_file);
        pthread_mutex_unlock(mutex_data);
        return;
    }

    move_letter(post_offices, work_post_offices, id_post_office, max_letter, output_file);

    pthread_mutex_unlock(mutex_data);

    return;
} 

bool move_letter(PostOffice *post_offices, bool *work_post_offices, unsigned int id_post_office, Letter *letter, FILE *output_file) {
    // функция, которая вызывает эту функцию, должна сама вызать mutex lock!!! 


    // с какими отделениями есть связь
    bool *links = post_offices[id_post_office].links;

    unsigned int id_receiver_post_office = letter->id_postoffice_receiver;

    unsigned int id_next_post_office = MAX_SIZE_POST_OFFICES + 1;
    int min_distance = INT_MAX;

    for (int next_id = 0; next_id < MAX_SIZE_POST_OFFICES; ++next_id) {
        // если его не существует, нет связи или переполнено
        if (post_offices[next_id].letters.size >= post_offices[next_id].capacity_post_office || work_post_offices[next_id] == false || links[next_id] == false) continue;
        // массив, где будут хранится расстояния от почтового отделения с индексом next_id
        // до итового почтового отделения
        int distance[MAX_SIZE_POST_OFFICES];
        for (int i = 0; i < MAX_SIZE_POST_OFFICES; ++i) {
            distance[i] = INT_MAX - 1;
        }

        bfs(post_offices, work_post_offices, next_id, distance);
        
        // if (min_distance == -1 && distance[id_receiver_post_office] != -1) {
        //     min_distance = distance[id_receiver_post_office];
        //     id_next_post_office = next_id;
        // }
        // else if (distance[id_receiver_post_office] < min_distance && distance[id_receiver_post_office] != -1) {
        //     min_distance = distance[id_receiver_post_office];
        //     id_next_post_office = next_id;
        // }
        // else if (distance[id_receiver_post_office] == -1) {
        //     min_distance = distance[id_receiver_post_office];
        //     id_next_post_office = next_id;
        // }
        
        if (distance[id_receiver_post_office] < min_distance) {
            min_distance = distance[id_receiver_post_office];
            id_next_post_office = next_id;
        }



    }


    // если не нашли куда можно отправить письмо
    // нет дорог между отделениями, нет свободных отделений
    if (id_next_post_office == MAX_SIZE_POST_OFFICES + 1) {
        fprintf(output_file, "[service sending letter]: письмо %u из отделения %u ", letter->id, id_post_office);
        fprintf(output_file, "не может быть перенаправлено в другое, ввиду недоступности/загруженности\n");
        fflush(output_file);
        return false;
    }

    if (id_next_post_office == id_receiver_post_office) {
        // если письмо доставлено
        letter->state = DELIVERED;
    }


    pop_skew_heap_LetterPtr(&(post_offices[id_post_office].letters));
    insert_skew_heap_LetterPtr(&(post_offices[id_next_post_office].letters), letter);

    letter->id_cur_postoffice = id_next_post_office;

    log_in_file_send_letter(output_file, letter->id, id_post_office, id_next_post_office);

    return true;
}