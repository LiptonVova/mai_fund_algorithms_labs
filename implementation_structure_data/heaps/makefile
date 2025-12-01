FLAGS = -g -Wall -std=c99

all: test_fibonacci_heap.out

clean:
	rm -rf *.out *.o

test_fibonacci_heap.out: test_fibonacci_heap.o fibonacci_heap.o 
	gcc test_fibonacci_heap.o fibonacci_heap.o $(FLAGS) -o test_fibonacci_heap.out

test_fibonacci_heap.o: ./fibonacci_heap/test_fibonacci_heap.c
	gcc ./fibonacci_heap/test_fibonacci_heap.c $(FLAGS) -c -o test_fibonacci_heap.o

fibonacci_heap.o: ./fibonacci_heap/fibonacci_heap.c
	gcc ./fibonacci_heap/fibonacci_heap.c $(FLAGS) -c -o fibonacci_heap.o