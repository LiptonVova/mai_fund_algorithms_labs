#include <stdio.h>
#include "include/overscanf.h"

void demo_oversscanf() {
    printf("                 ДЕМОНСТРАЦИЯ oversscanf                  \n");
    
    printf("Тест 1: Все пользовательские спецификаторы\n");

    int roman_val, custom_val_lower, custom_val_upper;
    unsigned int zeck_val;
    const char *input1 = "XIV:101001:1a:1A";
    
    int base1 = 16;
    int base2 = 16;
    int result1 = oversscanf(input1, "%Ro:%Zr:%Cv:%CV", &roman_val, &zeck_val, &custom_val_lower, base1, &custom_val_upper, base2);
    
    printf("Ввод:          \"%s\"\n", input1);
    printf("Формат:        \"%%Ro:%%Zr:%%Cv:%%CV\"\n");
    printf("Результат:     %d (успешно считанных полей)\n", result1);
    printf("Римское:       %d (ожидалось: 14)\n", roman_val);
    printf("Цекендорф:     %u (ожидалось: 3)\n", zeck_val);
    printf("Cv (hex):      %d (ожидалось: 26)\n", custom_val_lower);
    printf("CV (hex):      %d (ожидалось: 26)\n", custom_val_upper);
    printf("Статус:        %s\n\n", (result1 == 4 && roman_val == 14 && zeck_val == 3 && custom_val_lower == 26 && custom_val_upper == 26) ? "УСПЕХ" : "ОШИБКА");
    
    printf("Тест 2: Смешанные спецификаторы (стандартные + пользовательские)\n");
    
    int std_int, roman_num, custom_num;
    char str_buffer[50];
    float float_val;
    const char *input2 = "42 Hello 3.14 CXLII 2f";
    
    int base3 = 16;
    int result2 = oversscanf(input2, "%d %s %f %Ro %Cv", &std_int, str_buffer, &float_val, &roman_num, &custom_num, base3);
    
    printf("Ввод:          \"%s\"\n", input2);
    printf("Формат:        \"%%d %%s %%f %%Ro %%Cv\"\n");
    printf("Результат:     %d (успешно считанных полей)\n", result2);
    printf("Целое:         %d\n", std_int);
    printf("Строка:        \"%s\"\n", str_buffer);
    printf("Дробное:       %.2f\n", float_val);
    printf("Римское:       %d (ожидалось: 142)\n", roman_num);
    printf("Cv (hex):      %d (ожидалось: 47)\n", custom_num);
    printf("Статус:        %s\n\n", (result2 == 5 && roman_num == 142 && custom_num == 47) ? "УСПЕХ" : "ОШИБКА");
    
    printf("Тест 3: Обработка невалидных римских чисел\n");
    
    int invalid_roman1, invalid_roman2;
    const char *input3 = "IIII ABC";
    
    int result3 = oversscanf(input3, "%Ro %Ro", &invalid_roman1, &invalid_roman2);
    
    printf("Ввод:          \"%s\"\n", input3);
    printf("Формат:        \"%%Ro %%Ro\"\n");
    printf("Результат:     %d (успешно считанных полей)\n", result3);
    printf("Статус:        %s\n\n", (result3 == 0) ? "УСПЕХ" : "ОШИБКА");
    
    printf("Тест 4: Различные системы счисления\n");
    
    int bin_num, oct_num, dec_num, hex_num_lower, hex_num_upper;
    const char *input4 = "1101:15:255:ff:FF";
    
    int base_bin = 2;
    int base_oct = 8;
    int base_dec = 10;
    int base_hex1 = 16;
    int base_hex2 = 16;
    
    int result4 = oversscanf(input4, "%Cv:%Cv:%Cv:%Cv:%CV", 
                           &bin_num, base_bin, 
                           &oct_num, base_oct, 
                           &dec_num, base_dec, 
                           &hex_num_lower, base_hex1, 
                           &hex_num_upper, base_hex2);
    
    printf("Ввод:          \"%s\"\n", input4);
    printf("Формат:        \"%%Cv:%%Cv:%%Cv:%%Cv:%%CV\"\n");
    printf("Результат:     %d (успешно считанных полей)\n", result4);
    printf("Двоичное:      %d (1101 = 13)\n", bin_num);
    printf("Восьмеричное:  %d (15 = 13)\n", oct_num);
    printf("Десятичное:    %d (255)\n", dec_num);
    printf("Cv (hex):      %d (ff = 255)\n", hex_num_lower);
    printf("CV (hex):      %d (FF = 255)\n", hex_num_upper);
    printf("Статус:        %s\n\n", (result4 == 5 && bin_num == 13 && oct_num == 13 && dec_num == 255 && hex_num_lower == 255 && hex_num_upper == 255) ? "УСПЕХ" : "ОШИБКА");
}


void demo_overfscanf() {
    printf("                   ДЕМОНСТРАЦИЯ overfscanf                   \n");
    
    FILE *file = fopen("test_data.txt", "r");
    if (!file) {
        printf("Ошибка: Не удалось открыть файл test_data.txt\n");
        return;
    }
    
    printf("Тест 1: Чтение всех спецификаторов из файла\n");
    
    int file_roman, file_custom_lower, file_custom_upper;
    unsigned int file_zeck;
    char file_str[50];
    float file_float;
    
    int base_file1 = 16;
    int base_file2 = 16;
    
    int result = overfscanf(file, "%s %f %Ro %Zr %Cv %CV", 
                          file_str, &file_float, &file_roman, &file_zeck, 
                          &file_custom_lower, base_file1, &file_custom_upper, base_file2);
    
    printf("Прочитано полей: %d\n", result);
    printf("Строка:          \"%s\"\n", file_str);
    printf("Дробное:         %.2f\n", file_float);
    printf("Римское:         %d\n", file_roman);
    printf("Цекендорф:       %u\n", file_zeck);
    printf("Cv (hex):        %d\n", file_custom_lower);
    printf("CV (hex):        %d\n", file_custom_upper);
    
    int success = (result == 6 && 
                  strcmp(file_str, "Hello") == 0 && 
                  file_float == 3.14f && 
                  file_roman == 42 && 
                  file_zeck == 6 && 
                  file_custom_lower == 26 && 
                  file_custom_upper == 26);
    
    printf("Статус:          %s\n\n", success ? "УСПЕХ" : "ОШИБКА");
    
    fclose(file);
}


int main() {
    printf("================================================================\n");
    printf("|          ТЕСТИРОВАНИЕ ФУНКЦИЙ overfscanf/oversscanf          |\n");
    printf("|                     Пользовательские флаги:                  |\n");
    printf("|                 %%Ro - римские числа                          |\n");
    printf("|                 %%Zr - цекендорфово представление             |\n");
    printf("|                 %%Cv - система счисления (нижний регистр)     |\n");
    printf("|                 %%CV - система счисления (верхний регистр)    |\n");
    printf("================================================================\n\n");


    demo_oversscanf();
    demo_overfscanf();

    return 0;


}