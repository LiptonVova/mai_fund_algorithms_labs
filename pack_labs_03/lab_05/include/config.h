#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "vector.h"
#include "binary_heap.h"
#include "linkedList_stack_queue.h"

#define MAX_SIZE_POST_OFFICES 100

typedef enum {
    SUCCESS,
    ERROR_COUNT_ARGUMENTS,
    ERROR_FILE_OPEN,
    ERROR_MALLOC,
    ERROR_FORMAT_DATA,
    ERROR_POST_OFFICE_NOT_EXIST,
    WARNING_ID_POST_OFFICE,
    WARNING_LINK_POST_OFFICES,
    WARNING_TYPE_LETTER,
    WARNING_ID_POST_OFFICE_FOR_ADD_LETTER,
} error_code_t;

typedef enum {
    SIMPLE = 1,
    URGENT = 2,
} TypeLetter;

typedef enum {
    DELIVERED,
    NOT_DELIVERED,
    IN_THE_PROCCESS_OF_SENDING,
} StatementLetter;

typedef struct {
    unsigned int id; // id письма 
    TypeLetter type; // тип письма (обычное, срочное)
    StatementLetter state; // состояние письма
    int priority; // приоритет, чем больше, тем важнее
    unsigned int id_postoffice_sender; // id почтового отделения отправителя
    unsigned int id_postoffice_receiver; // id почтового отделения получателя
    unsigned int id_cur_postoffice; // id почтового отделения, где сейчас это письмо
    char tech_data[100]; // технические данные
    bool taked; // забирали ли из почтового отделения это письмо
} Letter;

typedef Letter* LetterPtr;
DEFINE_BINARY_MAX_HEAP(LetterPtr)

typedef struct {
    unsigned int id; // id почтового отделения
    bool links[MAX_SIZE_POST_OFFICES]; // массив, в котором хранятся связи этого отделения с другими
    unsigned int capacity_post_office; // вместимость почтового отделения
    Heap_LetterPtr letters; // очередь с приоритетом с письмами
} PostOffice;


DEFINE_VECTOR(LetterPtr)
// для bfs
DEFINE_LIST_STACK_QUEUE(size_t)



typedef enum {
    ADD_POSTOFFICE = 1,
    DELETE_POSTOFFICE = 2,
    ADD_LETTER = 3,
    GET_LETTER = 4,
    PRINT_ALL_LETTERS = 5,
    READ_DATA_FROM_INPUT_FILE = 6,
    EXIT = 7,
} Choice;

Vector_LetterPtr create_vector_impl();
Heap_LetterPtr create_priority_queue_impl();
LinkedList_size_t create_linked_list_stack_queue_impl();



#endif