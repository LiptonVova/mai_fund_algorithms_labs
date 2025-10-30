FLAGS = -g -Wall -std=c99

all: main.out

clean: 
	rm -rf *.o *.out

main.out: main.o solve.o
	gcc main.o solve.o $(FLAGS) -o main.out

main.o: main.c include/linkedList.h
	gcc main.c $(FLAGS) -c -o main.o 

solve.o: src/solve.c 
	gcc src/solve.c $(FLAGS) -c -o solve.o