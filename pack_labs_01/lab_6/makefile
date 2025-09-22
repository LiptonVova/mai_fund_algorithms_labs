all: main.out

main.out: main.o functions.o validate.o
	gcc main.o functions.o validate.o -g -lm -o main.out

main.o: main.c
	gcc main.c -g -c -o main.o

functions.o: src/functions.c
	gcc src/functions.c -g -c -o functions.o 

validate.o: src/validate.c
	gcc src/validate.c -g -c -o validate.o