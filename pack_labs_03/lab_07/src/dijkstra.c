#include "../include/dijkstra.h"


Token define_token(const char c) {
    int n = 6;
    char operators[] = "+-*/^~";
    for (int i = 0; i < n; ++i) {
        if (c == operators[i]) {
            return OPERATOR;
        }
    }

    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        return OPERAND;
    }
    if (c == ')') {
        return OPEN_BRACKET;
    }
    if (c == '(') {
        return CLOSE_BRACKET;
    }
    return UNKNOWN;
}


int define_priority(const char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    else if (c == '*' || c == '/') {
        return 2;
    }
    else if (c == '^') {
        return 3;
    }
    else if (c == '~') {
        return 4;
    }
    return -1;
}

Associativity define_associativity(const char operator) {
    if (operator == '^' || operator == '~') {
        return RIGHT_ASSOCIATIVITY;
    }
    return LEFT_ASSOCIATIVITY;
}

bool define_pop(const char operator_1, const char operator_2) {
    Associativity associativity = define_associativity(operator_1);
    if (associativity == LEFT_ASSOCIATIVITY) {
        return define_priority(operator_1) >= define_priority(operator_2);
    }
    else {
        return define_priority(operator_1) > define_priority(operator_2);
    }
}


void parse_expression(char *str_expression, LinkedList_char *output_queue) {
    State state = EXPECTED_OPERAND;

    int index = 0;
    char c = str_expression[index++];

    LinkedList_char stack = create_list_stack_queue();

    while (c != '\0') {
        Token token = define_token(c);
        switch (state) {
            case (EXPECTED_OPERAND):
                // ожидаем либо операнд, либо открывающую скобку, либо унарный минус
                if (token == OPERAND) {
                    // если операнд, то однозначно добавляем его в выходную очередь
                    enqueue_char(output_queue, c);
                    
                    // если это операнд, то меняем состояние, так как теперь мы ожидаем операцию
                    state = EXPECTED_OPERATOR;
                }
                else if (token == OPEN_BRACKET) {
                    // если это открывающая скобка, то добавляем ее в стэк
                    push_stack_char(&stack, c);
                }
                else if (c == '-') {
                    // это унарный минус
                    // добавляем его в стэк
                    // обозначаем унарный минус в виде ~
                    push_stack_char(&stack, '~'); 
                }

                else {
                    printf("-- Ошибка в выражении\n");
                    return;
                }

                break;

            case (EXPECTED_OPERATOR):
                // ожидаем бинарный оператор или закрывающая скобку
                if (token == OPERATOR) {
                    if (stack.size != 0) { 
                        char top_stack;
                        do {
                            top_stack = peek_stack_char(&stack); // получаем оператор с вершины стека

                            pop_stack_char(&stack); // удаляем операцию со стека операций
                            enqueue_char(output_queue, top_stack); // добавляем операцию в выходную очередь

                        } while (stack.size > 0 && define_pop(c, top_stack));
                    }
                    
                    push_stack_char(&stack, c); // добавляем операцию в стек

                    state = EXPECTED_OPERAND;
                }

                else if (token == CLOSE_BRACKET) {
                    if (stack.size != 0) {
                        char top_stack = peek_stack_char(&stack); // вершина стэка

                        while (top_stack != '(') {
                            pop_stack_char(&stack); // удаляем эту операцию
                            enqueue_char(output_queue, top_stack); // перекладываем в выходную очередь

                            top_stack = peek_stack_char(&stack); // вершина стэка

                            if (stack.size == 0 && top_stack != '(') { // если стэк закончился, а открывающей скобки нет
                                printf("-- Ошибка в выражении\n");
                                return;
                            }
                        }
                        pop_stack_char(&stack); // удаляем открывающую скобку и никуда ее не добавляем
                    }   

                    else {
                        printf("-- Ошибка в выражении\n");
                        return;
                    } 
                }

                else {
                    printf("-- Ошибка в выражении\n");
                    return;
                }

                break;
            
            
            default:
                printf("-- Ошибка в выражении\n");
                return;
        }

        c = str_expression[index++];
    }

    // если что то осталось в стеке, перекладываем
    while (stack.size != 0) {
        char top_stack = peek_stack_char(&stack);
        if (top_stack == '(') {
            printf("-- Ошибка в выражении\n");
            return;
        }
        pop_stack_char(&stack);

        enqueue_char(output_queue, top_stack);
    }
}