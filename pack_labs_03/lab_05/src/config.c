#include "../include/config.h"

void delete_func(Letter* value) {
    free(value);
}

int comp(Letter* value_1, Letter* value_2) {
    if (value_1->id < value_2->id) return -1;
    else if (value_1->id > value_2->id) return 1;
    return 0;
}

Letter* copy_func(Letter* other) {
    return other; // важно именно оператор перемещения, потому что я работаю с указателями
}

void swap(Letter **letter_1, Letter **letter_2) {
    Letter* temp = *letter_1;
    *letter_1 = copy_func(*letter_2);
    *letter_2 = copy_func(temp);
}

Letter* default_constructor() {
    Letter* letter = (Letter*)malloc(sizeof(Letter));
    if (!letter) return NULL;
    letter->id = 0;
    letter->type = SIMPLE;
    letter->state = NOT_DELIVERED;
    letter->priority = 0;
    letter->id_postoffice_sender = 0;
    letter->id_postoffice_receiver = 0;
    letter->id_cur_postoffice = 0;
    strcpy(letter->tech_data, "");
    return letter;
    
}

Vector_LetterPtr create_vector_impl() {
    const size_t initial_capacity = 10;
    return create_vector_LetterPtr(initial_capacity, copy_func, delete_func, comp, default_constructor);
}

Heap_LetterPtr create_priority_queue_impl() {
    const size_t initial_capacity = 10;
    return create_heap_LetterPtr(initial_capacity, delete_func,\
                    copy_func, comp, default_constructor, swap);
}

void delete_func_size_t(size_t value) {
    return;
}

size_t copy_func_size_t(size_t value) {
    return value;
}

int comp_size_t(size_t value_1, size_t value_2) {
    if (value_1 < value_2) return -1;
    if (value_1 > value_2) return 1;
    return 0;
}

size_t default_constructor_size_t() {
    return 0;
}

LinkedList_size_t create_linked_list_stack_queue_impl() {
    return create_list_size_t(delete_func_size_t, copy_func_size_t, comp_size_t, default_constructor_size_t);
}
