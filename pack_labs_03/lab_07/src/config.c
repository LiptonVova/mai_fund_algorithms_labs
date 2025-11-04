#include "../include/config.h"

void delete_func(Element value) {

}

Element copy_func(Element other) {
    Element element;
    element.token = other.token;
    element.value = other.value;
    return element;
}

int comp(Element value_1, Element value_2) {
    if (value_1.token != value_2.token) {
        return 0;
    }
    if (value_1.token == NUMBER) {
        return value_1.value.int_value == value_2.value.int_value;

    }
    else {
        return value_1.value.char_value == value_2.value.char_value;
    }
}

Element default_constructor() {
    Element element;
    element.token = UNKNOWN;
    element.value.int_value = 0;
    return element;
}

LinkedList_Element create_list_stack_queue() {
    LinkedList_Element linkedList = create_list_Element(delete_func, copy_func, comp, default_constructor);
    return linkedList;
}