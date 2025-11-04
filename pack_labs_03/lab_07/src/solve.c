#include "../include/solve.h"


void solve(int argc, char **argv) {
    if (argc != 3) {
        printf("-- Неправильный формат запуска программы\n");
        print_usage();
        return;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("-- Не удалось открыть файл %s\n", argv[1]);
        print_usage();
        return;
    }

    FILE* log_file = fopen(argv[2], "w");
    if (!log_file) {
        printf("-- Не удалось открыть файл %s\n", argv[2]);
        print_usage();
        fclose(input_file);
        return;
    }

    interpretator(input_file, log_file);    
}

Token define_token(const char c) {
    const int n = 6;
    char operators[] = "+-*/^~";
    for (int i = 0; i < n; ++i) {
        if (c == operators[i]) {
            return OPERATOR;
        }
    }

    if (c >= 'A' && c <= 'Z') {
        return VARIABLE;
    }
    if (c >= '0' && c <= '9') {
        return NUMBER;
    }
    if (c == '(') {
        return OPEN_BRACKET;
    }
    if (c == ')') {
        return CLOSE_BRACKET;
    }
    return UNKNOWN;
}

error_code_t convert_and_push_to_queue(char *buffer_number, int* index_buffer_number, LinkedList_Element *input_queue) {
    buffer_number[*index_buffer_number] = '\0';
    // если сейчас не число, а до этого было число 
    // значит надо преобразовать его в int и добавить во входную очередь
    char *endptr;
    int value = strtol(buffer_number, &endptr, 10);
    if (*endptr != '\0') {
        printf("-- Ошибка при преобразовании числа\n");
        return ERROR_PARSE_TOKENS;
    }

    // обнуляем буффер
    *index_buffer_number = 0;
    buffer_number[*index_buffer_number] = '\0';

    // значит получилось преобразовать число
    // создаем элемент и добавляем его во входную очередь
    Element element;
    element.token = NUMBER;
    element.value.int_value = value;

    enqueue_Element(input_queue, element);

    return SUCCESS;
}

error_code_t parse_tokens(char *str_expression, LinkedList_Element *input_queue) {
    int index = 0;
    char c = str_expression[index++];
    char prev_c = '\0';

    char buffer_number[100] = "\0";
    int index_buffer_number = 0;
    while (c != '\0') {
        if (define_token(c) == NUMBER) {
            buffer_number[index_buffer_number++] = c; // добавляем в буффер
        }                

        else if (define_token(prev_c) == NUMBER) {
            error_code_t error = convert_and_push_to_queue(buffer_number, &index_buffer_number, input_queue);
            if (error != SUCCESS) return error;
        }

        Token cur_token = define_token(c);
        if (cur_token != NUMBER && cur_token != UNKNOWN) {
            Element element;
            element.token = cur_token;
            element.value.char_value = c;

            enqueue_Element(input_queue, element);
        }
        if (cur_token == UNKNOWN) {
            printf("-- Неизвестный символ в выражении\n");
            return ERROR_PARSE_TOKENS;
        }

        prev_c = c;
        c = str_expression[index++];
    }

    if (define_token(prev_c) == NUMBER) {
        // если в конце осталось необработанное число 
        error_code_t error =convert_and_push_to_queue(buffer_number, &index_buffer_number, input_queue);
        if (error != SUCCESS) return error;
    }

    return SUCCESS;
}


error_code_t handle_type_operation(char *str, TypeOperation type_operation, char *str_expression) {
    switch (type_operation) {
        case (ASSIGNMENT):
            strcpy(str_expression, str + 2); // A=B 
            break;
        case (PRINT):
            strcpy(str_expression, str + 6); // PRINT(A)
            str_expression[strlen(str_expression) - 1] = '\0';
            break;
        default:
            printf("-- Ошибка записи\n");
            return ERROR_WITH_EXPRESSION;
    }
    return SUCCESS;
}

error_code_t calculate_binary_operator(Element operator, Element operand_1, Element operand_2, int* result) {
    switch (operator.value.char_value) {
        case '+':
            *result = operand_1.value.int_value + operand_2.value.int_value;
            break;
        case '-':
            *result = operand_1.value.int_value - operand_2.value.int_value;
            break;
        case '*':
            *result = operand_1.value.int_value * operand_2.value.int_value;
            break;
        case '/':
            if (operand_2.value.int_value == 0) {
                printf("-- Деление на ноль\n");
                return ERROR_CALCULATE;
            }
            *result = operand_1.value.int_value / operand_2.value.int_value;
            break;
        case '^':
            *result = fast_raise_to_the_power(operand_1.value.int_value, operand_2.value.int_value);
            break;
        default:
            printf("-- Ошибка при вычислении\n");
            return ERROR_CALCULATE;
    }
    return SUCCESS;
}

error_code_t handle_unary_operator(LinkedList_Element *temp_stack) {
    // нужно извлечь элемент, и преобразовать его и добавить обратно в стек

    if (temp_stack->size == 0) {
        printf("-- Ошибка при вычислении выражения\n");
        return ERROR_CALCULATE;
    }
    Element top_stack = peek_stack_Element(temp_stack);
    pop_stack_Element(temp_stack);

    Element new_stack_element;
    new_stack_element.token = NUMBER;
    new_stack_element.value.int_value = top_stack.value.int_value * (-1); // унарный только минус 

    push_stack_Element(temp_stack, new_stack_element);

    return SUCCESS;
}

