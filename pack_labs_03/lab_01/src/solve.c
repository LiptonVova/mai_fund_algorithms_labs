#include "../include/solve.h"


unsigned int bit_increment(unsigned int x) {
    // вычисление сложения в столбик
    unsigned int remain = 1;
    while (remain) {
        unsigned int temp = x & remain; // определяем где будут переносы (это где 1 и в первом и во втором слагаемых)
        x = x ^ remain; // складываем без учета каких либо переносов
        remain = temp << 1; // если были переносы, то переносим в следующий разряд и складываем заново
    }
    return x;
}

unsigned int bit_decrement(unsigned int x) {
    // вычитание в столбик

    unsigned int borrow = 1;
    while (borrow) {
        unsigned int temp = (~x) & borrow; // опеределяем в каком бите нужно занять единицу 
        // нужно найти где в x первый ноль, и при этом в borrow == 1 (поэтому нужно инвертировать биты)

        x = x ^ borrow; // вычитаем 
        borrow = temp << 1; // если остались заемы, то переносим заем в следующий разряд
    }
    return x;
}


void translate_to_base(const unsigned int number, const int r, char *result) {
    unsigned int copy_number = number;
    const unsigned int total_bits = 64;
    char cur_result[bit_increment(total_bits)];

    for (unsigned int i = 0; i < total_bits; i = bit_increment(i)) {
        cur_result[i] = '0';
    }
    cur_result[total_bits] = '\0';

    int index = bit_decrement(total_bits);

    const unsigned int mask = bit_decrement(1 << r); // r битов '1' для получения последних r битов числа

    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    unsigned int tmp = 0;
    while (copy_number != 0) {
        tmp = copy_number & mask;
        cur_result[index] = digits[tmp]; 
        index = bit_decrement(index);
        copy_number >>= r;
    }

    // Находим позицию первого ненулевого символа
    unsigned int start_pos = 0;
    for (; start_pos < bit_decrement(total_bits); start_pos = bit_increment(start_pos)) {
        if (cur_result[start_pos] != '0') break;
    }

    unsigned int j = 0; // позиция в результирующей строке 
    unsigned int current_pos = start_pos; // позиция в старой строке
    
    // Копируем символы пока не достигнем конца строки
    while (cur_result[current_pos] != '\0') {
        // Копируем текущий символ
        result[j] = cur_result[current_pos];
        
        // Переходим к следующим позициям
        j = bit_increment(j);
        current_pos = bit_increment(current_pos);
    }
    
    // Добавляем завершающий нуль
    result[j] = '\0';
}