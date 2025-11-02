#ifndef UTILS_H
#define UTILS_H


#include "config.h"
#include <stdio.h>


void write_in_file_desciptor(FILE *output, LinkedList_Liver livers);
LinkedList_Liver copy_linked_list_livers(LinkedList_Liver livers);

void insert_sort_livers(LinkedList_Liver *livers, Liver liver);
LinkedList_Liver read_livers_from_file(FILE* input);

// функции вывода любой информации в терминал  
void print_info(); // основное меню
void print_info_search(); // меню выбора поиска
void print_liver(FILE* output, const Liver liver); // вывод жителя
void print_info_edit(); // меню редактирования жителя



#endif