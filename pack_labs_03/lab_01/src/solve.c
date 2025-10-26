#include "../include/solve.h"


void translate_to_base(const unsigned int number, const int r, char *result) {
    unsigned int copy_number = number;
    const int total_bits = sizeof(unsigned int) * 8;
    char cur_result[total_bits + 1];

    for (int i = 0; i < total_bits; ++i) {
        cur_result[i] = '0';
    }
    cur_result[total_bits] = '\0';

    int index = total_bits - 1;

    const unsigned int mask = (1 << r) - 1; // r битов '1' для получения последних r битов числа

    unsigned int tmp = 0;
    while (copy_number != 0) {
        tmp = copy_number & mask;
        cur_result[index] = tmp > 9 ? 'A' + (tmp - 10) : '0' + tmp; // получаем последние r битов числа 
        --index;
        copy_number >>= r;
    }

    int i = 0;
    for ( ; i < total_bits - 1; ++i) {
        if (cur_result[i] != '0') break;
    }

    strcpy(result, cur_result + i);
}