FLAGS=-g -Wall -std=c99

all: main.out test_binary_heap_int.out test_binary_heap_double.out test_binary_heap_struct.out

clean: 
	rm -rf *.o *.out

main.out: main.o
	gcc main.o $(FLAGS) -o main.out

main.o: main.c 
	gcc main.c $(FLAGS) -c -o main.o

test_binary_heap_int.out: test_binary_heap_int.c
	gcc test_binary_heap_int.c $(FLAGS) -o test_binary_heap_int.out

test_binary_heap_double.out: test_binary_heap_double.c
	gcc test_binary_heap_double.c $(FLAGS) -o test_binary_heap_double.out

test_binary_heap_struct.out: test_binary_heap_struct.c
	gcc test_binary_heap_struct.c $(FLAGS) -o test_binary_heap_struct.out