#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "include/validate.h"
#include "include/solve.h"

enum {
    SUCCESS,
    ERROR_WRONG_BASE,
    ERROR_WRONG_NUMBER,
    ERROR_MALLOC,
};


int main() {
    int base;
    char str[100];
    printf("Введите основание системы счисления от 2 до 36\n");
    scanf("%s", str);
    int flag = validate_base(str);
    if (!flag) {
        printf("Введите основание системы счисления от 2 до 36\n");
        return ERROR_WRONG_BASE;
    }
    base = atoi(str);
    if (base < 2 || base > 36) {
        printf("Введите основание системы счисления от 2 до 36\n");
        return ERROR_WRONG_BASE;
    }

    int size_buff = 100;
    char* buff = malloc(sizeof(char) * size_buff);
    if (!buff) {
        printf("Ошибка при выделении памяти\n");
        return ERROR_MALLOC;
    }
    buff[0] = '\0';
    int index = 0;
    
    int index_word = 0;
    
    int cur_result = 0;
    int max_result = cur_result;


    char* answer_str_view;
    int index_answer = 0;

    int flag_negative = 0;
    int flag_negative_result = 0;

    printf("Введите числа:\n");

    char stop_message[] = "stop";
    char stop_message_upper[] = "STOP";
    int size_stop_message = strlen(stop_message);
    
    char c;
    
    int count;
    while (1) {
        if (index == size_stop_message) {
            count = 0;
            for (int i = 0; i < size_stop_message; ++i) {
                if ((buff[i] == stop_message[i] || buff[i] == stop_message_upper[i])) {
                    count++;
                }
            }
            if (count == 4) {
                break;
            }
        }

        scanf("%c", &c);
        if (c == ' ' || c == '\n') {
            if (index == 0) { // слова нет 
                if (flag_negative) {
                    printf("Это не число\n");
                    return ERROR_WRONG_NUMBER;
                }
                continue;
            } 

            char * word = malloc(sizeof(char) * index);
            if (!word) {
                printf("Ошибка при выделении памяти\n");
                return ERROR_MALLOC;
            }

            index_word = 0;
            for (int i = 0; i < index; ++i) {
                word[index_word++] = buff[i]; 
            }

            cur_result = perevod_base_to_ten_cc(word, index_word, base);
            if (cur_result == -1) {
                printf("Данное число не может быть представлено в %d c/c\n", base);
                return ERROR_WRONG_NUMBER; 
            }

            if (abs(cur_result) > max_result) {
                max_result = abs(cur_result);
                index_answer = 0;

                // char * temp = realloc(answer_str_view, sizeof(char) * (index + 1));
                // if (!temp) {
                //     printf("Ошибка при выделении памяти\n");
                //     return ERROR_MALLOC;
                // }
                // answer_str_view = temp;
                answer_str_view = perevod_ten_cc_to_base(max_result, base);
                flag_negative_result = flag_negative;
            }
            buff[0] = '\0';
            index = 0;
            flag_negative = 0;
            free(word);
        }
        else if (c == '-') {
            if (index != 0) {
                printf("Невалидное число\n");
                return ERROR_WRONG_NUMBER;
            }
            if (flag_negative) {
                printf("Невалидное число\n");
                return ERROR_WRONG_NUMBER;
            }
            flag_negative = 1;
        }
        else {
            buff[index++] = c;
        }
    }

    char* result_9_cc = perevod_ten_cc_to_base(max_result, 9);
    char* result_18_cc = perevod_ten_cc_to_base(max_result, 18);
    char* result_27_cc = perevod_ten_cc_to_base(max_result, 27);
    char* result_36_cc = perevod_ten_cc_to_base(max_result, 36);

    if (flag_negative_result) {
        printf("максимальное число в %d c/c: -%s\n", base, answer_str_view);
        printf("максимальное число в 10 c/c: -%d\n", max_result);
        
        printf("максимальное число в 9 c/c: -%s\n", result_9_cc);
        printf("максимальное число в 18 c/c: -%s\n", result_18_cc);
        printf("максимальное число в 27 c/c: -%s\n", result_27_cc);
        printf("максимальное число в 36 c/c: -%s\n", result_36_cc);
    } 
    else {
        printf("максимальное число в %d c/c: %s\n", base, answer_str_view);
        printf("максимальное число в 10 c/c: %d\n", max_result);
        
        printf("максимальное число в 9 c/c: %s\n", result_9_cc);
        printf("максимальное число в 18 c/c: %s\n", result_18_cc);
        printf("максимальное число в 27 c/c: %s\n", result_27_cc);
        printf("максимальное число в 36 c/c: %s\n", result_36_cc);
    }

    free(result_9_cc);
    free(result_18_cc);
    free(result_27_cc);
    free(result_36_cc);



    free(buff);
    free(answer_str_view);

    return SUCCESS;
}