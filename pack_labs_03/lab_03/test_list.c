#include <stdio.h>
#include "include/linkedList.h"

DEFINE_LIST_STACK(int)

void delete_func(int value) {
    // Для int ничего особого не делаем
}

int copy_func(int value) {
    return value;
}

int comp(int value_1, int value_2) {
    return value_1 == value_2;
}

void print_list(LinkedList *list) {
    printf("List (%ld): ", list->size);
    for (int i = 0; i < list->size; ++i) {
        printf("%d", get_at_list(list, i));
        if (i < list->size - 1) printf("->");
    }
    printf("\n");
}

int default_constuctor() {
    return 0;
}

int main() {
    printf("=== ТЕСТ 1: Создание пустого списка ===\n");
    LinkedList list = create_list(delete_func, copy_func, comp, default_constuctor);
    printf("size linkedlist = %ld\n", list.size);
    
    printf("\n=== ТЕСТ 2: Добавление в конец ===\n");
    push_back_list(&list, 1);
    push_back_list(&list, 2);
    push_back_list(&list, 3);
    print_list(&list);
    
    printf("\n=== ТЕСТ 3: Добавление в начало ===\n");
    push_front_list(&list, 10);
    push_front_list(&list, 20);
    print_list(&list);
    
    printf("\n=== ТЕСТ 4: Вставка по индексу ===\n");
    insert_at_list(&list, 1, 100);  // в середину
    insert_at_list(&list, 0, 500);  // в начало
    insert_at_list(&list, list.size, 999);  // в конец
    print_list(&list);
    
    printf("\n=== ТЕСТ 5: Получение элементов ===\n");
    printf("Элемент 0: %d\n", get_at_list(&list, 0));
    printf("Элемент 3: %d\n", get_at_list(&list, 3));
    printf("Последний элемент: %d\n", get_at_list(&list, list.size - 1));
    
    printf("\n=== ТЕСТ 6: Удаление с начала ===\n");
    pop_front_list(&list);
    print_list(&list);
    
    printf("\n=== ТЕСТ 7: Удаление с конца ===\n");
    pop_back_list(&list);
    print_list(&list);
    
    printf("\n=== ТЕСТ 8: Удаление по индексу ===\n");
    delete_at_list(&list, 2);  // из середины
    print_list(&list);
    delete_at_list(&list, 0);  // первый элемент
    print_list(&list);
    delete_at_list(&list, list.size - 1);  // последний элемент
    print_list(&list);
    
    printf("\n=== ТЕСТ 9: Работа с одним элементом ===\n");
    LinkedList single_list = create_list(delete_func, copy_func, comp, default_constuctor);
    push_back_list(&single_list, 42);
    printf("До удаления: ");
    print_list(&single_list);
    pop_back_list(&single_list);  // удаляем единственный элемент
    printf("После удаления: ");
    print_list(&single_list);
    
    printf("\n=== ТЕСТ 10: Сравнение списков ===\n");
    LinkedList list1 = create_list(delete_func, copy_func, comp, default_constuctor);
    LinkedList list2 = create_list(delete_func, copy_func, comp, default_constuctor);
    
    push_back_list(&list1, 1);
    push_back_list(&list1, 2);
    push_back_list(&list1, 3);
    
    push_back_list(&list2, 1);
    push_back_list(&list2, 2);
    push_back_list(&list2, 3);
    
    printf("Списки равны: %d\n", is_equal_list(&list1, &list2));
    
    push_back_list(&list2, 4);
    printf("После добавления - равны: %d\n", is_equal_list(&list1, &list2));
    
    printf("\n=== ТЕСТ 11: Очистка списка ===\n");
    printf("До очистки: ");
    print_list(&list1);
    erase_list(&list1);
    printf("После очистки: ");
    print_list(&list1);
    
    printf("\n=== ТЕСТ 12: Удаление из пустого списка ===\n");
    LinkedList empty_list = create_list(delete_func, copy_func, comp, default_constuctor);
    pop_front_list(&empty_list);  // не должно падать
    pop_back_list(&empty_list);   // не должно падать
    printf("Пустой список размер: %ld\n", empty_list.size);
    
    printf("\n=== ТЕСТ 13: Граничные случаи индексов ===\n");
    LinkedList edge_list = create_list(delete_func, copy_func, comp, default_constuctor);
    push_back_list(&edge_list, 1);
    push_back_list(&edge_list, 2);
    
    // Невалидные индексы - не должны падать
    get_at_list(&edge_list, 5);   // за пределами
    delete_at_list(&edge_list, 5); // за пределами
    insert_at_list(&edge_list, 5, 100); // за пределами
    
    printf("\n=== ФИНАЛЬНАЯ ОЧИСТКА ===\n");
    delete_list(&list);
    delete_list(&single_list);
    delete_list(&list1);
    delete_list(&list2);
    delete_list(&empty_list);
    delete_list(&edge_list);
    
    printf("Все тесты завершены!\n");
    return 0;
}