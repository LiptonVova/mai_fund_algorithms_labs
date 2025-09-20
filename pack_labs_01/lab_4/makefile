all: main.out

main.out: main.o number_e.o number_gamma.o number_ln2.o number_pi.o number_sqrt_2.o dop_functions.o
	gcc main.o number_e.o number_gamma.o number_ln2.o number_pi.o number_sqrt_2.o dop_functions.o -g -lm -o main.out

main.o: main.c
	gcc main.c -g -c -lm -o main.o

dop_functions.o: src/dop_functions.c
	gcc src/dop_functions.c -g -c -lm -o dop_functions.o

number_e.o: src/number_e.c
	gcc src/number_e.c -g -c -lm -o number_e.o

number_gamma.o: src/number_gamma.c
	gcc src/number_gamma.c -g -c -lm -o number_gamma.o

number_ln2.o: src/number_ln2.c
	gcc src/number_ln2.c -g -c -lm -o number_ln2.o

number_pi.o: src/number_pi.c
	gcc src/number_pi.c -g -c -lm -o number_pi.o

number_sqrt_2.o: src/number_sqrt_2.c
	gcc src/number_sqrt_2.c -g -c -lm -o number_sqrt_2.o
