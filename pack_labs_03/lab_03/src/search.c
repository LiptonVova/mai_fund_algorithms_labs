#include "../include/search.h"


Node_Liver* search_id(LinkedList_Liver livers, size_t id, size_t* index) {
    Node_Liver *cur_node = livers.head;
    size_t cur_index = 0; // житель по счету
    while (cur_node != NULL && cur_node->data.id != id) {
        cur_node = cur_node->next;
        cur_index++;
    }
    *index = cur_index; 
    return cur_node;
}


void handle_search_id(LinkedList_Liver livers) {
    printf("Найдем жителя по id!\n");
    printf("Введите желаемый id: ");
    size_t id = 0;
    scanf("%ld", &id);

    size_t index = 0;
    Node_Liver *cur_node = search_id(livers, id, &index);

    if (cur_node == NULL) {
        printf("Жителя с данным id не найдено\n");
        return;
    }
    print_liver(stdout, cur_node->data);
}

LinkedList_Liver search_surname(LinkedList_Liver livers, char* surname) {
    LinkedList_Liver result = create_list_Liver(delete_func, copy_func, comp, default_constructor);

    Node_Liver *cur_node = livers.head;
    while (cur_node != NULL) {
        if (strcmp(cur_node->data.surname, surname) == 0) {
            push_back_list_Liver(&result, cur_node->data);
        }
        cur_node = cur_node->next;
    }
    return result;
}

void handle_search_surname(LinkedList_Liver livers) {
    printf("Найдем житетей по фамилии!\n");
    printf("Введите желаемую фамилию: ");
    char surname[100] = "\0";
    scanf("%s", surname);

    LinkedList_Liver result = search_surname(livers, surname);    

    Node_Liver *cur_node = result.head;
    int flag = 0;
    for (size_t i = 0; i < result.size; ++i) {
        print_liver(stdout, cur_node->data);
        flag = 1;
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данной фамилией в городе нет\n");
    }
}

LinkedList_Liver search_name(LinkedList_Liver livers, char* name) {
    LinkedList_Liver result = create_list_Liver(delete_func, copy_func, comp, default_constructor);

    Node_Liver *cur_node = livers.head;
    while (cur_node != NULL) {
        if (strcmp(cur_node->data.name, name) == 0) {
            push_back_list_Liver(&result, cur_node->data);
        }
        cur_node = cur_node->next;
    }
    return result;
}

void handle_search_name(LinkedList_Liver livers) {
    printf("Найдем житетей по имени!\n");
    printf("Введите желаемое имя: ");
    char name[100] = "\0";
    scanf("%s", name);

    LinkedList_Liver result = search_name(livers, name);    

    Node_Liver *cur_node = result.head;
    int flag = 0;
    for (size_t i = 0; i < result.size; ++i) {
        print_liver(stdout, cur_node->data);
        flag = 1;
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данным именем в городе нет\n");
    }
}


LinkedList_Liver search_birthday(LinkedList_Liver livers, int day, int month, int year) {
    LinkedList_Liver result = create_list_Liver(delete_func, copy_func, comp, default_constructor);

    Node_Liver *cur_node = livers.head;
    while (cur_node != NULL) {
        if (cur_node->data.day_birthday == day && cur_node->data.month_birthday == month && cur_node->data.year_birthday) {
            push_back_list_Liver(&result, cur_node->data);
        }
        cur_node = cur_node->next;
    }
    return result;
}

void handle_search_birthday(LinkedList_Liver livers) {
    printf("Найдем житетей по дате рождения!\n");
    int day = 0, month = 0, year = 0;
    printf("Введите число: ");
    scanf("%d", &day);
    printf("Введите месяц: ");
    scanf("%d", &month);
    printf("Введите год: ");
    scanf("%d", &year);


    LinkedList_Liver result = search_birthday(livers, day, month, year);    

    Node_Liver *cur_node = result.head;
    int flag = 0;
    for (size_t i = 0; i < result.size; ++i) {
        print_liver(stdout, cur_node->data);
        flag = 1;
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей с данной датой рождения в городе нет\n");
    }
}

LinkedList_Liver search_gender(LinkedList_Liver livers, char gender) {
    LinkedList_Liver result = create_list_Liver(delete_func, copy_func, comp, default_constructor);

    Node_Liver *cur_node = livers.head;
    while (cur_node != NULL) {
        if (cur_node->data.gender == gender) {
            push_back_list_Liver(&result, cur_node->data);
        }
        cur_node = cur_node->next;
    }
    return result;
}

void handle_search_gender(LinkedList_Liver livers) {
    printf("Найдем жителя по полу!\nВведите желаемый пол (Мужской-M, Женский-W): ");

    char gender;
    scanf(" %c", &gender);
    gender = toupper(gender);

    LinkedList_Liver result = search_gender(livers, gender);    

    Node_Liver *cur_node = result.head;
    int flag = 0;
    for (size_t i = 0; i < result.size; ++i) {
        print_liver(stdout, cur_node->data);
        flag = 1;
        cur_node = cur_node->next;
    }

    if (flag == 0) {
        printf("Жителей такого пола в городе нет\n");
    }
}


