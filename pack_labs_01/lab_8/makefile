all: main.out

main.out: main.o validate.o solve.o
	gcc main.o validate.o solve.o -g -lm -o main.out

main.o: main.c
	gcc main.c -g -c -o main.o

validate.o: src/validate.c
	gcc src/validate.c -g -c -o validate.o

solve.o: src/solve.c
	gcc src/solve.c -g -c -o solve.o