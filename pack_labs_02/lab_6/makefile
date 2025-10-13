FLAGS = -g -std=c99 -Wall

all: main.out

clean: 
	rm -f *.out *.o

main.out: main.o functions.o handle.o print.o comp.o
	gcc main.o functions.o handle.o print.o comp.o $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o

functions.o: src/functions.c
	gcc src/functions.c $(FLAGS) -c -o functions.o

handle.o: src/handle.c
	gcc src/handle.c $(FLAGS) -c -o handle.o 

print.o: src/print.c
	gcc src/print.c $(FLAGS) -c -o print.o 

comp.o: src/comp.c
	gcc src/comp.c $(FLAGS) -c -o comp.o