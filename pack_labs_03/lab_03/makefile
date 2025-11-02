FLAGS = -g -Wall -std=c99
OBJ = main.o handles.o solve.o config.o utils.o search.o edit.o undo.o

all: main.out test_list.out

clean: 
	rm -rf *.o *.out

main.out: $(OBJ)
	gcc $(OBJ) $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o 

test_list.out: test_list.c
	gcc test_list.c $(FLAGS) -o test_list.out

handles.o: src/handles.c
	gcc src/handles.c $(FLAGS) -c -o handles.o

solve.o: src/solve.c src/handles.c src/config.c
	gcc src/solve.c $(FLAGS) -c -o solve.o

config.o: src/config.c 
	gcc src/config.c $(FLAGS) -c -o config.o

utils.o: src/utils.c
	gcc src/utils.c $(FLAGS) -c -o utils.o

search.o: src/search.c
	gcc src/search.c $(FLAGS) -c -o search.o

edit.o: src/edit.c
	gcc src/edit.c $(FLAGS) -c -o edit.o

undo.o: src/undo.c
	gcc src/undo.c $(FLAGS) -c -o undo.o

