FLAGS = -g -Wall -std=c99
OBJ = additional_functions.o overscanf.o specifiers.o roman_numbers.o zeckendorf.o translate_base_to_ten.o
TEST = test_overfscanf.out test_oversscanf.out
INCLUDES_UNITY=-I./include -I../../Unity/src
UNITY_SRC=../../Unity/src/unity.c

all: main.out

test: $(TEST)
	./test_overfscanf.out
	./test_oversscanf.out

clean: 
	rm -f *.o *.out

main.out: $(OBJ) main.o 
	gcc $(OBJ) main.o $(FLAGS) -o main.out 

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o

additional_functions.o: src/additional_functions.c
	gcc src/additional_functions.c $(FLAGS) -c -o additional_functions.o

overscanf.o: src/overscanf.c
	gcc src/overscanf.c $(FLAGS) -c -o overscanf.o

specifiers.o: src/specifiers.c
	gcc src/specifiers.c $(FLAGS) -c -o specifiers.o

roman_numbers.o: src/roman_numbers.c
	gcc src/roman_numbers.c $(FLAGS) -c -o roman_numbers.o

zeckendorf.o: src/zeckendorf.c
	gcc src/zeckendorf.c $(FLAGS) -c -o zeckendorf.o

translate_base_to_ten.o: src/translate_base_to_ten.c
	gcc src/translate_base_to_ten.c $(FLAGS) -c -o translate_base_to_ten.o

test_overfscanf.out: $(OBJ) test_overfscanf.o unity.o
	gcc $(OBJ) test_overfscanf.o unity.o -o test_overfscanf.out

test_overfscanf.o: tests/test_overfscanf.c
	gcc tests/test_overfscanf.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_overfscanf.o

test_oversscanf.out: $(OBJ) test_oversscanf.o unity.o
	gcc $(OBJ) test_oversscanf.o unity.o -o test_oversscanf.out

test_oversscanf.o: tests/test_oversscanf.c
	gcc tests/test_oversscanf.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_oversscanf.o

unity.o: $(UNITY_SRC)
	gcc $(FLAGS) $(INCLUDES_UNITY) $(UNITY_SRC) -c -o unity.o

.PHONY:
	all test clean