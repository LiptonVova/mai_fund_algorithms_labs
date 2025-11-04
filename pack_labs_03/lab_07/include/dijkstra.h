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
    LEFT_ASSOCIATIVITY,
    RIGHT_ASSOCIATIVITY,
} Associativity;

error_code_t parse_expression(LinkedList_Element *input_queue, LinkedList_Element *output_queue);



#endif