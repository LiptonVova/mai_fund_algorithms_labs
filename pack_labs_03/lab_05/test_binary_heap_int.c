#include <stdio.h>

#include "include/binary_heap.h"


DEFINE_BINARY_MAX_HEAP(int)

void delete_int(int value) {

}

int copy_int(const int value) {
    return value;
}

int comp_int(int value_1, int value_2) {    
    if (value_1 < value_2) return -1;
    if (value_1 > value_2) return 1;
    return 0;
}

int default_int() {
    return 0;
}

void swap_int(int *value_1, int *value_2) {
    int temp = *value_1;
    *value_1 = *value_2;
    *value_2 = temp;
}


int main() {
    printf("=== ДЕМОНСТРАЦИЯ ДЛЯ int ===\n");
    
    // Создание пустой кучи
    Heap_int heap = create_heap_int(5, delete_int, copy_int, comp_int, default_int, swap_int);
    printf("Создана пустая куча. Размер: %zu\n", size_heap_int(&heap));
    
    // Добавление элементов
    printf("\nДобавляем элементы: 5, 2, 8, 1, 1, 1, 1, 10\n");
    push_heap_int(&heap, 5);
    push_heap_int(&heap, 2);
    push_heap_int(&heap, 8);
    push_heap_int(&heap, 1);
    push_heap_int(&heap, 1);
    push_heap_int(&heap, 1);
    push_heap_int(&heap, 1);
    push_heap_int(&heap, 10);
    
    printf("Размер кучи после добавления: %zu\n", size_heap_int(&heap));
    printf("Минимальный элемент: %d\n", peek_heap_int(&heap));
    
    // Извлечение элементов в отсортированном порядке
    printf("\nИзвлекаем элементы в порядке приоритета:\n");
    while (!is_empty_heap_int(&heap)) {
        printf("%d ", pop_heap_int(&heap));
    }
    printf("\n");
    
    // Построение кучи из массива
    printf("\nСтроим кучу из массива [6, 1, 2, 7, 6, 3]:\n");
    int array[] = {6, 1, 2, 7, 6, 3};
    Heap_int heap2 = build_heap_int(array, 6, delete_int, copy_int, comp_int, default_int, swap_int);
    
    printf("Извлекаем элементы:\n");
    while (!is_empty_heap_int(&heap2)) {
        printf("%d ", pop_heap_int(&heap2));
    }
    printf("\n");
    
    delete_heap_int(&heap);
    delete_heap_int(&heap2);
    return 0;
}