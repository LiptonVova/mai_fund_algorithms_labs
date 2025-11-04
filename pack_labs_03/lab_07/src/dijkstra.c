#include "../include/dijkstra.h"



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
    return -1; // в стеке открытая скобка, ее выталкивать не надо
}

Associativity define_associativity(const char operator) {
    if (operator == '^' || operator == '~') {
        return RIGHT_ASSOCIATIVITY;
    }
    return LEFT_ASSOCIATIVITY;
}

bool define_pop(const Element operator_1, const Element operator_2) {
    // operator_1 - новый элемент
    // operator_2 - элемент с вершины стека
    // выталкиваем, если operator_2 >= (>) operator_1
    // то есть выталкиваем все операторы, у которых приоритет больше или равен (больше) чем у нового оператор  
    Associativity associativity = define_associativity(operator_1.value.char_value);
    if (associativity == LEFT_ASSOCIATIVITY) {
        return define_priority(operator_2.value.char_value) >= define_priority(operator_1.value.char_value);
    }
    else {
        return define_priority(operator_2.value.char_value) > define_priority(operator_1.value.char_value);
    }
}

error_code_t logic_expected_operand(Element *element, State *state, LinkedList_Element *stack, LinkedList_Element *output_queue) {
    // функция, которая отвечает за логику, при state == EXPECTED_OPERAND

    Token token = element->token;

    // ожидаем либо операнд, либо открывающую скобку, либо унарный минус
    if (token == VARIABLE || token == NUMBER) {
        // если операнд, то однозначно добавляем его в выходную очередь
        enqueue_Element(output_queue, *element);
        
        // если это операнд, то меняем состояние, так как теперь мы ожидаем операцию
        *state = EXPECTED_OPERATOR;
    }
    else if (token == OPEN_BRACKET) {
        // если это открывающая скобка, то добавляем ее в стэк
        push_stack_Element(stack, *element);
    }
    else if (element->token == OPERATOR && element->value.char_value == '-') {
        // это унарный минус
        // добавляем его в стэк
        // обозначаем унарный минус в виде ~
        Element new_element;
        new_element.token = OPERATOR;
        new_element.value.char_value = '~'; // меняем унарный минус на ~
        push_stack_Element(stack, new_element); 
    }

    else {
        printf("-- Ошибка в выражении\n");
        return ERROR_WITH_EXPRESSION;
    }

    return SUCCESS;

}

error_code_t logic_expected_operator(Element *element, State *state, LinkedList_Element *stack, LinkedList_Element *output_queue) {
    // функция, которая отвечает за логику при state == EXPECTED_OPERATOR

    Token token = element->token;
    // ожидаем бинарный оператор или закрывающая скобку
    if (token == OPERATOR) {
        while (stack->size > 0 && define_pop(*element, peek_stack_Element(stack)))  {
            Element top_stack = peek_stack_Element(stack); // получаем оператор с вершины стека

            pop_stack_Element(stack); // удаляем операцию со стека операций
            enqueue_Element(output_queue, top_stack); // добавляем операцию в выходную очередь
        } 
        
        push_stack_Element(stack, *element); // добавляем операцию в стек

        *state = EXPECTED_OPERAND;
    }

    else if (token == CLOSE_BRACKET) {
        if (stack->size != 0) {
            Element top_stack = peek_stack_Element(stack); // вершина стэка

            while (top_stack.value.char_value != '(') {
                pop_stack_Element(stack); // удаляем эту операцию
                enqueue_Element(output_queue, top_stack); // перекладываем в выходную очередь

                top_stack = peek_stack_Element(stack); // вершина стэка

                if (stack->size == 0 && top_stack.value.char_value != '(') { // если стэк закончился, а открывающей скобки нет
                    printf("-- Ошибка в выражении\n");
                    return ERROR_WITH_EXPRESSION;
                }
            }
            pop_stack_Element(stack); // удаляем открывающую скобку и никуда ее не добавляем
        }   

        else {
            printf("-- Ошибка в выражении\n");
            return ERROR_WITH_EXPRESSION;
        } 
    }

    else {
        printf("-- Ошибка в выражении\n");
        return ERROR_WITH_EXPRESSION;
    }

    return SUCCESS;
}

error_code_t logic_shift_stack_to_queue(LinkedList_Element *stack, LinkedList_Element *output_queue) {
    // финальная логика, когда нужно переложить из стека в очередь

    Element top_stack = peek_stack_Element(stack);
    if (top_stack.token == OPEN_BRACKET) {
        printf("-- Ошибка в выражении\n");
        return ERROR_WITH_EXPRESSION;
    }
    pop_stack_Element(stack);

    enqueue_Element(output_queue, top_stack);

    return SUCCESS;
}

error_code_t parse_expression(LinkedList_Element *input_queue, LinkedList_Element *output_queue) {
    // основная логика алгоритма Дейкстры

    State state = EXPECTED_OPERAND;

    LinkedList_Element stack = create_list_stack_queue(); // создаем стэк для хранения операторов

    while (input_queue->size != 0) {
        Element element = peek_queue_Element(input_queue); // берем очередной элемент во входной очереди
        dequeue_Element(input_queue); // удаляем из входной очереди

        switch (state) {
            case (EXPECTED_OPERAND): {
                error_code_t error = logic_expected_operand(&element, &state, &stack, output_queue);
                if (error != SUCCESS) return error;
                break;
            }

            case (EXPECTED_OPERATOR): {
                error_code_t error = logic_expected_operator(&element, &state, &stack, output_queue);
                if (error != SUCCESS) return error;
                break;     
            }
            
            default:
                printf("-- Ошибка в выражении\n");
                return ERROR_WITH_EXPRESSION; 
        }
    }

    // если что то осталось в стеке, перекладываем
    while (stack.size != 0) {
        error_code_t error = logic_shift_stack_to_queue(&stack, output_queue);
        if (error != SUCCESS) return error;
    }

    return SUCCESS;
}