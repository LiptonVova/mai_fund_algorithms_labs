all: main.out

main.out: main.o lab_2.o
	gcc main.o lab_2.o -g -o main.out

main.o: main.c
	gcc main.c -g -c -o main.o

lab_2.o: src/lab_2.c
	gcc src/lab_2.c -g -c -o lab_2.o
