#include "skew_heap_int.h"

#include <stdlib.h>
#include <stdbool.h>

// #define DEFINE_SKEW_MAX_HEAP(int) 


/* ----------------- БАЗОВЫЕ ОПЕРАЦИИ ----------------- */ 
SkewHeap_int create_skew_heap_int(void (*delete_func)(int), 
                        int (*comp)(int, int), int (*default_constructor)(void)) { 
    SkewHeap_int heap; 
    heap.root = NULL; 
    heap.size = 0; 
    heap.delete_func = delete_func; 
    heap.comp = comp; 
    heap.default_constructor = default_constructor; 
    return heap; 
}
void delete_node_skew_heap_int(Node_int *node, void (*delete_func)(int)) { 
    if (node == NULL) return ;
    delete_node_skew_heap_int(node->left, delete_func); 
    delete_node_skew_heap_int(node->right, delete_func); 
    delete_func(node->data); 
    free(node);    
} 
void delete_skew_heap_int(SkewHeap_int *heap) { 
    delete_node_skew_heap_int(heap->root, heap->delete_func); 
    free(heap->root); 
    heap->root = NULL; 
} 
bool is_empty_int(SkewHeap_int *heap) { 
    return heap->size == 0; 
} 
size_t size_heap_int(SkewHeap_int *heap) { 
    return heap->size; 
} 
Node_int* merge_skew_heap_int(Node_int *root_1, 
                    Node_int *root_2, int (*comp)(int, int)) { 
    if (root_1 == NULL) { 
        return root_2; 
    } 
    if (root_2 == NULL) { 
        return root_1; 
    } 
    /* слева всегда содержится большее */ 
    /* свапаем при необходимости */ 
    if (comp(root_2->data, root_1->data) == 1) { /* root_2->data > root_1->data */ 
        Node_int* temp = root_2; 
        root_2 = root_1; 
        root_1 = temp; 
    } 
    /* теперь слева содержится только большее число */ 
    /* значит нужно свапнуть левое и правое поддерево */ 
    Node_int *temp = root_1->right; 
    root_1->right = root_1->left; 
    root_1->left = temp; 
    /* теперь нужно рекурсиво смержить левое поддерево с root_2 */ 
    /* и поместить результат в наибольший из корней (очевидно это root_1) */ 
    root_1->left = merge_skew_heap_int(root_1->left, root_2, comp); 
    return root_1; 
} 
bool insert_skew_heap_int(SkewHeap_int *heap, int value) {
    Node_int * new_element = (Node_int*)malloc(sizeof(Node_int)); 
    if (new_element == NULL) { 
        return false; 
    } 
    new_element->data = value; 
    new_element->left = NULL; 
    new_element->right = NULL; 
    heap->root = merge_skew_heap_int(heap->root, new_element, heap->comp); 
    heap->size++; 
    return true; 
} 
void pop_skew_heap_int(SkewHeap_int *heap) { 
    if (heap->root == NULL) { 
        return; 
    } 
    Node_int* temp = heap->root;

    heap->root = merge_skew_heap_int(heap->root->left, heap->root->right, heap->comp); 
    heap->delete_func(temp->data); 
    free(temp); 
    heap->size--; 
} 
int peek_skew_heap_int(SkewHeap_int *heap) { 
    if (heap->root == NULL) { 
        return heap->default_constructor(); 
    } 
    return heap->root->data; 
} 
bool is_equal_node_skew_heap_int(Node_int *node_1, Node_int *node_2, int (*comp)(int, int)) { 
    if (node_1 == NULL && node_2 == NULL) { 
        return true; 
    } 
    if (node_1 == NULL || node_2 == NULL) { 
        return false; 
    } 
    if (comp(node_1->data, node_2->data) != 0) { 
        return false; 
    } 
    return is_equal_node_skew_heap_int(node_1->left, node_2->left, comp) && 
            is_equal_node_skew_heap_int(node_1->right, node_2->right, comp); 
} 
bool is_equal_skew_heap_int(SkewHeap_int *heap_1, SkewHeap_int *heap_2) { 
    return is_equal_node_skew_heap_int(heap_1->root, heap_2->root, heap_1->comp); 
} 
