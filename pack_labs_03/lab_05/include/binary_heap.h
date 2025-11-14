#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H


#include <stdlib.h>

#define DEFINE_BINARY_MAX_HEAP(HEAP_TYPE) \
/* Максимальная бинарная куча */ \
typedef struct { \
    HEAP_TYPE *data; /* массив элементов */ \
    size_t size; /* текущее количество элементов */ \
    size_t capacity; /* вместимость */ \
    void (*delete_func)(HEAP_TYPE); /* деструктор */\
    HEAP_TYPE (*copy_func)(HEAP_TYPE); /* конструктор копирования */ \
    int (*comp)(HEAP_TYPE, HEAP_TYPE); /* компоратор */ \
    /* -1 - heap_1 < heap_2 */ \
    /* 0 - heap_1 == heap_2 */ \
    /* 1 - heap_1 > heap_2 */ \
    HEAP_TYPE (*default_constructor)(void); /* стандартный конструктор */ \
    void (*swap)(HEAP_TYPE*, HEAP_TYPE*); /* swap функция */ \
} Heap_##HEAP_TYPE; \
/* ----------------- БАЗОВЫЕ ОПЕРАЦИИ ----------------- */ \
/* Создание кучи с заданной начальной вместимостью */ \
inline static Heap_##HEAP_TYPE create_heap_##HEAP_TYPE(size_t initial_capacity, void (*delete_func)(HEAP_TYPE), HEAP_TYPE (*copy_func)(HEAP_TYPE),\
                        int (*comp)(HEAP_TYPE, HEAP_TYPE), HEAP_TYPE (*default_constructor)(void), void (*swap)(HEAP_TYPE*, HEAP_TYPE*)) { \
    Heap_##HEAP_TYPE heap; \
    heap.size = 0; \
    heap.capacity = initial_capacity; \
    heap.data = (HEAP_TYPE*)malloc(sizeof(HEAP_TYPE)*initial_capacity); \
    if (!heap.data) { \
        heap.data = NULL; \
        heap.capacity = 0; \
    }\
    heap.delete_func = delete_func; \
    heap.copy_func = copy_func; \
    heap.comp = comp; \
    heap.default_constructor = default_constructor; \
    heap.swap = swap; \
    return heap; \
} \
/* Проверка, пуста ли куча (1 — пуста, 0 — нет) */ \
inline static int is_empty_heap_##HEAP_TYPE(const Heap_##HEAP_TYPE *h) {\
    return h->size == 0; \
}\
/* Возврат текущего количества элементов */ \
inline static size_t size_heap_##HEAP_TYPE(const Heap_##HEAP_TYPE *h) { \
    return h->size;\
} \
/* Получение элемента с наивысшим приоритетом (минимального) без удаления */ \
inline static HEAP_TYPE peek_heap_##HEAP_TYPE(const Heap_##HEAP_TYPE *h) { \
    if (h->size == 0) { \
        return h->default_constructor();\
    } \
    return h->copy_func(h->data[0]);\
}\
/* Просеивание вниз */ \
inline static void sift_down_##HEAP_TYPE(Heap_##HEAP_TYPE *h, const size_t index) { \
    /* просеить вниз элемент, который находится по индексу index */ \
    if (index < 0 || index >= h->size) { \
        return; \
    } \
    size_t i = index; \
    while (i * 2 + 1 < h->size) { /* пока есть потомки */ \
        size_t left_child = i * 2 + 1; /* индекс левого ребенка */ \
        size_t right_child = i * 2 + 2; /* индекс правого ребенка */ \
        size_t biggest = i; /* здесь будет хранится индекс наибольшого ребенка */ \
        if (h->comp(h->data[biggest], h->data[left_child]) == -1) { /* сравниваем с левым потомком*/ \
            biggest = left_child; \
        } \
        if (right_child < h->size && h->comp(h->data[biggest], h->data[right_child]) == -1 ) { /* сравниваем с правым потомком*/ \
            biggest = right_child; \
        } \
        if (biggest == i) { /* значит структура кучи уже правильная (нашли место) */ \
            break; \
        } \
        h->swap(&h->data[biggest], &h->data[i]); /* просеиваем вниз */ \
        i = biggest; \
    } \
} \
/* Просеивание вверх */ \
inline static void sift_up_##HEAP_TYPE(Heap_##HEAP_TYPE *h, const size_t index) { \
    /* просеить вверх элемент, который находится по индексу index */ \
    /* если index == 0, то это корень, его просеивать наверх точно не надо */ \
    if (index <= 0 || index >= h->size) { \
        return; \
    } \
    size_t i = index; \
    size_t parent = (i - 1) / 2; \
    while (i > 0 && h->comp(h->data[i], h->data[parent]) == 1) { \
        /* пока потомок меньше чем родитель, проталкиваем вверх */ \
        h->swap(&(h->data[i]), &(h->data[parent])); \
        i = parent; \
        parent = (i - 1) / 2; \
    } \
} \
/* Добавление элемента в кучу */\
inline static void push_heap_##HEAP_TYPE(Heap_##HEAP_TYPE *h, HEAP_TYPE value) { \
    if (h->size + 1 == h->capacity) { \
        h->capacity = (h->capacity == 0 ? 1 : h->capacity * 2); \
        HEAP_TYPE *temp = (HEAP_TYPE*)realloc(h->data, sizeof(HEAP_TYPE) * h->capacity); \
        if (!temp) {  \
            h->capacity /= 2; \
            return; \
        } \
        h->data = temp;\
    }\
    h->data[h->size] = h->copy_func(value); \
    h->size++; \
    sift_up_##HEAP_TYPE(h, h->size - 1); \
} \
/* Удаление элемента с наивысшим приоритетом (минимального) и возврат его */ \
inline static HEAP_TYPE pop_heap_##HEAP_TYPE(Heap_##HEAP_TYPE *h) { \
    if (h->size == 0) { \
        return h->default_constructor(); \
    }\
    HEAP_TYPE pop_element = h->data[0]; \
    h->swap(&h->data[0], &h->data[h->size - 1]); /* меняем максимальный элемент с последним элементом в куче */ \
    h->size--; /* уменьшаем размер кучи */ \
    sift_down_##HEAP_TYPE(h, 0); /* просеиваем вниз */ \
    return h->copy_func(pop_element);\
} \
/* Построение кучи из массива */\
inline static Heap_##HEAP_TYPE build_heap_##HEAP_TYPE(const HEAP_TYPE *array, size_t n, \
                        void (*delete_func)(HEAP_TYPE), HEAP_TYPE (*copy_func)(const HEAP_TYPE),\
                        int (*comp)(HEAP_TYPE, HEAP_TYPE), HEAP_TYPE (*default_constructor)(void), \
                        void (*swap)(HEAP_TYPE*, HEAP_TYPE*)) { \
    size_t initial_capacity = (n == 0 ? 1 : n * 2); \
    Heap_##HEAP_TYPE heap = create_heap_##HEAP_TYPE(initial_capacity, delete_func, copy_func, comp, default_constructor, swap); \
    if (heap.capacity == 0) /* не получилось выделить память */ { \
        return heap; \
    } \
    /* Алгоритм Флойда */ \
    for (size_t i = 0; i < n; ++i) { \
        heap.data[i] = copy_func(array[i]); /* просто копируем исходный массив */ \
    } \
    heap.size = n; \
    if (n < 2) return heap; \
    size_t start_index = (n / 2) - 1; /* индекс первого нелистового элемента */ \
    for (size_t i = start_index; i >= 0; ) { \
        sift_down_##HEAP_TYPE(&heap, i); /* просеиваем снизу вверх */ \
        if (i == 0) break; \
        --i; \
    } \
    return heap; \
} \
/* Сравнение двух куч (лексикографически по массиву внутреннего представления) */ \
/* возвращает 1 — равны, 0 — не равны */\
inline static int is_equal_heap_##HEAP_TYPE(const Heap_##HEAP_TYPE *h1, const Heap_##HEAP_TYPE *h2) { \
    if (h1->size != h2->size) { \
        return 0; \
    } \
    for (size_t i = 0; i < h1->size; ++i) { \
        if (h1->comp(h1->data[i], h2->data[i]) != 0) { \
            return 0; \
        } \
    } \
    return 1; \
}\
/* Удаление кучи и освобождение памяти */\
inline static void delete_heap_##HEAP_TYPE(Heap_##HEAP_TYPE *h) { \
    for (size_t i = 0; i < h->size; ++i) { \
        HEAP_TYPE value = pop_heap_##HEAP_TYPE(h); \
        h->delete_func(value);\
    }\
    free(h->data); \
    h->capacity = 0; \
} \


#endif