#include <stdio.h>
#include <stdlib.h>
#include "include/skew_heap.h"
// #include "include/skew_heap_int.c"

typedef struct {
    int a;
    int b;
} Custom;

DEFINE_SKEW_MAX_HEAP(int)

typedef Custom* CustomPtr;

DEFINE_SKEW_MAX_HEAP(CustomPtr)

void delete_func_custom(CustomPtr value) {
    free(value);
}

int comp_custom(CustomPtr value_1, CustomPtr value_2) {
    if (value_1->a > value_2->a) return 1;
    if (value_1->a < value_2->a) return -1;
    return 0;
}

CustomPtr default_constructor_custom() {
    Custom* default_с = (Custom*)malloc(sizeof(Custom));
    if (default_с == NULL) {
        return NULL;
    }
    default_с->a = 0;
    default_с->b = 0;
    return default_с;
}

void delete_func(int ) {

}

int comp(int a, int b) {
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

int default_constructor() {
    return 0;
}

int main() {
    SkewHeap_int skew_heap_int = create_skew_heap_int(delete_func, comp, default_constructor);
    insert_skew_heap_int(&skew_heap_int, 1);
    insert_skew_heap_int(&skew_heap_int, -1);
    insert_skew_heap_int(&skew_heap_int, 15);

    printf("first element: %d\n", peek_skew_heap_int(&skew_heap_int));

    pop_skew_heap_int(&skew_heap_int);
    
    printf("second element: %d\n", peek_skew_heap_int(&skew_heap_int));

    pop_skew_heap_int(&skew_heap_int);
    printf("third element: %d\n", peek_skew_heap_int(&skew_heap_int));
    
    printf("size: %ld\n", size_heap_int(&skew_heap_int));

    delete_skew_heap_int(&skew_heap_int);

    printf("кастомная структура\n\n");

    SkewHeap_CustomPtr skew_heap_custom = create_skew_heap_CustomPtr(delete_func_custom, comp_custom, default_constructor_custom);

    Custom* custom_1 = (Custom*)malloc(sizeof(Custom));
    Custom* custom_2 = (Custom*)malloc(sizeof(Custom));
    Custom* custom_3 = (Custom*)malloc(sizeof(Custom));

    custom_1->a = 1;
    custom_1->b = 2;
    custom_2->a = 0;
    custom_2->b = 2;
    custom_3->a = 5;
    custom_3->b = 2;

    insert_skew_heap_CustomPtr(&skew_heap_custom, custom_1);
    insert_skew_heap_CustomPtr(&skew_heap_custom, custom_2);
    insert_skew_heap_CustomPtr(&skew_heap_custom, custom_3);

    
    Custom* temp = peek_skew_heap_CustomPtr(&skew_heap_custom);
    printf("first element: a = %d, b = %d\n", temp->a, temp->b);

    pop_skew_heap_CustomPtr(&skew_heap_custom);
    
    temp = peek_skew_heap_CustomPtr(&skew_heap_custom);
    printf("second element: a = %d, b = %d\n", temp->a, temp->b);

    pop_skew_heap_CustomPtr(&skew_heap_custom);
    temp = peek_skew_heap_CustomPtr(&skew_heap_custom);
    printf("third element: a = %d, b = %d\n", temp->a, temp->b);
    
    printf("size: %ld\n", size_heap_CustomPtr(&skew_heap_custom));

    delete_skew_heap_CustomPtr(&skew_heap_custom);


    return 0;
}