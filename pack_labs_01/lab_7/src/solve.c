#include "../include/solve.h"
#include <stdio.h>
#include <stdlib.h>


int handler_min_cc(char* number, int length) {
    int min_cc = 2;
    char c;
    int cur_cc;
    for (int i = 0; i < length; ++i) {
        c = number[i];
        if (c >= '0' && c <= '9') {
            cur_cc = (c - '0') + 1;
        }
        else if (c >= 'A' && c <= 'Z') {
            cur_cc = (c - 'A') + 11;
        }
        else if (c >= 'a' && c <= 'z') {
            cur_cc = (c - 'a') + 11;
        }
        else {
            return -1;
        }
        if (cur_cc >= min_cc) {
            min_cc = cur_cc;
        }
    }

    return min_cc;
}

int perevod_min_cc_to_ten_cc(char* number, int length, int min_cc) {
    int res = 0;
    char c;
    int r;
    for (int i = 0; i < length; ++i) {
        c = number[i];
        if (c >= '0' && c <= '9') {
            r = c - '0';
        }
        else if (c >= 'A' && c <= 'Z') {
            r = (c - 'A') + 10; 
        }
        else {
            r = (c - 'a') + 10;
        }
        res = res * min_cc + r;
    }
    return res;
}



int solve(FILE* input, FILE* output) {
    int buff_size = 100;
    char * buff = malloc(sizeof(char) * buff_size);
    int index = 0;
    int index_word;
    char c;
    int min_cc;
    do {
        c = fgetc(input);
        if (c == '\n' || c == ' ' || c == EOF) {
            if (index == 0) {
                continue;
            }
            char* word = malloc(sizeof(char) * index);
            if (!word) {
                printf("Ошибка при выделении памяти\n");
                return -1;;
            }

            index_word = 0;
            for (int i = 0; i < index; ++i) {
                word[index_word++] = buff[i];
            } 
            min_cc = handler_min_cc(word, index_word);
            if (min_cc == -1) {
                printf("Неизвестный символ\n");
                return -1;
            }

            int answer = perevod_min_cc_to_ten_cc(word, index_word, min_cc);

            fprintf(output, "%d\n", answer);


            free(word);
            
            buff_size = 100;
            char * temp = realloc(buff, sizeof(char) * buff_size);
            if (!temp) {
                printf("Ошибка при выделении памяти\n");
                return -1;
            }

            buff = temp;
            index = 0;
            continue;
        }

        if (index + 1 == buff_size) {
            buff_size *= 2;
            char * temp = realloc(buff, sizeof(char) * buff_size);
            if (!temp) {
                printf("Ошибка при выделении памяти\n");
                return -1;
            }

            buff = temp;
        }

        buff[index++] = c;
    } while ( c != EOF);
    return 0;
}