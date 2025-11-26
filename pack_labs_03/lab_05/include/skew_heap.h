#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H


#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_SKEW_MAX_HEAP(HEAP_TYPE) \
/* Максимальная косая куча */ \
typedef struct Node_##HEAP_TYPE { \
    HEAP_TYPE data; \
    struct Node_##HEAP_TYPE *left; \
    struct Node_##HEAP_TYPE *right; \
} Node_##HEAP_TYPE; \
typedef struct { \
    Node_##HEAP_TYPE *root; /* указатель на корень */ \
    size_t size; /* колво элементов */ \
    void (*delete_func)(HEAP_TYPE); /* деструктор */\
    int (*comp)(HEAP_TYPE, HEAP_TYPE); /* компоратор */ \
    /* -1 - heap_1 < heap_2 */ \
    /* 0 - heap_1 == heap_2 */ \
    /* 1 - heap_1 > heap_2 */ \
    HEAP_TYPE (*default_constructor)(void); /* стандартный конструктор */ \
} SkewHeap_##HEAP_TYPE; \
/* ----------------- БАЗОВЫЕ ОПЕРАЦИИ ----------------- */ \
inline static SkewHeap_##HEAP_TYPE create_skew_heap_##HEAP_TYPE(void (*delete_func)(HEAP_TYPE), \
                        int (*comp)(HEAP_TYPE, HEAP_TYPE), HEAP_TYPE (*default_constructor)(void)) { \
    SkewHeap_##HEAP_TYPE heap; \
    heap.root = NULL; \
    heap.size = 0; \
    heap.delete_func = delete_func; \
    heap.comp = comp; \
    heap.default_constructor = default_constructor; \
    return heap; \
}\
inline static void delete_node_skew_heap_##HEAP_TYPE(Node_##HEAP_TYPE *node, void (*delete_func)(HEAP_TYPE)) { \
    if (node == NULL) return ;\
    delete_node_skew_heap_##HEAP_TYPE(node->left, delete_func); \
    delete_node_skew_heap_##HEAP_TYPE(node->right, delete_func); \
    /* delete_func(node->data); */ \
    free(node);    \
} \
inline static void delete_skew_heap_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap) { \
    delete_node_skew_heap_##HEAP_TYPE(heap->root, heap->delete_func); \
    heap->root = NULL; \
} \
inline static bool is_empty_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap) { \
    return heap->size == 0; \
} \
inline static size_t size_heap_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap) { \
    return heap->size; \
} \
inline static Node_##HEAP_TYPE* merge_skew_heap_##HEAP_TYPE(Node_##HEAP_TYPE *root_1, \
                    Node_##HEAP_TYPE *root_2, int (*comp)(HEAP_TYPE, HEAP_TYPE)) { \
    if (root_1 == NULL) { \
        return root_2; \
    } \
    if (root_2 == NULL) { \
        return root_1; \
    } \
    /* слева всегда содержится большее */ \
    /* свапаем при необходимости */ \
    if (comp(root_2->data, root_1->data) == 1) { /* root_2->data > root_1->data */ \
        Node_##HEAP_TYPE* temp = root_2; \
        root_2 = root_1; \
        root_1 = temp; \
    } \
    /* теперь слева содержится только большее число */ \
    /* значит нужно свапнуть левое и правое поддерево */ \
    Node_##HEAP_TYPE *temp = root_1->right; \
    root_1->right = root_1->left; \
    root_1->left = temp; \
    /* теперь нужно рекурсиво смержить левое поддерево с root_2 */ \
    /* и поместить результат в наибольший из корней (очевидно это root_1) */ \
    root_1->left = merge_skew_heap_##HEAP_TYPE(root_1->left, root_2, comp); \
    return root_1; \
} \
inline static bool insert_skew_heap_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap, HEAP_TYPE value) {\
    Node_##HEAP_TYPE * new_element = (Node_##HEAP_TYPE*)malloc(sizeof(Node_##HEAP_TYPE)); \
    if (new_element == NULL) { \
        return false; \
    } \
    new_element->data = value; \
    new_element->left = NULL; \
    new_element->right = NULL; \
    heap->root = merge_skew_heap_##HEAP_TYPE(heap->root, new_element, heap->comp); \
    heap->size++; \
    return true; \
} \
inline static void pop_skew_heap_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap) { \
    if (heap->root == NULL) { \
        return; \
    } \
    Node_##HEAP_TYPE *temp = heap->root;\
    heap->root = merge_skew_heap_##HEAP_TYPE(heap->root->left, heap->root->right, heap->comp); \
    /* heap->delete_func(temp->data); */ \
    free(temp); \
    heap->size--; \
} \
inline static HEAP_TYPE peek_skew_heap_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap) { \
    if (heap->root == NULL) { \
        return heap->default_constructor(); \
    } \
    return heap->root->data; \
} \
inline static bool is_equal_node_skew_heap_##HEAP_TYPE(Node_##HEAP_TYPE *node_1, Node_##HEAP_TYPE *node_2, int (*comp)(HEAP_TYPE, HEAP_TYPE)) { \
    if (node_1 == NULL && node_2 == NULL) { \
        return true; \
    } \
    if (node_1 == NULL || node_2 == NULL) { \
        return false; \
    } \
    if (comp(node_1->data, node_2->data) != 0) { \
        return false; \
    } \
    return is_equal_node_skew_heap_##HEAP_TYPE(node_1->left, node_2->left, comp) && \
            is_equal_node_skew_heap_##HEAP_TYPE(node_1->right, node_2->right, comp); \
} \
inline static bool is_equal_skew_heap_##HEAP_TYPE(SkewHeap_##HEAP_TYPE *heap_1, SkewHeap_##HEAP_TYPE *heap_2) { \
    return is_equal_node_skew_heap_##HEAP_TYPE(heap_1->root, heap_2->root, heap_1->comp); \
} \

#endif