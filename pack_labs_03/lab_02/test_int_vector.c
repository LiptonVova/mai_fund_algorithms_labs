#include <stdio.h>
#include "include/vector.h"

int copy_int(int value) {
    return value;
}

void delete_int(int value) {

    (void)value;
}

DEFINE_VECTOR(int)

int main() {
    printf("=== Testing Int Vector ===\n");
    

    Vector v = create_vector(2, copy_int, delete_int);
    printf("Vector created: size=%zu, capacity=%zu\n", v.size, v.capacity);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    printf("After push_back: size=%zu, capacity=%zu\n", v.size, v.capacity);
    

    printf("Elements: %d, %d, %d\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1),
           get_at_vector(&v, 2));

    Vector v2 = create_vector(3, copy_int, delete_int);
    push_back_vector(&v2, 10);
    push_back_vector(&v2, 20);
    push_back_vector(&v2, 30);
    

    printf("Vectors equal: %d\n", is_equal_vector(&v, &v2));

    delete_at_vector(&v, 1);
    printf("After delete at index 1: size=%zu\n", v.size);
    printf("Elements after delete: %d, %d\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1));

    copy_vector(&v, &v2);
    printf("After copy: size=%zu\n", v.size);
    

    Vector *v3 = copy_vector_new(&v);
    printf("New copied vector: size=%zu\n", v3->size);
    
    printf("Original and copy equal: %d\n", is_equal_vector(&v, v3));
    
    delete_vector(&v);
    delete_vector(&v2);
    delete_vector(v3);
    free(v3);
    printf("Vectors cleaned up\n");
    
    return 0;
}