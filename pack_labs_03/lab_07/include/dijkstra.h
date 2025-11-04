#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "config.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// для обработки унарного минуса
typedef enum {
    EXPECTED_OPERAND, // ожидаем операнд, открывающую скобку, унарный минус 
    EXPECTED_OPERATOR, // ожидаем операцию или закрывающую скобку
} State;

typedef enum {
    UNKNOWN,
    OPERAND,
    OPERATOR,
    OPEN_BRACKET,
    CLOSE_BRACKET,
} Token;

typedef enum {
    LEFT_ASSOCIATIVITY,
    RIGHT_ASSOCIATIVITY,
} Associativity;

void parse_expression(char *str_expression, LinkedList_char *output_queue);



#endif