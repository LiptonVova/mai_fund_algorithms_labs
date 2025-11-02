#include "../include/config.h"


void delete_func(Liver liver) {
}

Liver copy_func(Liver other) {
    Liver cur;
    cur.id = other.id;
    strcpy(cur.surname, other.surname);
    strcpy(cur.name, other.name);
    strcpy(cur.middle_name, other.middle_name);
    cur.day_birthday = other.day_birthday;
    cur.month_birthday = other.month_birthday;
    cur.year_birthday = other.year_birthday;
    cur.gender = other.gender;
    cur.average_income = other.average_income;
    return cur;
}

int comp(Liver liver_1, Liver liver_2) {
    int comp_id_name = liver_1.id == liver_2.id && strcmp(liver_1.surname, liver_2.surname) && \
                    strcmp(liver_1.name, liver_2.name) &&  strcmp(liver_1.middle_name, liver_2.middle_name);
    int comp_birthday = liver_1.day_birthday == liver_2.day_birthday && liver_1.month_birthday == liver_2.month_birthday && \
                    liver_1.year_birthday == liver_2.year_birthday;
    int comp_gender_income = liver_1.gender == liver_2.gender && liver_1.average_income == liver_2.average_income;
    return comp_id_name && comp_birthday && comp_gender_income;
}

Liver default_constructor() {
    Liver liver;
    liver.id = 0;
    strcpy(liver.surname,"\0");
    strcpy(liver.name, "\0");
    strcpy(liver.middle_name, "\0");
    liver.day_birthday = 0;
    liver.month_birthday = 0;
    liver.year_birthday = 0;
    liver.gender = 'M';
    liver.average_income = 0;
    return liver;
}