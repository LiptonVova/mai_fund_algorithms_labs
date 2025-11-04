#include "include/binary_heap.h"

#include <string.h>
#include <stdio.h>

void delete_double(double value) {
}

double copy_double(double value) {
    return value;
}

int comp_double(double value_1, double value_2) {    
    if (value_1 < value_2) return -1;
    if (value_1 > value_2) return 1;
    return 0;
}

double default_double() {
    return 0.0;
}

void swap_double(double *value_1, double *value_2) {
    double temp = *value_1;
    *value_1 = *value_2;
    *value_2 = temp;
}

DEFINE_BINARY_MIN_HEAP(double)

int main() {
    printf("\n=== ДЕМОНСТРАЦИЯ ДЛЯ double ===\n");
    
    // Создание пустой кучи
    Heap_double heap = create_heap_double(5, delete_double, copy_double, comp_double, default_double, swap_double);
    printf("Создана пустая куча. Размер: %zu\n", size_heap_double(&heap));
    
    // Добавление элементов
    printf("\nДобавляем элементы: 5.5, 2.2, 8.8, 1.1, 10.10\n");
    push_heap_double(&heap, 5.5);
    push_heap_double(&heap, 2.2);
    push_heap_double(&heap, 8.8);
    push_heap_double(&heap, 1.1);
    push_heap_double(&heap, 10.10);
    
    printf("Размер кучи после добавления: %zu\n", size_heap_double(&heap));
    printf("Минимальный элемент: %.2f\n", peek_heap_double(&heap));
    
    // Извлечение элементов в отсортированном порядке
    printf("\nИзвлекаем элементы в порядке приоритета:\n");
    while (!is_empty_heap_double(&heap)) {
        printf("%.2f ", pop_heap_double(&heap));
    }
    printf("\n");
    
    // Построение кучи из массива
    printf("\nСтроим кучу из массива [6.6, 1.1, 2.2, 7.7, 6.1, 3.3]:\n");
    double array[] = {6.6, 1.1, 2.2, 7.7, 6.1, 3.3};
    Heap_double heap2 = build_heap_double(array, 6, delete_double, copy_double, comp_double, default_double, swap_double);
    
    printf("Извлекаем элементы:\n");
    while (!is_empty_heap_double(&heap2)) {
        printf("%.2f ", pop_heap_double(&heap2));
    }
    printf("\n");
    
    delete_heap_double(&heap);
    delete_heap_double(&heap2);

    return 0;
}