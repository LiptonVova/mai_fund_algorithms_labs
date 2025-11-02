#ifndef CONFIG_H
#define CONFIG_H

#include "linkedList.h"
#include <string.h>

typedef struct {
    size_t id;
    char surname[100];
    char name[100];
    char middle_name[100];
    int day_birthday;
    int month_birthday;
    int year_birthday;
    char gender;
    double average_income;
} Liver ;

// двусвязный список жителей
DEFINE_LIST_STACK(Liver)

void delete_func(Liver liver); // десктруктор 
Liver copy_func(Liver other); // конструктор копирования
int comp(Liver liver_1, Liver liver_2); // компоратор
Liver default_constructor(); // дефолтный конструктор



#endif