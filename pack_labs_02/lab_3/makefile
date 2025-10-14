OBJ=print.o additional_functions.o specifiers.o
TEST=test_overfprintf.out test_oversprintf.out
FLAGS=-g -std=c99
INCLUDES_UNITY=-I./include -I../../Unity/src
UNITY_SRC=../../Unity/src/unity.c


all: main.out

test: $(TEST)
	./test_oversprintf.out
	./test_overfprintf.out

clean: 
	rm -f *.o *.out

main.out: main.o $(OBJ)
	gcc main.o $(OBJ) $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o

print.o: src/print.c
	gcc src/print.c $(FLAGS) -c -o print.o

additional_functions.o: src/additional_functions.c
	gcc src/additional_functions.c $(FLAGS) -c -o additional_functions.o

specifiers.o: src/specifiers.c
	gcc src/specifiers.c $(FLAGS) -c -o specifiers.o

test_overfprintf.out: $(OBJ) test_overfprintf.o unity.o
	gcc $(OBJ) test_overfprintf.o unity.o -o test_overfprintf.out

test_overfprintf.o: tests/test_overfprintf.c
	gcc tests/test_overfprintf.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_overfprintf.o

test_oversprintf.out: $(OBJ) test_oversprintf.o unity.o
	gcc $(OBJ) test_oversprintf.o unity.o -o test_oversprintf.out

test_oversprintf.o: tests/test_oversprintf.c
	gcc tests/test_oversprintf.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_oversprintf.o


unity.o: $(UNITY_SRC)
	gcc $(FLAGS) $(INCLUDES_UNITY) $(UNITY_SRC) -c -o unity.o


.PHONY:
	all test clean