#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define DEFINE_VECTOR(VECTOR_TYPE) \
typedef struct { \
    VECTOR_TYPE *data; /* указатель на элементы */ \
    size_t size; /* текущее количество элементов */ \
    size_t capacity; /* вместимость (количество выделенных элементов) */ \
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE); \
    void (*DeleteVoidPtr)(VECTOR_TYPE); \
    int (*Comp)(VECTOR_TYPE, VECTOR_TYPE); \
    VECTOR_TYPE (*DefaultConstructor)(void);\
} Vector_##VECTOR_TYPE; \
\
\
/* Создание нового вектора */ \
inline static Vector_##VECTOR_TYPE create_vector_##VECTOR_TYPE(size_t initial_capacity, VECTOR_TYPE(*CopyFunc)(VECTOR_TYPE), \
                                            void (*DeleteFunc)(VECTOR_TYPE), int (*Comp)(VECTOR_TYPE, VECTOR_TYPE), VECTOR_TYPE (*DefaultConstructor)(void)) { \
    Vector_##VECTOR_TYPE vector; \
    vector.size = 0; \
    vector.capacity = initial_capacity; \
    vector.data = (VECTOR_TYPE*)malloc(sizeof(VECTOR_TYPE)*vector.capacity); \
    if (!vector.data) { \
        vector.data = NULL; \
        vector.size = 0; \
        vector.capacity = 0;\
    } \
    vector.CopyVoidPtr = CopyFunc; \
    vector.DeleteVoidPtr = DeleteFunc; \
    vector.Comp = Comp; \
    vector.DefaultConstructor = DefaultConstructor; \
    return vector; \
} \
/* Удаление внутреннего содержимого вектора (data, size=0, capacity=0) */ \
inline static void erase_vector_##VECTOR_TYPE(Vector_##VECTOR_TYPE *v) { \
    for (size_t i = 0; i < v->size; ++i) { \
        v->DeleteVoidPtr(v->data[i]); \
    } \
    v->size = 0;\
    v->capacity = 0;\
} \
/* Сравнение двух векторов (лексикографически) */ \
/* возвращает 1 — равны, 0 — не равны */ \
inline static int is_equal_vector_##VECTOR_TYPE(const Vector_##VECTOR_TYPE *v1, const Vector_##VECTOR_TYPE *v2) { \
    if (v1->size != v2->size) { \
        return 0; \
    } \
    for (size_t i = 0; i < v1->size; ++i) { \
        if (v1->Comp(v1->data[i], v2->data[i]) != 0) { \
            return 0; \
        }\
    }\
    return 1;\
}\
/* Копирование содержимого одного вектора в другой (существующий) */ \
inline static void copy_vector_##VECTOR_TYPE(Vector_##VECTOR_TYPE *dest, const Vector_##VECTOR_TYPE *src) {\
    if (dest->capacity < src->capacity) { \
        VECTOR_TYPE* temp = (VECTOR_TYPE*)realloc(dest->data, sizeof(VECTOR_TYPE) * src->capacity); \
        if (!temp) { \
            return; \
        } \
        dest->data = temp; \
    } \
    for (size_t i = 0; i < src->size; ++i) { \
        /* если VECTOR_TYPE слонжый тип, то если мы просто перезапишем v->data[index]*/ \
        /* то получится что у нас останется выделенная память, а указатель на нее сотрется*/ \
        dest->DeleteVoidPtr(dest->data[i]); \
        dest->data[i] = dest->CopyVoidPtr(src->data[i]); \
    }\
    for (size_t i = src->size; i < dest->size; ++i) {\
        /* если VECTOR_TYPE сложный тип */ \
        /* и src->size < dest->size, то тогда получается утечка*/ \
        dest->DeleteVoidPtr(dest->data[i]);\
    }\
    dest->CopyVoidPtr = src->CopyVoidPtr; \
    dest->DeleteVoidPtr = src->DeleteVoidPtr; \
    dest->capacity = src->capacity;\
    dest->size = src->size;\
}\
/* Создание нового вектора в динамической памяти и копирование содержимого */ \
inline static Vector_##VECTOR_TYPE *copy_vector_new_##VECTOR_TYPE(const Vector_##VECTOR_TYPE *src) {\
    Vector_##VECTOR_TYPE *dest = (Vector_##VECTOR_TYPE*)malloc(sizeof(Vector_##VECTOR_TYPE)); \
    if (!dest) { \
        return NULL; \
    } \
    dest->data = (VECTOR_TYPE*)malloc(sizeof(VECTOR_TYPE) * src->capacity); \
    if (!dest->data) {\
        free(dest); \
        return NULL; \
    } \
    for (size_t i = 0; i < src->size; ++i) {\
        dest->data[i] = src->data[i]; \
    }\
    dest->CopyVoidPtr = src->CopyVoidPtr; \
    dest->DeleteVoidPtr = src->DeleteVoidPtr; \
    dest->capacity = src->capacity;\
    dest->size = src->size; \
    return dest; \
}\
/* Добавление элемента в конец вектора */ \
inline static void push_back_vector_##VECTOR_TYPE(Vector_##VECTOR_TYPE *v, VECTOR_TYPE value) { \
    if (v->size == v->capacity) {\
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;\
        VECTOR_TYPE *temp = (VECTOR_TYPE*)realloc(v->data, sizeof(VECTOR_TYPE) * v->capacity);\
        if (!temp) {\
            return;\
        }\
        v->data = temp; \
    } \
    v->data[v->size++] = value;\
}\
/* Удаление элемента по индексу */ \
inline static void delete_at_vector_##VECTOR_TYPE(Vector_##VECTOR_TYPE *v, size_t index) { \
    if (index < 0 || index >= v->size) { \
        return; \
    } \
    for (size_t i = index; i < v->size - 1; ++i) { \
        v->data[i] = v->data[i + 1];\
    }\
    --v->size;\
} \
/* Получение элемента по индексу */ \
inline static VECTOR_TYPE get_at_vector_##VECTOR_TYPE(const Vector_##VECTOR_TYPE *v, size_t index) { \
    if (index < 0 || index >= v->size) { \
        return v->DefaultConstructor(); \
    } \
    return v->data[index]; \
} \
/* Освобождение памяти, занимаемой экземпляром вектора void */ \
inline static void delete_vector_##VECTOR_TYPE(Vector_##VECTOR_TYPE *v) { \
    erase_vector_##VECTOR_TYPE(v); \
    free(v->data); \
}

#endif