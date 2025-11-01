FLAGS = -g -Wall -std=c99

all: main.out test_list.out

clean: 
	rm -rf *.o *.out

main.out: main.o handles.o solve.o 
	gcc main.o handles.o solve.o $(FLAGS) -o main.out

main.o: main.c include/linkedList.h
	gcc main.c $(FLAGS) -c -o main.o 

test_list.out: test_list.c
	gcc test_list.c $(FLAGS) -o test_list.out

handles.o: src/handles.c include/linkedList.h
	gcc src/handles.c $(FLAGS) -c -o handles.o

solve.o: src/solve.c src/handles.c
	gcc src/solve.c $(FLAGS) -c -o solve.o

