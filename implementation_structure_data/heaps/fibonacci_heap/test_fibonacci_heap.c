#include <stdio.h>
#include "fibonacci_heap.h"

int main() {
    Fibonacci_heap heap = create_fibonacci_heap();

    push(&heap, 1);
    push(&heap, 2);
    push(&heap, 3);
    push(&heap, -1);
    push(&heap, 4);
    push(&heap, -10);
    push(&heap, 20);
    push(&heap, 5);

    int i = 1;
    while (heap.size != 0) {
        int elem = peek(&heap);
        printf("Элемент №%d = %d\n", i, elem);

        pop(&heap);

        if (i == 5) {
            printf("Произошла вставка (100) по середине\n");
            push(&heap, 100);

            printf("Произошла вставка (-100) по середине\n");
            push(&heap, -100);
        }
        ++i;
    }


    free_heap(&heap);
}