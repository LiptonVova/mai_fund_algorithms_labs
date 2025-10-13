FLAGS = -g -std=c99 -Wall
OBJ = functions.o

all: main.out

main.out: main.o $(OBJ)
	gcc main.o $(OBJ) $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o

functions.o: src/functions.c
	gcc src/functions.c $(FLAGS) -c -o functions.o