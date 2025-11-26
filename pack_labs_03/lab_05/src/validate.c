#include "../include/validate.h"


error_code_t validate_count_arguments(int argc) {
    if (argc != 2 && argc != 3) {
        printf("-- ошибка: неправильный запуск программы\n");    
        print_usage();
        return ERROR_COUNT_ARGUMENTS;
    }
    return SUCCESS;
}


error_code_t validate_link_sender_receiver(unsigned int sender, unsigned int receiver, PostOffice *post_offices, bool* work_post_offices) {
    if (sender >= MAX_SIZE_POST_OFFICES || receiver >= MAX_SIZE_POST_OFFICES) {
        printf("-- ошибка: id почтового отделения не может быть больше %ud", MAX_SIZE_POST_OFFICES);
        return ERROR_FORMAT_DATA;
    }
    if (sender == receiver) {
        printf("-- ошибка: связь между тем же отделением\n");
        return ERROR_FORMAT_DATA;
    }    
    if (work_post_offices[sender] == false) {
        printf("-- ошибка: такого почтового отделения не существует: %ud", sender);
        return ERROR_POST_OFFICE_NOT_EXIST;
    }
    if (work_post_offices[receiver] == false) {
        printf("-- ошибка: такого почтового отделения не существует: %ud", receiver);
        return ERROR_POST_OFFICE_NOT_EXIST;
    }
    
    if (post_offices[sender].links[receiver] == true) {
        printf("-- варнинг: связь почтового отделения %u с почтовым отделением %u уже существует\n", sender, receiver);
        return WARNING_LINK_POST_OFFICES;
    }
    if (post_offices[receiver].links[sender] == true) {
        printf("-- варнинг: связь почтового отделения %u с почтовым отделением %u уже существует\n", receiver, sender);
        return WARNING_LINK_POST_OFFICES;
    }

    return SUCCESS;
}

error_code_t validate_add_id_postoffice(const bool *work_post_offices, const unsigned int id) {
    if (id >= MAX_SIZE_POST_OFFICES) {
        printf("-- варнинг: id почтового отделения слишком большой\n");
        return WARNING_ID_POST_OFFICE;
    }
    if (work_post_offices[id] == true) {
        printf("-- варнинг: такое почтовое отделения уже существует\n");
        return WARNING_ID_POST_OFFICE;
    }
    return SUCCESS;
}

error_code_t validate_number_id_link_postoffice(const bool *work_post_offices, const unsigned int id_link_post_office, const unsigned int id) {
    if (id_link_post_office >= MAX_SIZE_POST_OFFICES) {
        printf("-- ошибка: id почтового отделения слишком большой\n");
        return ERROR_POST_OFFICE_NOT_EXIST;
    }
    if (work_post_offices[id_link_post_office] == false) {
        printf("-- ошибка: такого почтового отделения не существует\n");
        return ERROR_POST_OFFICE_NOT_EXIST;
    }
    if (id_link_post_office == id) {
        printf("-- ошибка: почтовое отделение не может быть связано с ним же\n");
        return ERROR_POST_OFFICE_NOT_EXIST;
    }

    return SUCCESS;
}

error_code_t validate_delete_id_postoffice(const bool *work_post_offices, const unsigned int id) {
    if (id >= MAX_SIZE_POST_OFFICES) {
        printf("-- варнинг: id почтового отделения слишком большой\n");
        return WARNING_ID_POST_OFFICE;
    }
    if (work_post_offices[id] == false) {
        printf("-- варнинг: такого почтового отделения не существует\n");
        return WARNING_ID_POST_OFFICE;
    }
    return SUCCESS;
}

error_code_t validate_id_postoffice_for_add_letter(PostOffice *post_offices, bool *work_post_offices, unsigned int id_sender) {
    error_code_t error = validate_delete_id_postoffice(work_post_offices, id_sender);
    if (error != SUCCESS) return error;

    if (post_offices[id_sender].letters.size == post_offices[id_sender].capacity_post_office) {
        printf("-- варнинг: это почтовое отделение переполнено\n");
        return WARNING_ID_POST_OFFICE_FOR_ADD_LETTER;
    }

    return SUCCESS;
}

error_code_t validate_type_letter(TypeLetter type_letter) {
    if (type_letter != SIMPLE && type_letter != URGENT) return WARNING_TYPE_LETTER;
    return SUCCESS;
}

bool validate_work_post_office(PostOffice *post_offices, bool *work_post_offices, bool *links, int *distance, unsigned int next_id_post_office) {
    if (links[next_id_post_office] == false) {
        // нет связи с этим отделением
        return false;
    }
    if (work_post_offices[next_id_post_office] == false) {
        // не существует
        return false;
    }
    if (distance[next_id_post_office] != -1) {
        // уже посещали ранее
        return false;
    }
    SkewHeap_LetterPtr letters = post_offices[next_id_post_office].letters;
    if (post_offices[next_id_post_office].capacity_post_office <= letters.size) {
        // переполнено
        return false;
    }
    return true;
}

error_code_t validate_id_letter_for_make_not_delivered(unsigned int id_letter, Vector_LetterPtr *vector_all_letters) {
    if (id_letter >= vector_all_letters->size) {
        printf("-- варнинг: несуществующее письмо\n");
        return WARNING_NOT_EXIST_LETTER;
    }
    return SUCCESS;    
}