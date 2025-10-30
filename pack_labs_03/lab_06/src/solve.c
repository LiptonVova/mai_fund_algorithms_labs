#include "../include/solve.h"


DEFINE_LIST_STACK(char)


void delete_func(char value) {

}

char copy_func(char value) {
    return value;
}

int comp(char value_1, char value_2) {
    return value_1 == value_2;
}

int check_bracket(LinkedList *stack, const char c) {
    switch (c) {
        case ')':
            return peek_stack(stack) == '(';
            break;
        case ']':
            return peek_stack(stack) == '[';
            break;
        case '}':
            return peek_stack(stack) == '{';
            break;
        case '>':
            return peek_stack(stack) == '<';
            break;
    }
    return 0;    
}

int check_brackets(const char *str) {
    const int n = strlen(str); 

    LinkedList stack = create_list(delete_func, copy_func, comp);

    for (size_t i = 0; i < n; ++i) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == '<') {
            push_stack(&stack, str[i]);
        }
        else if (str[i] == ')' || str[i] == ']' || str[i] == '}' || str[i] == '>') {
            int check = check_bracket(&stack, str[i]);
            if (!check) {
                delete_list(&stack);
                return 0;
            }
            pop_stack(&stack);
        }
    }

    delete_list(&stack);
    return 1;
}