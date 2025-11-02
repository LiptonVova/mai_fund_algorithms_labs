#include "../include/undo.h"

void delete_func_command(Command command) {
    delete_func(command.new_liver);
    delete_func(command.old_liver);
}

Command copy_func_command(Command other) {
    Command command;
    command.name_command = other.name_command;
    command.new_liver = copy_func(other.new_liver);
    command.old_liver = copy_func(other.old_liver);
    return command;
}

int comp_command(Command command_1, Command command_2) {
    return command_1.name_command == command_2.name_command && \
            comp(command_1.new_liver, command_2.new_liver) && comp(command_1.old_liver, command_2.old_liver);
}

Command default_constructor_command() {
    Command command;
    command.name_command = DEFAULT_COMMAND;
    command.new_liver = default_constructor();
    command.old_liver = default_constructor();
    return command;
}


// функция создания стэка для хранения команд программы
LinkedList_Command create_stack_command() {
    LinkedList_Command stack = create_list_Command(delete_func_command, copy_func_command, \
                                                    comp_command, default_constructor_command);
    return stack;
}

void handle_cancel_add_liver(LinkedList_Liver *livers, Command command) {
    size_t id = command.new_liver.id;
    
    size_t index = 0;

    Node_Liver* cur_node = search_id(*livers, id, &index);

    if (!cur_node) {
        printf("--Ошибка при отмены n/2 действий(command = add)\n");
        printf("--нет такого жителя...\n");
        return;
    }

    delete_at_list_Liver(livers, index);
}

void handle_cancel_edit_liver(LinkedList_Liver *livers, Command command) {
    // команда редактирования, то есть нам надо заменить нового жителя старым
    size_t id = command.new_liver.id;

    size_t index = 0;

    Node_Liver* cur_node = search_id(*livers, id, &index);

    if (!cur_node ) {
        printf("--Ошибка при отмены n/2 действий(command = add)\n");
        printf("--нет такого жителя...\n");
        return;
    }

    delete_at_list_Liver(livers, index);
    insert_sort_livers(livers, command.old_liver);
}
void handle_cancel_delete_liver(LinkedList_Liver *livers, Command command) {
    // команда удаления, то есть нам надо добавить удаленного жителя

    insert_sort_livers(livers, command.old_liver);
}

void handle_undo(LinkedList_Liver *livers, LinkedList_Command *stack_commands) {
    // функция, которая возвращает последние N/2 команд 

    size_t size_stack = stack_commands->size;
    size_t n = (size_stack == 0 ? 0 : size_stack / 2); // округляем вниз

    for (size_t i = 0; i < n; ++i) {
        Command command = peek_stack_Command(stack_commands);

        switch (command.name_command) {
            case (ADD_LIVER):
                handle_cancel_add_liver(livers, command);
                break;
            case (EDIT_LIVER):
                handle_cancel_edit_liver(livers, command);
                break;
            case (DELETE_LIVER):
                handle_cancel_delete_liver(livers, command);
                break;
            default:
                printf("--Неизвестная команда\n");
                printf("--Произошла ошибка при выполнении отмены последних n/2 команд\n");
                break;
        }

        pop_stack_Command(stack_commands);
    }

    // очищаем стэк
    erase_list_Command(stack_commands);
}