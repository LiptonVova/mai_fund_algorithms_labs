all: main.out

main.out: main.o output.o check.o solve.o
	gcc main.o output.o check.o solve.o -lm -o main.out

main.o: main.c
	gcc main.c -g -c -o main.o

output.o: src/output.c
	gcc src/output.c -g -c -lm -o output.o

check.o: src/check.c
	gcc src/check.c -g -c -o check.o

solve.o: src/solve.c
	gcc src/solve.c -g -c -lm -o solve.o