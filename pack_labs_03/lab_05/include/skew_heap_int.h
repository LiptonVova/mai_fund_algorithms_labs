#ifndef SKEW_HEAP_INT_H
#define SKEW_HEAP_INT_H

#include <stdlib.h>
#include <stdbool.h>

/* Максимальная косая куча */ 
typedef struct Node_int { 
    int data; 
    struct Node_int *left; 
    struct Node_int *right; 
} Node_int; 
typedef struct { 
    Node_int *root; /* указатель на корень */ 
    size_t size; /* колво элементов */ 
    void (*delete_func)(int); /* деструктор */
    int (*comp)(int, int); /* компоратор */ 
    /* -1 - heap_1 < heap_2 */ 
    /* 0 - heap_1 == heap_2 */ 
    /* 1 - heap_1 > heap_2 */ 
    int (*default_constructor)(void); /* стандартный конструктор */ 
} SkewHeap_int; 

SkewHeap_int create_skew_heap_int(void (*delete_func)(int), 
                        int (*comp)(int, int), int (*default_constructor)(void));;
                    
void delete_node_skew_heap_int(Node_int *node, void (*delete_func)(int));
void delete_skew_heap_int(SkewHeap_int *heap);
bool is_empty_int(SkewHeap_int *heap);
size_t size_heap_int(SkewHeap_int *heap);

Node_int* merge_skew_heap_int(Node_int *root_1, 
                    Node_int *root_2, int (*comp)(int, int));
bool insert_skew_heap_int(SkewHeap_int *heap, int value);
void pop_skew_heap_int(SkewHeap_int *heap);
int peek_skew_heap_int(SkewHeap_int *heap) ;
bool is_equal_node_skew_heap_int(Node_int *node_1, Node_int *node_2, int (*comp)(int, int));
bool is_equal_skew_heap_int(SkewHeap_int *heap_1, SkewHeap_int *heap_2) ;




#endif