#include "../include/handles.h"


error_code_t handle_add_postoffice(PostOffice *post_offices, bool *work_post_offices, FILE *output_file) {
    printf("============================Добавление почтового отделения============================\n");
    error_code_t error = SUCCESS;
    unsigned int id_post_office = 0;
    do {
        printf("Введите id почтового отделения: ");
        scanf("%u", &id_post_office);
        error = validate_add_id_postoffice(work_post_offices, id_post_office);
        
        // цикл будет повторяться, если error == WARNING_ID_POST_OFFICE (означает, что невалидный id)
    } while (error != SUCCESS);

    unsigned int capacity_post_office = 0;
    printf("Введите вместимость почтового отделения (сколько одновременно писем может хранить почтовое отделение): ");
    scanf("%u", &capacity_post_office);

    int count_links = 0; 
    printf("Введите количество почтовых отделений, у которых есть связь с текущим отделением: ");
    scanf("%d", &count_links);

    
    PostOffice new_post_office;

    for (int i = 0; i < MAX_SIZE_POST_OFFICES; ++i) {
        new_post_office.links[i] = false;
    }

    for (int i = 0; i < count_links; ++i) {
        if (i == 0) printf("Введите id почтового отделения, у которого есть связь с новым отделением: ");
        else printf("--||--: ");

        unsigned int id_link_post_office = 0;
        scanf("%u", &id_link_post_office);

        error = validate_number_id_link_postoffice(work_post_offices, id_link_post_office, id_post_office);
        if (error != SUCCESS) return error; 

        new_post_office.links[id_link_post_office] = true;
        post_offices[id_link_post_office].links[id_post_office] = true;
    }

    new_post_office.id = id_post_office;
    new_post_office.capacity_post_office = capacity_post_office;
    new_post_office.letters = create_priority_queue_impl();

    post_offices[id_post_office] = new_post_office;
    work_post_offices[id_post_office] = true;

    printf("-- инфо: успешно добавлено!\n");

    return SUCCESS;
}

error_code_t handle_delete_postoffice(PostOffice *post_offices, bool *work_post_offices, FILE *output_file) {
    printf("============================Удаление почтового отделения============================\n");
    error_code_t error = SUCCESS;
    unsigned int id_post_office = 0;
    do {
        printf("Введите id почтового отделения: ");
        scanf("%u", &id_post_office);
        error = validate_delete_id_postoffice(work_post_offices, id_post_office);
        
        // цикл будет повторяться, если error == WARNING_ID_POST_OFFICE (означает, что невалидный id)
    } while (error != SUCCESS);


    // нужно у всех почтовых отделений удалить связь с удаляемым
    for (int i = 0; i < MAX_SIZE_POST_OFFICES; ++i) {
        if (work_post_offices[i]) {
            post_offices[i].links[id_post_office] = false; // удаляем связь
        }
    }

    return SUCCESS;
}

error_code_t handle_add_letter(PostOffice *post_offices, bool *work_post_offices, FILE *output_file, Vector_LetterPtr* vector_all_letters) {
    printf("============================Добавление письма============================\n");
    error_code_t error = SUCCESS;

    static unsigned int static_id_letter = 0;

    Letter* letter = (Letter*)malloc(sizeof(Letter));
    if (!letter) {
        printf("-- ошибка: ошибка при выделении памяти\n");
        printf("-- инфо: письмо не было добавлено\n");
        return ERROR_MALLOC;
    }

    printf("Введите число (тип) письма (простое - 1, срочное - 2): \n");
    int type_letter = 0;
    do {
        scanf("%d", &type_letter);
        error = validate_type_letter(type_letter);
        if (error != SUCCESS) printf("-- варнинг: невалидный тип письма, попробуйте еще раз\n");
    } while (error != SUCCESS);

    int priority = 0;
    printf("Введите приоритет письма (целое число): ");
    scanf("%d", &priority);

    unsigned int id_sender = 0;
    do {
        printf("Введите id почтового отделения отправителя: ");
        scanf("%u", &id_sender);
        error = validate_delete_id_postoffice(work_post_offices, id_sender);
        if (error != SUCCESS) printf("-- варнинг: невалидный id отправителя, попробуйте еще раз\n");
    }
    while (error != SUCCESS);
    unsigned int id_receiver = 0;
    do {
        printf("Введите id почтового отделения получателя: ");
        scanf("%u", &id_receiver);
        error = validate_delete_id_postoffice(work_post_offices, id_receiver);
        if (error != SUCCESS) printf("-- варнинг: невалидный id получателя, попробуйте еще раз\n");
    }
    while (error != SUCCESS);

    printf("Введите технические данные письма: ");
    scanf("\n");
    fgets(letter->tech_data, 100, stdin);
    letter->tech_data[99] = '\0';

    letter->id = static_id_letter++;
    letter->type = type_letter;
    letter->state = (id_sender == id_receiver ? DELIVERED : IN_THE_PROCCESS_OF_SENDING);
    letter->priority = priority;
    letter->id_postoffice_sender = id_sender;
    letter->id_postoffice_receiver = id_receiver;
    letter->taked = false;

    push_heap_LetterPtr(&post_offices[id_sender].letters, letter);
    push_back_vector_LetterPtr(vector_all_letters, letter);

    return SUCCESS;
}

void handle_get_letter(bool *work_post_offices, Vector_LetterPtr *vector_all_letters, FILE *output_file) {
    printf("Введите id письма, которое нужно найти: ");
    int id_letter = 0;
    scanf("%d", &id_letter);

    if (id_letter < 0 || id_letter >= vector_all_letters->size) {
        printf("-- варнинг: вы ввели id несуществующего письма\n");
        return;
    }

    Letter *cur_letter = get_at_vector_LetterPtr(vector_all_letters, id_letter);
    const unsigned int id_receiver = cur_letter->id_postoffice_receiver;

    if (work_post_offices[id_receiver] == false) {
        printf("К сожалению почтовое отделения получателя недоступно...\n");
        return;
    }

    if (cur_letter->state == NOT_DELIVERED) {
        printf("Письмо не может быть доставлено ввиду загруженности/недоступности\n");
        return;
    }
    if (cur_letter->state == IN_THE_PROCCESS_OF_SENDING) {
        printf("Письмо в процессе доставки, ожидайте\n");
        return;
    }

    if (cur_letter->taked == true) {
        printf("Письмо было успешно доставлено и его уже забирали из отделения\n");
        return;
    }

    printf("Вы успешно забрали письмо!\n");
    cur_letter->taked = true;
}
