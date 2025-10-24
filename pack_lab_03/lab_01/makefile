all: main.out 

main.out: main.o solve.o
	gcc main.o solve.o -g -Wall -std=c99 -o main.out

main.o: main.c
	gcc main.c -g -Wall -std=c99 -c -o main.o

solve.o: src/solve.c
	gcc src/solve.c -g -Wall -std=c99 -c -o solve.o