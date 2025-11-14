FLAGS = -g -Wall -pthread
OBJ = main.o config.o core.o utils.o validate.o handles.o

all: main.out test_binary_heap_int.out

clean: 
	rm -rf *.o *.out

main.out: $(OBJ)
	gcc $(OBJ) $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o 

core.o: src/core.c
	gcc src/core.c $(FLAGS) -c -o core.o 

config.o: src/config.c
	gcc src/config.c $(FLAGS) -c -o config.o 

utils.o: src/utils.c
	gcc src/utils.c $(FLAGS) -c -o utils.o 

validate.o: src/validate.c
	gcc src/validate.c $(FLAGS) -c -o validate.o 

handles.o: src/handles.c
	gcc src/handles.c $(FLAGS) -c -o handles.o 

test_binary_heap_int.out: test_binary_heap_int.c 
	gcc test_binary_heap_int.c $(FLAGS) -o test_binary_heap_int.out