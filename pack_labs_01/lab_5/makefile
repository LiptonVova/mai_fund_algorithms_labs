all: main.out

main.out: main.o output.o flags.o dop_functions.o
	gcc main.o output.o flags.o dop_functions.o -g -o main.out

main.o: main.c
	gcc main.c -g -c -o main.o

output.o: src/output.c
	gcc src/output.c -g -c -o output.o

flags.o: src/flags.c
	gcc src/flags.c -g -c -o flags.o

dop_functions.o: src/dop_functions.c
	gcc src/dop_functions.c -g -c -o dop_functions.o