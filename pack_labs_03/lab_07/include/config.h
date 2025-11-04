#ifndef CONFIG_H
#define CONFIG_H

#include "linkedList_stack_queue.h"

typedef enum {
    UNKNOWN,
    // OPERAND,
    NUMBER,
    VARIABLE,
    OPERATOR,
    OPEN_BRACKET,
    CLOSE_BRACKET,
} Token;

typedef union {
    int int_value;
    char char_value;
} Value ;

typedef struct {
    Token token;
    Value value;
} Element;


typedef enum {
    SUCCESS,
    ERROR_WITH_EXPRESSION,
    ERROR_PARSE_TOKENS,
    ERROR_CALCULATE,
} error_code_t;

DEFINE_LIST_STACK(Element)

LinkedList_Element create_list_stack_queue();


#endif