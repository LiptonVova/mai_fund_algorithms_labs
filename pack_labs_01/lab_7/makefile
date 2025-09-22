all: main.out

main.out: main.o output.o solve.o
	gcc main.o output.o solve.o -g -o main.out

main.o: main.c
	gcc main.c -g -c -o main.o

output.o: src/output.c
	gcc src/output.c -g -c -o output.o

solve.o: src/solve.c
	gcc src/solve.c -g -c -o solve.o