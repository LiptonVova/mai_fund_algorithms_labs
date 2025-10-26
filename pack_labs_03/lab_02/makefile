FLAGS=-g -Wall -std=c99

all: main.out test_int_vector.out test_string_vector.out test_double_vector.out

clean:
	rm -rf *.o *.out

main.out: main.o
	gcc main.o $(FLAGS) -o main.out

main.o: main.c include/vector.h
	gcc main.c $(FLAGS) -c -o main.o

test_int_vector.out: test_int_vector.c include/vector.h
	gcc test_int_vector.c $(FLAGS) -o test_int_vector.out

test_string_vector.out: test_string_vector.c include/vector.h
	gcc test_string_vector.c $(FLAGS) -o test_string_vector.out

test_double_vector.out: test_double_vector.c include/vector.h
	gcc test_double_vector.c $(FLAGS) -o test_double_vector.out

