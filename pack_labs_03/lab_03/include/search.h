#ifndef SEARCH_H
#define SEARCH_H

#include "config.h"
#include <ctype.h>
#include <stdio.h>
#include "utils.h"

Node_Liver* search_id(LinkedList_Liver livers, size_t id, size_t* index);

void handle_search_id(LinkedList_Liver livers);
void handle_search_surname(LinkedList_Liver livers);
void handle_search_name(LinkedList_Liver livers);
void handle_search_birthday(LinkedList_Liver livers);
void handle_search_gender(LinkedList_Liver livers);



#endif