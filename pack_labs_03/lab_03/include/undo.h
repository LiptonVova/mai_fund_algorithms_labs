#ifndef UNDO_H
#define UNDO_H

#include "linkedList.h"
#include "config.h"
#include "utils.h"
#include "search.h"

// отслеживаю только три команды, которые как то меняют структуру списка
typedef enum {
    DEFAULT_COMMAND, 
    ADD_LIVER, // добавление жителя
    EDIT_LIVER, // изменение жителя 
    DELETE_LIVER, // удаления жителя
    SAVE_FILE // записали в файл
} NameCommand;


// будем хранить команды в структуре Command
typedef struct {
    NameCommand name_command; // название команды
    Liver new_liver; // уже измененный житель
    // если команда == edit, то liver - это житель после изменения 
    // если команда == delete, то liver - это defalt liver
    // если команда ==  add, то это новый житель
    Liver old_liver; // житель до изменений
    // если команда == edit || команда == delete, то liver - это житель до изменения
    // если команда == add, то это default житель 

    // для команды записи в файл
    LinkedList_Liver livers; // двусвязный список на момент записи в файл
} Command;

DEFINE_LIST_STACK(Command) 

LinkedList_Command create_stack_command();

void handle_undo(LinkedList_Liver *livers, LinkedList_Command *stack_commands, char* name_file_output, FILE* file_output);



#endif