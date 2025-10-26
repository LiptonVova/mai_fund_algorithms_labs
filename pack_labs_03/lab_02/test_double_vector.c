#include <stdio.h>
#include "include/vector.h"

double copy_double(double value) {
    return value;
}

void delete_double(double value) {
    (void)value;
}

DEFINE_VECTOR(double)

int main() {
    printf("=== Testing Double Vector ===\n");
    
    Vector v = create_vector(3, copy_double, delete_double);
    printf("Vector created: size=%zu, capacity=%zu\n", v.size, v.capacity);
    
    push_back_vector(&v, 1.1);
    push_back_vector(&v, 2.2);
    push_back_vector(&v, 3.3);
    printf("After push_back: size=%zu, capacity=%zu\n", v.size, v.capacity);
    
    printf("Elements: %.1f, %.1f, %.1f\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1),
           get_at_vector(&v, 2));
    
    Vector *v_copy = copy_vector_new(&v);
    printf("New copied vector: size=%zu\n", v_copy->size);
    
    printf("Original and copy equal: %d\n", is_equal_vector(&v, v_copy));
    
    erase_vector(&v);
    printf("After erase: size=%zu, capacity=%zu\n", v.size, v.capacity);
    
    // Очистка
    delete_vector(v_copy);
    free(v_copy);
    delete_vector(&v);
    printf("Vectors cleaned up\n");
    
    return 0;
}