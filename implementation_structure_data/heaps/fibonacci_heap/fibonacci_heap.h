#ifndef FIBONACCI_HEAP
#define FIBONACCI_HEAP

#include <stdbool.h>

typedef struct Node {
    int data; // данные
    int degree; // порядок текущего дерева

    struct Node *child; // указатель на сына
    struct Node *right_sibling; // указатель на правого брата
    struct Node *left_sibling; // указатель на левого брата
} Node;

typedef struct {
    int size; // колво элементов

    Node *min; // указатель на минимальный элемент

    Node *head; // указатель на начало односвязного списка, 
    // нужно для того чтобы начинать с самого левого элемента при перераспределении
} Fibonacci_heap;


Node* create_fibonacci_node(int data);
Fibonacci_heap create_fibonacci_heap();
bool push(Fibonacci_heap *heap, int data);
void merge(Node* node_1, Node* node_2);
bool pop(Fibonacci_heap *heap);
int peek(Fibonacci_heap *heap);
void free_heap(Fibonacci_heap *heap);
void free_node(Node* node);

#endif