error_code_t handle_binary_operator(Element top_element, LinkedList_Element *temp_stack) {
    // достаем два операнда из стека
    // причем первым достается второй элемент 
    // вторым достается первый элемент
    // производим соответствующую операцию
    // и обратно пихаем в стек

    if (temp_stack->size < 2) {
        printf("-- Ошибка при вычислении выражения\n");
        return ERROR_CALCULATE;
    }

    Element top_stack = peek_stack_Element(temp_stack);
    pop_stack_Element(temp_stack);
    Element second_top_stack = peek_stack_Element(temp_stack);
    pop_stack_Element(temp_stack);

    int cur_result = 0;
    error_code_t error = calculate_binary_operator(top_element, second_top_stack, top_stack, &cur_result);
    if (error != SUCCESS) return error;

    Element new_stack_element;
    new_stack_element.token = NUMBER;
    new_stack_element.value.int_value = cur_result;

    push_stack_Element(temp_stack, new_stack_element);

    return SUCCESS;
}

error_code_t handle_variable(Element top_element, int* table_variables, LinkedList_Element *temp_stack) {
    // если это переменная, то надо посмотреть, если ли она в таблице переменных
    int index = top_element.value.char_value - 'A';
    if (table_variables[index] == INT_MIN) {
        printf("-- Неизвестная переменная: %c\n", top_element.value.char_value);
        return ERROR_CALCULATE;
    }

    Element new_stack_element;
    new_stack_element.token = NUMBER;
    new_stack_element.value.int_value = table_variables[index];
    push_stack_Element(temp_stack, new_stack_element);

    return SUCCESS;
}

error_code_t calculate_expression(LinkedList_Element *output_queue, int* table_variables, int *result) {
    // вычисление выражения в постфиксной форме записи

    // стэк для временного хранения операндов
    LinkedList_Element temp_stack = create_list_stack_queue();

    while (output_queue->size != 0) {
        Element top_element = peek_queue_Element(output_queue); // получаем верхний элемент

        dequeue_Element(output_queue);

        if (top_element.token == OPERATOR) {
            // если это оператор, то надо проверить, бинарный или унарный этот оператор
            if (top_element.value.char_value == '~') {
                // значит это унарный оператор

                error_code_t error = handle_unary_operator(&temp_stack);
                if (error != SUCCESS) return error;
            }

            else {
                // значит это бинарный оператор                
                error_code_t error = handle_binary_operator(top_element, &temp_stack);
                if (error != SUCCESS) return error;
            }
        }

        else if (top_element.token == NUMBER) {
            // если число сразу добавляем в стек
            push_stack_Element(&temp_stack, top_element);
        }

        else if (top_element.token == VARIABLE) {
            error_code_t error = handle_variable(top_element, table_variables, &temp_stack);
            if (error != SUCCESS) return error;
        }

        else {
            // что то неизвестное
            printf("-- Ошибка в парсинге выражения\n");
            return ERROR_CALCULATE;
        }
    }

    if (temp_stack.size != 1) {
        printf("-- Ошибка в вычислении выражения\n");
        return ERROR_CALCULATE;
    }

    Element result_element = peek_stack_Element(&temp_stack); 
    *result = result_element.value.int_value;

    return SUCCESS;
}

void handle_final_logic(char *str, int result, TypeOperation type_operation, int* table_variables, FILE* log_file, int count) {
    // логирование и финальная логика
    fprintf(log_file, "[%d] %s | ", count, str);


    if (type_operation == ASSIGNMENT) {
        // тогда нужно присвоить переменной результат
        int index = str[0] - 'A';
        table_variables[index] = result;
    }

    else if (type_operation == PRINT) {
        // тогда нужно вывести результат
        printf("%d\n", result);

    }

    for (int i = 0; i < 26; ++i) {
        if (table_variables[i] != INT_MIN) {
            fprintf(log_file, "%c=%d ", i + 'A', table_variables[i]);
        }
    }

    if (type_operation == ASSIGNMENT) {
        fprintf(log_file, "| Assignment\n");
    }
    else if (type_operation == PRINT) {
        fprintf(log_file, "| Print\n");
    }

    fflush(log_file);
}


error_code_t interpretator(FILE* input_file, FILE* log_file) {
    // таблица переменных
    int table_variables[26];
    for (int i = 0; i < 26; ++i) table_variables[i] = INT_MIN;
    
    error_code_t error = SUCCESS;

    int count = 1;
    
    char str[100];
    while (!feof(input_file)) {
        fgets(str, sizeof(str), input_file);

        // удаляем пробелы из строки
        delete_spaces_and_upper_case(str);  

        // определяем тип операции
        TypeOperation type_operation; 
        define_type_operation(str, &type_operation);

        // в зависимости от типа операции меняется логика программы
        char str_expression[100]; // правая часть равно (либо что в скобках команды print)
        error = handle_type_operation(str, type_operation, str_expression);        
        if (error != SUCCESS) return error;
        
        // входная очередь для токенов
        LinkedList_Element input_queue = create_list_stack_queue();
        
        // парсим выражение на токены
        error = parse_tokens(str_expression, &input_queue); // распарсить исходное выражение на токены
        if (error != SUCCESS) return error;

        // выходная очередь для вычисления выражения
        LinkedList_Element output_queue = create_list_stack_queue();

        // алгоритм дейкстры для парсинга выражения
        error = parse_expression(&input_queue, &output_queue);
        if (error != SUCCESS) return error;

        // вычислить выражение в постфиксной форме записи
        int result = 0; 
        error = calculate_expression(&output_queue, table_variables, &result);
        if (error != SUCCESS) return error;

        // выполнение логики (либо присваивание, либо принт) + логирование
        handle_final_logic(str, result, type_operation, table_variables, log_file, count);

        ++count;
    }

    return SUCCESS;
}