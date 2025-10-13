#include "../include/functions.h"


int open_file(char* message, char* type, char *filename, FILE **file) {
    printf("%s: ", message);
    scanf("%s", filename);

    *file = fopen(filename, type);
    if (!(*file)) {
        printf("Ошибка открытия файла %s\n", filename);
        return ERROR_OPEN_FILE;
    }

    return SUCCESS;
}

void handle_eighty_char_is_space(char* cur_str, char**str) {
    int index = 80;
    while (index >= 0 && (*str)[index] != ' ') {
        index--; // дошли до первого пробела перед последним словом
    }

    while (index >= 0 && (*str)[index] == ' ') {
        index--; // доходим до самого крайнего символва предпоследнего слова
    }


    if (index == -1) {
        // одно большое слово, которое больше чем 80 символов
        // в задаче не сказано как это хэндлить, поэтому я просто выведу вот эти 80 символов
        // то есть разорвал слово

        strncpy(cur_str, *str, 80);
        cur_str[80] = '\0';
        *str += 80;
    }
    else {
        index++; // указываем на первый пробел сразу после предпоследнего слова 
        strncpy(cur_str, *str, index);
        cur_str[index] = '\0';
        *str += index; // меняем указатель на str
    }
}

void add_spaces_in_string_impl(int count_spaces_for_gap, int count_spaces_remainder, char * cur_str, FILE *output) {
    char result[81];
    int index_cur_str = 0;
    for (int i = 0; i < 80; ++i) {
        result[i] = cur_str[index_cur_str];
        index_cur_str++;
        if (cur_str[index_cur_str] == ' ') {
            while (cur_str[index_cur_str] == ' ') { // если пробел, то надо добавить новых пробелов
                index_cur_str++;
            }
            for (int j = 0; j < count_spaces_for_gap; ++j) {
                result[++i] = ' ';
            }
            if (count_spaces_remainder > 0) {
                result[++i] = ' ';
                count_spaces_remainder--;
            } 
        }
    }
    result[80] = '\0';
    fputs(result, output);
    fputc('\n', output);
}

void add_spaces_in_string(char* cur_str, FILE*output) {
    int index = strlen(cur_str);

    int all_count_spaces = 0;

    int count_words = 1;
    for (int i = 1; i < index; ++i) {
        if (cur_str[i - 1] != ' ' && cur_str[i] == ' ') { // учитывает двойные пробелы
            count_words++;
        }
        if (cur_str[i] == ' ') {
            all_count_spaces++; // если есть двойные пробелы, то мы все равно их равномерно распределим
        }
    }

    all_count_spaces += (80 - index);

    const int delim = (count_words - 1 == 0) ? 1 : (count_words - 1);  

    const int count_spaces_for_gap = all_count_spaces / delim;
    int count_spaces_remainder = all_count_spaces % delim;

    add_spaces_in_string_impl(count_spaces_for_gap, count_spaces_remainder, cur_str, output);
}


void handle_string(char *str, FILE *output) {
    
    while (str) {
        while (str && *str == ' ') { // убираем лишние пробелы, если они есть в начале
            str++;
        }
        if (!str) {
            break;
        }

        if (strlen(str) <= 80) { // последняя строка имеет меньше 80 символов
            fputs(str, output);
            break;
        }

        char cur_str[81];
        cur_str[0] = '\0';
        if (str[80] == ' ') { // 81 символ
            // первые 80 символов хорошие, можно обрабатывать
            strncpy(cur_str, str, 80);
            cur_str[80] = '\0';
            str += 80; // меняем указатель на str
        }

        else if (str[80] != ' ') {
            // разорвали слово - надо найти предпоследнее и до него все скопировать
            handle_eighty_char_is_space(cur_str, &str);
        }

        // теперь в cur_str хранится строка <= 80, в котором последний символ равен либо пробел, либо конец слова
        if (strlen(cur_str) < 80) {
            // тогда нужно добавлять равномерно пробелы 
            add_spaces_in_string(cur_str, output);
        }
        else if (strlen(cur_str) == 80) {
            // тогда последний символ - это конец слова, делать нечего не надо
            fputs(cur_str, output);
            fputc('\n', output);
        }
    }
}

void solve(FILE *input, FILE *output) {
    char str[1000];
    str[0] = '\0';
        while (fgets(str, sizeof(str), input) != NULL) {        
        if (strlen(str) <= 80) {
            size_t len = strlen(str);
            int index = 0;
            while (index < len && str[index] == ' ') {
                index++;
            }
            char str_without_first_spaces[1000];
            strcpy(str_without_first_spaces, str+index);
            if (*str_without_first_spaces == '\n') {
                continue;
            }
            fputs(str_without_first_spaces, output);
        }
        else {
            handle_string(str, output);
        }
    }
}