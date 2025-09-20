all: main.out

main.out: main.o str_to_int.o main_functions.o
	gcc main.o str_to_int.o main_functions.o -o main.out

main.o: main.c 
	gcc main.c -c -g -o main.o

main_functions.o: src/main_functions.c
	gcc src/main_functions.c -c -g -o main_functions.o

str_to_int.o: src/str_to_int.c
	gcc src/str_to_int.c -c -g -o str_to_int.o 