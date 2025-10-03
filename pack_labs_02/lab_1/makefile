OBJ = fraction.o check_finite_fraction.o math_function.o
FLAGS = -g -std=c99
INCLUDES_UNITY = -I./include -I../../Unity/src
UNITY_SRC = ../../Unity/src/unity.c

all: main.out test.out

test: test.out
	./test.out

clean: 
	rm -f *.o *.out
	rm -f main.out test.out

main.out: main.o $(OBJ)
	gcc main.o $(OBJ) -g -lm -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o 

fraction.o: src/fraction.c
	gcc src/fraction.c $(FLAGS) -c -o fraction.o

math_function.o: src/math_function.c
	gcc src/math_function.c $(FLAGS) -c -o math_function.o

check_finite_fraction.o: src/check_finite_fraction.c
	gcc src/check_finite_fraction.c $(FLAGS) -c -o check_finite_fraction.o

test.out: $(OBJ) test.o unity.o
	gcc $(OBJ) test.o unity.o -lm -o test.out

test.o: tests/test.c
	gcc tests/test.c $(FLAGS) $(INCLUDES_UNITY) -c -o test.o

unity.o: $(UNITY_SRC)
	gcc $(FLAGS) $(INCLUDES_UNITY) $(UNITY_SRC) -c -o unity.o


.PHONY:
	all test clean