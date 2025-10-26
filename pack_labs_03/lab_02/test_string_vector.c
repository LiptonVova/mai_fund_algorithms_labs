#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/vector.h"

char* copy_string(char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* new_str = malloc(len + 1);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}

void delete_string(char* str) {
    free(str);
}

DEFINE_VECTOR(char*)

int main() {
    printf("=== Testing String Vector ===\n");
    

    Vector v = create_vector(2, copy_string, delete_string);
    printf("Vector created: size=%zu, capacity=%zu\n", v.size, v.capacity);
    

    push_back_vector(&v, copy_string("Hello"));
    push_back_vector(&v, copy_string("World"));
    push_back_vector(&v, copy_string("Test"));
    printf("After push_back: size=%zu, capacity=%zu\n", v.size, v.capacity);

    printf("Elements: %s, %s, %s\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1),
           get_at_vector(&v, 2));
    
    delete_at_vector(&v, 1);
    printf("After delete at index 1: size=%zu\n", v.size);
    printf("Elements after delete: %s, %s\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1));
    
    Vector v2 = create_vector(2, copy_string, delete_string);
    push_back_vector(&v2, copy_string("One"));
    push_back_vector(&v2, copy_string("Two"));
    
    copy_vector(&v, &v2);
    printf("After copy: size=%zu\n", v.size);
    printf("Copied elements: %s, %s\n", 
           get_at_vector(&v, 0),
           get_at_vector(&v, 1));
    
    printf("Vectors equal: %d\n", is_equal_vector(&v, &v2));

    delete_vector(&v);
    delete_vector(&v2);
    printf("Vectors cleaned up\n");
    
    return 0;
}