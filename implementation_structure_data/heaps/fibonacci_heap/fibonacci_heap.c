#include "fibonacci_heap.h"

#include <stdlib.h>


Node* create_fibonacci_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    } 

    node->data = data;
    node->degree = 0; // пока что состоим из одного элемента (2**0 = 1)
    node->child = NULL;
    node->right_sibling = NULL;
    node->left_sibling = NULL;

    return node;
}

Fibonacci_heap create_fibonacci_heap() {
    Fibonacci_heap heap;
    heap.size = 0;
    heap.min = NULL;
    heap.head = NULL;
    
    return heap;
}

bool push(Fibonacci_heap *heap, int data) {
    // bool - возвращаем 
    // true - если успешно
    // false - если произошли ошибки (выделения памяти) 

    // лениво добавляем элементы
    // единственное, что надо проверить, если добавляемый элемент 
    // будет приоритетнее, чем прошлый

    Node* new_node = create_fibonacci_node(data);
    if (!new_node) return false;
    
    if (!heap->min) {
        // частный случай 
        // если куча пустая

        heap->min = new_node;
        heap->head = new_node;
    }

    // если куча не пустая
    else {
        new_node->right_sibling = heap->head;
        heap->head->left_sibling = new_node;
        heap->head = new_node;
    }


    if (data < heap->min->data) {
        // новый элемент приоритетнее чем старый
        heap->min = new_node;        
    }

    heap->size++;
    return true;
}

void merge(Node* node_1, Node* node_2) {
    // функция, которая мержит два дерева
    // результат всегда хранится в node_1!
    if (node_1->data > node_2->data) {
        // слева всегда приоритетнее
        Node* temp = node_2;
        node_2 = node_1;
        node_1 = temp; 
    }

    Node* left_sibling_node_2 = node_2->left_sibling;
    Node* right_sibling_node_2 = node_2->right_sibling;

    if (left_sibling_node_2) left_sibling_node_2->right_sibling = right_sibling_node_2;
    if (right_sibling_node_2) right_sibling_node_2->left_sibling = left_sibling_node_2; 

    node_2->right_sibling = node_1->child;
    node_2->left_sibling = NULL;
    node_1->child = node_2;

    int max_degree = node_1->degree;
    if (node_2->degree > node_1->degree) {
        max_degree = node_2->degree;
    }
    node_1->degree = ++max_degree;
}

bool pop(Fibonacci_heap *heap) {
    // проверяем частный случай - куча пуста
    if (!heap->min) return false;

    
    Node *pop_node = heap->min;
    Node *child_pop_node = pop_node->child;
    
    if (pop_node == heap->head) {
        heap->head = heap->head->right_sibling;
    }
    heap->min = heap->head;

    Node *next_elem = pop_node->child;

    Node* left = pop_node->left_sibling;
    Node* right = pop_node->right_sibling;

    if (left) left->right_sibling = right;
    if (right) right->left_sibling = left;

    free(pop_node);

    int ARRAY_SIZE = 1; 
    Node** array = (Node**)malloc(sizeof(Node*) * ARRAY_SIZE);
    if (!array) return false;

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = NULL;
    }

    while (next_elem && next_elem->right_sibling) {
        // получаем самый правый элемент
        next_elem = next_elem->right_sibling;
    }

    if (next_elem) {
        // подвесили всех детей нашего удаляемого узла
        // к основному списку
        next_elem->right_sibling = heap->head;
        heap->head->left_sibling = next_elem;
        heap->head = child_pop_node;
    }

    // теперь проходимся по всему основному списку и заполняем array
    // при необходимости мержим
    next_elem = heap->head;
    while (next_elem) {
        if (next_elem->data < heap->min->data) {
            heap->min = next_elem;
        }

        int degree = next_elem->degree;

        if (degree >= ARRAY_SIZE) {
            const int OLD_ARRAY_SIZE = ARRAY_SIZE;
            ARRAY_SIZE *= 2;
            Node ** temp = (Node**)realloc(array, sizeof(Node*) * ARRAY_SIZE);
            if (!temp) {
                free(array);
                return false;
            }
            array = temp;

            for (int i = OLD_ARRAY_SIZE; i < ARRAY_SIZE; ++i) {
                array[i] = NULL;
            }
        }

        if (array[degree] && array[degree] != next_elem) {
            // есть два дерева с одинаковым порядком - нужно их смержить

            merge(next_elem, array[degree]);
            
            // здесь важно не потерять указатель на head
            if (next_elem == heap->head || array[degree] == heap->head) {
                // если хотя бы какой то узел являлся головой основного списка, 
                // то тогда его надо сохранить!
                heap->head = next_elem;
            }

            array[degree] = NULL;
        }
        else {
            array[degree] = next_elem;
            next_elem = next_elem->right_sibling;
        }
    }

    free(array);

    heap->size--;
    return true;  
}

int peek(Fibonacci_heap *heap) {
    return heap->min->data;
}

void free_node(Node* node) {
    // очистка памяти, которая занимает нода
    if (!node) return;

    free_node(node->child);
    free_node(node->right_sibling);
    free(node);
}

void free_heap(Fibonacci_heap *heap) {
    free_node(heap->head);
    heap->size = 0;
}