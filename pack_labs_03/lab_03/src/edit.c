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
    printf("Введите новое число рождения: ");
    scanf("%d", &new_day);
    printf("Введите новый месяц рождения (число от 1 до 12): ");
    scanf("%d", &new_month);
    printf("Введите новый год рождения: ");
    scanf("%d", &new_year);
    
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
    scanf("%lf", &new_income);

    cur_node->data.average_income = new_income;
    printf("Успешно изменено!\n");
}