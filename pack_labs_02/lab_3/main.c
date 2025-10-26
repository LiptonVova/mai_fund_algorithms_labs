#include "include/print.h"
#include <stdio.h>


int main() {
    overfprintf(stdout, "1. Стандартные флаги:\n");
    overfprintf(stdout, "Стандартные: %d %f %s\n", 42, 3.14, "test");
    overfprintf(stdout, "\n");
    
    overfprintf(stdout, "2. %%Ro - римские цифры:\n");
    overfprintf(stdout, "1994 = %Ro\n", 1994);
    overfprintf(stdout, "2023 = %Ro\n", 2023);
    overfprintf(stdout, "49 = %Ro\n", 49);
    overfprintf(stdout, "\n");
    
    overfprintf(stdout, "3. %%Zr - цекендорфово представление:\n");
    overfprintf(stdout, "10 = %Zr\n", 10u);
    overfprintf(stdout, "20 = %Zr\n", 20u);
    overfprintf(stdout, "15 = %Zr\n", 15u);
    overfprintf(stdout, "34 = %Zr\n", 34u);
    overfprintf(stdout, "7 = %Zr\n", 7u);
    overfprintf(stdout, "4 = %Zr\n", 4u);
    overfprintf(stdout, "12 = %Zr\n", 12u);
    overfprintf(stdout, "3 = %Zr\n", 3u);
    overfprintf(stdout, "1 = %Zr\n", 1u);
    overfprintf(stdout, "0 = %Zr (завершающая единица) \n", 0u);
    overfprintf(stdout, "\n");
    
    overfprintf(stdout, "4. %%Cv и %%CV - системы счисления:\n");
    overfprintf(stdout, "255 в 16-ричной (нижний): %Cv\n", 255, 16);
    overfprintf(stdout, "255 в 16-ричной (верхний): %CV\n", 255, 16);
    overfprintf(stdout, "123 в 8-ричной: %Cv\n", 123, 8);
    overfprintf(stdout, "42 в 2-ичной: %Cv\n", 42, 2);
    overfprintf(stdout, "\n");

    overfprintf(stdout, "5. %%to и %%TO - преобразование из строки:\n");
    overfprintf(stdout, "\"ff\" из 16-ричной: %to\n", "ff", 16);
    overfprintf(stdout, "\"FF\" из 16-ричной: %TO\n", "FF", 16);
    overfprintf(stdout, "\"1010\" из 2-ичной: %to\n", "1010", 2);
    overfprintf(stdout, "\n");
    
    overfprintf(stdout, "6. Дампы памяти:\n");
    int test_int = -1;
    unsigned int test_uint = 1;
    double test_double = 3.14159;
    float test_float = 2.71828f;
    
    overfprintf(stdout, "%%mi (int --1): %mi\n", test_int);
    overfprintf(stdout, "%%mu (uint 1): %mu\n", test_uint);
    overfprintf(stdout, "%%md (double 3.14159): %md\n", test_double);
    overfprintf(stdout, "%%mf (float 2.71828): %mf\n", test_float);
    overfprintf(stdout, "\n");
    
    overfprintf(stdout, "7. Комбинированное использование:\n");
    overfprintf(stdout, "Римские: %Ro, Цекендорф: %Zr, HEX: %Cv\n", 
                2023, 20u, 255, 16);
    overfprintf(stdout, "\n");
    
    overfprintf(stdout, "8. Тестирование oversprintf:\n");
    char buffer[256];
    int chars_written;
    
    chars_written = oversprintf(buffer, "Rim: %Ro, HEX: %Cv", 49, 255, 16);
    overfprintf(stdout, "Результат: %s\n", buffer);
    overfprintf(stdout, "Записано символов: %d\n", chars_written);
    
    chars_written = oversprintf(buffer, "Dump int: %mi", test_int);
    overfprintf(stdout, "Результат: %s\n", buffer);
    overfprintf(stdout, "Записано символов: %d\n", chars_written);

    overfprintf(stdout, "\n9. Проверка возвращаемого значения:\n");
    int count1 = overfprintf(stdout, "Test: %d = %Ro\n", 100, 100);
    overfprintf(stdout, "overfprintf вернул: %d\n", count1);
    
    int count2 = oversprintf(buffer, "Test: %d = %Ro\n", 100, 100);
    overfprintf(stdout, "oversprintf вернул: %d\n", count2);
    
    return 0;
}