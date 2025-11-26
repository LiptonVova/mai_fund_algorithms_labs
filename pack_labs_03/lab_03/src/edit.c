#include "../include/edit.h"

void handle_edit_surname(Node_Liver* cur_node) {
    printf("Введите новую фамилию: ");
    char new_surname[100];
    scanf("%s", new_surname);

    strcpy(cur_node->data.surname, new_surname);

    printf("Успешно изменено!\n");
}
void handle_edit_name(Node_Liver* cur_node) {
    printf("Введите новое имя: ");
    char new_name[100];
    scanf("%s", new_name);

    strcpy(cur_node->data.name, new_name);

    printf("Успешно изменено!\n");
}
void handle_edit_middle_name(Node_Liver* cur_node) {
    printf("Введите новое отчество: ");
    char new_middle_name[100];
    scanf("%s", new_middle_name);

    strcpy(cur_node->data.middle_name, new_middle_name);

    printf("Успешно изменено!\n");
}
void handle_edit_date_birthday(Node_Liver* cur_node) {
    int new_day = 0, new_month = 0, new_year = 0;
    char *endptr;
    printf("Введите новое число рождения: ");
    // scanf("%d", &new_day);
    char day_b[100] = "\0";
    scanf("%s", day_b);
    new_day = strtol(day_b, &endptr, 10);
    while (*endptr != '\0' ) {
        printf("Пожалуйста попробуйте еще раз: ");
        char temp_day_b[100] = "\0";
        scanf("%s", temp_day_b);
        new_day = strtol(temp_day_b, &endptr, 10);
    }

    printf("Введите новый месяц рождения (число от 1 до 12): ");
    // scanf("%d", &new_month);
    char month_b[100] = "\0";
    scanf("%s", month_b);
    new_month = strtol(month_b, &endptr, 10);
    while (*endptr != '\0' ) {
        printf("Пожалуйста попробуйте еще раз: ");
        char temp_month_b[100] = "\0";
        scanf("%s", temp_month_b);
        new_month = strtol(temp_month_b, &endptr, 10);
    }
    printf("Введите новый год рождения: ");
    // scanf("%d", &new_year);
    char year_b[100] = "\0";
    scanf("%s", year_b);
    new_year = strtol(year_b, &endptr, 10);
    while (*endptr != '\0' ) {
        printf("Пожалуйста попробуйте еще раз: ");
        char temp_year_b[100] = "\0";
        scanf("%s", temp_year_b);
        new_year = strtol(temp_year_b, &endptr, 10);
    }
    
    cur_node->data.day_birthday = new_day;
    cur_node->data.month_birthday = new_month;
    cur_node->data.year_birthday = new_year;

    printf("Успешно изменено!\n");
}
void handle_edit_gender(Node_Liver* cur_node) {
    printf("Введите новый пол (M - мужской, W - женский): ");
    char new_gender;
    scanf(" %c", &new_gender);
    new_gender = toupper(new_gender);

    cur_node->data.gender = new_gender;
    printf("Успешно изменено!\n");
}


void handle_edit_income(Node_Liver* cur_node) {
    printf("Введите новый среднемесячный доход: ");
    double new_income = 0;
    // scanf("%lf", &new_income);
    char income[100] = "\0";
    scanf("%s", income);
    char *endptr;
    new_income = strtod(income, &endptr);
    while (*endptr != '\0' ) {
        printf("Пожалуйста попробуйте еще раз: ");
        char temp_income[100] = "\0";
        scanf("%s", temp_income);
        new_income = strtod(temp_income, &endptr);
        
    }

    cur_node->data.average_income = new_income;
    printf("Успешно изменено!\n");
}