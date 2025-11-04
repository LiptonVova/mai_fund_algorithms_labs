#include "../include/config.h"

void delete_func(char value) {

}

char copy_func(char other) {
    return other;
}

int comp(char value_1, char value_2) {
    return value_1 == value_2;
}

char default_constructor() {
    return '\0';
}


LinkedList_char create_list_stack_queue() {
    LinkedList_char stack = create_list_char(delete_func, copy_func, comp, default_constructor);
    return stack;
}