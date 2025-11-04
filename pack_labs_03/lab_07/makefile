FLAGS=-g -Wall -std=c99

all: main.out

clean:
	rm -rf *.o *.out

main.out: main.o solve.o utils.o config.o dijkstra.o
	gcc main.o solve.o utils.o config.o dijkstra.o $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o 

solve.o: src/solve.c
	gcc src/solve.c $(FLAGS) -c -o solve.o

utils.o: src/utils.c
	gcc src/utils.c $(FLAGS) -c -o utils.o

config.o: src/config.c
	gcc src/config.c $(FLAGS) -c -o config.o

dijkstra.o: src/dijkstra.c
	gcc src/dijkstra.c $(FLAGS) -c -o dijkstra.o