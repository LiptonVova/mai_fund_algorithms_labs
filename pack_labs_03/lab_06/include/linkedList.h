#ifndef LINKED_LIST_H
#define LINKED_LIST_H


#include <stdlib.h>


#define DEFINE_LIST_STACK(LIST_TYPE) \
typedef struct Node { \
    LIST_TYPE data; \
    struct Node *prev; \
    struct Node *next; \
} Node; \
/* Двусвязный список */ \
typedef struct { \
    Node *head; \
    Node *tail; \
    size_t size; \
    void (*DeleteVoidPtr)(LIST_TYPE); \
    LIST_TYPE (*CopyVoidPtr)(LIST_TYPE); \
    int (*Comporator)(LIST_TYPE, LIST_TYPE); \
} LinkedList; \
/* ----------------- БАЗОВЫЕ ОПЕРАЦИИ ---------------- */ \
/* Создание пустого списка */ \
LinkedList create_list(void (*delete_func)(LIST_TYPE), LIST_TYPE (*copy_func)(LIST_TYPE), int (*comp)(LIST_TYPE, LIST_TYPE)) { \
    LinkedList list; \
    list.head = NULL; \
    list.tail = NULL; \
    list.size = 0; \
    list.DeleteVoidPtr = delete_func; \
    list.CopyVoidPtr = copy_func; \
    list.Comporator = comp; \
    return list; \
} \
/* Добавление элемента в конец списка */ \
void push_back_list(LinkedList *list, LIST_TYPE value) { \
    Node* new_node = (Node*)malloc(sizeof(Node)); \
    if (!new_node) return; \
    new_node->data = list->CopyVoidPtr(value); \
    /* добавили в конец, значит new_node становится tail */ \
    /* нет следующего элемента, зато есть предыдущий */ \
    new_node->next = NULL; \
    new_node->prev = list->tail; /* проверять на NULL нет необходимости, */ \
    /* ведь в случае list->tail == NULL, то new_node->prev должен стать NULL */ \
    \
    if (list->tail) list->tail->next = new_node; \
    \
    list->size++; \
    list->tail = new_node; /* теперь новый конец списка */ \
    if (!list->head) list->head = new_node; /* если список был пустой, то head == tail == new_node */ \
} \
/* Добавление элемента в начало списка */ \
void push_front_list(LinkedList *list, LIST_TYPE value) { \
    Node* new_node = (Node*)malloc(sizeof(Node)); \
    if (!new_node) return; \
    new_node->data = list->CopyVoidPtr(value); \
    /* добавляем в начало, значит new_node становится новый head */ \
    new_node->prev = NULL; \
    new_node->next = list->head;  /* проверять на NULL нет необходимости, */ \
    /* ведь в случае list->head == NULL, то new_node->next должен стать NULL */ \
    \
    if (list->head) list->head->prev = new_node; \
    \
    list->size++; \
    list->head = new_node; /* теперь новое начало списка */ \
    if (!list->tail) list->tail = new_node; /* если список был пустой, то head == tail == new_node */ \
} \
/* Удаление элемента с конца списка */ \
void pop_back_list(LinkedList *list) { \
    if (list->size == 0) return ; /* если список пустой, то ничего не делать */ \
    list->size--; \
    Node* delete_node = list->tail; /* сохранить указатель на удаляемый элемент */ \
    list->tail = list->tail->prev; /* новый последний элемент */ \
    /* проверка на if (list->tail) нужна, если у нас один элемент в списке */ \
    if (list->tail) { \
        list->tail->next = NULL; /* обнуляем указатель у нового конца списка */ \
    }\
    else { /* тогда список состоял из одного элемента */ \
        list->head = NULL; \
    } \
    list->DeleteVoidPtr(delete_node->data); \
    free(delete_node); \
} \
/*Удаление элемента с начала списка */ \
void pop_front_list(LinkedList *list) { \
    if (list->size == 0) return ; /* если список пустой, то ничего не делать */ \
    list->size--; \
    Node* delete_node = list->head; /* сохранить указатель на удаляемый элемент */ \
    list->head = list->head->next; /* новый последний элемент */ \
    /* проверка на if (list->head) нужна, если у нас один элемент в списке */ \
    if (list->head) { \
        list->head->prev = NULL; /* обнуляем указатель у нового начала списка */ \
    } \
    else { /* тогда список состоял из одного элемента */ \
        list->tail = NULL; \
    } \
    list->DeleteVoidPtr(delete_node->data); \
    free(delete_node); \
} \
/* Вставка элемента по индексу */ \
void insert_at_list(LinkedList *list, size_t index, LIST_TYPE value) { \
    if (index < 0 || index > list->size) return; \
    if (index == list->size) { \
        push_back_list(list, value); /* пытаемся добавить в самый конец */ \
        return; \
    } \
    Node* node_index = list->head; /* узел, который до вставки находится по индексу index */ \
    for (size_t i = 0; i < index; ++i) { \
        node_index = node_index->next; \
    } \
    Node* new_node = (Node*)malloc(sizeof(Node)); \
    if (!new_node) return; \
    new_node->data = list->CopyVoidPtr(value); \
    new_node->next = node_index; \
    new_node->prev = node_index->prev; \
    \
    if (node_index->prev) { \
        node_index->prev->next = new_node; \
    } \
    else { /* тогда мы вставили на место head */ \
        list->head = new_node; \
    } \
    node_index->prev = new_node; \
    \
    list->size++; \
} \
/* Удаление элемента по индексу */ \
void delete_at_list(LinkedList *list, size_t index) { \
    if (index < 0 || index >= list->size) return; \
    Node * delete_node = list->head; \
    for (size_t i = 0; i < index; ++i) { \
        delete_node = delete_node->next; \
    } \
    if (delete_node->prev) { \
        delete_node->prev->next = delete_node->next; \
    } \
    else { /* значит мы удаляем head */ \
        list->head = delete_node->next; \
    } \
    if (delete_node->next) { \
        delete_node->next->prev = delete_node->prev; \
    } \
    else { /* значит мы удалили tail */ \
        list->tail = delete_node->prev; \
    } \
    list->size--; \
    list->DeleteVoidPtr(delete_node->data); \
    free(delete_node); \
} \
/* Получение элемента по индексу */ \
LIST_TYPE get_at_list(const LinkedList *list, size_t index) { \
    if (index < 0 || index >= list->size) return (LIST_TYPE)0; \
    Node * cur_node = list->head; \
    for (size_t i = 0; i < index; ++i) { \
        cur_node = cur_node->next; \
    } \
    return cur_node->data; \
} \
/* Сравнение двух списков (лексикографически) */ \
/* возвращает 1 — равны, 0 — не равны */ \
int is_equal_list(const LinkedList *l1, const LinkedList *l2) { \
    if (l1->size != l2->size) return 0; \
    Node * node_1 = l1->head; \
    Node * node_2 = l2->head; \
    for (size_t i = 0; i < l1->size; ++i) { \
        if (!l1->Comporator(node_1->data, node_2->data)) { \
            return 0; \
        } \
        node_1 = node_1->next; \
        node_2 = node_2->next; \
    } \
    return 1; \
} \
/* Очистка содержимого списка (удаление всех элементов) */ \
void erase_list(LinkedList *list) { \
    while (list->head != NULL) { \
        pop_front_list(list); /* удаляем все элементы */ \
    } \
} \
/* Полное удаление списка (освобождение ресурсов) */ \
void delete_list(LinkedList *list) { \
    while (list->head != NULL) { \
        pop_front_list(list); /* удалили из списка первый элемент */ \
        /* pop_front_list сам освобождает память */ \
    } \
} \
/* ----------------- СТЕК ----------------- */ \
/* Поместить элемент на вершину стека */ \
void push_stack(LinkedList *stack, LIST_TYPE value) { \
    push_back_list(stack, value); \
} \
/* Извлечь элемент с вершины стека */ \
void pop_stack(LinkedList *stack) { \
    pop_back_list(stack); \
} \
/* Получить элемент с вершины стека без удаления */ \
LIST_TYPE peek_stack(const LinkedList *stack) { \
    if (stack->size > 0) { \
        return stack->tail->data; \
    } \
    return (LIST_TYPE)0; \
} \
/* ---------------- ОЧЕРЕДЬ ----------------- */ \
/* Добавить элемент в очередь */ \
void enqueue(LinkedList *queue, LIST_TYPE value) { \
    push_front_list(queue, value); \
} \
/* Извлечь элемент из очереди */ \
void dequeue(LinkedList *queue) { \
    pop_back_list(queue); \
} \
/* Получить первый элемент очереди без удаления */ \
LIST_TYPE peek_queue(const LinkedList *queue) { \
    if (queue->size > 0) { \
        return queue->head->data; \
    } \
    return (LIST_TYPE)0; \
} 

#endif