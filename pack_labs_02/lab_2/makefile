OBJ = functions.o
TEST_MEM_OUT = test_memchr.out test_memcmp.out test_memcpy.out test_memset.out
TEST_STR_1_OUT = test_strncat.out test_strchr.out test_strncmp.out test_strncpy.out test_strcspn.out
TEST_STRERROR_OUT = test_strerror.out 
TEST_STR_2_OUT = test_strlen.out test_strpbrk.out test_strrchr.out test_strstr.out test_strtok.out
FLAGS = -g -std=c99
INCLUDES_UNITY = -I./include -I../../Unity/src
UNITY_SRC = ../../Unity/src/unity.c


all: main.out 	 

test: $(TEST_MEM_OUT) $(TEST_STR_1_OUT) $(TEST_STRERROR_OUT) $(TEST_STR_2_OUT)
	./test_memchr.out 
	./test_memcmp.out 
	./test_memcpy.out 
	./test_memset.out
	./test_strncat.out
	./test_strchr.out
	./test_strncmp.out
	./test_strncpy.out
	./test_strcspn.out
	./test_strerror.out
	./test_strlen.out
	./test_strpbrk.out
	./test_strrchr.out
	./test_strstr.out
	./test_strtok.out

clean: 
	rm -f *.o *.out

main.out: main.o $(OBJ)
	gcc main.o $(OBJ) $(FLAGS) -o main.out

main.o: main.c
	gcc main.c $(FLAGS) -c -o main.o 

functions.o: src/functions.c
	gcc src/functions.c $(FLAGS) -c -o functions.o

test_memchr.out: $(OBJ) test_memchr.o unity.o
	gcc $(OBJ) test_memchr.o unity.o -o test_memchr.out

test_memcmp.out: $(OBJ) test_memcmp.o unity.o
	gcc $(OBJ) test_memcmp.o unity.o -o test_memcmp.out

test_memcpy.out: $(OBJ) test_memcpy.o unity.o
	gcc $(OBJ) test_memcpy.o unity.o -o test_memcpy.out

test_memset.out: $(OBJ) test_memset.o unity.o
	gcc $(OBJ) test_memset.o unity.o -o test_memset.out

test_strncat.out: $(OBJ) test_strncat.o unity.o
	gcc $(OBJ) test_strncat.o unity.o -o test_strncat.out

test_strchr.out: $(OBJ) test_strchr.o unity.o
	gcc $(OBJ) test_strchr.o unity.o -o test_strchr.out

test_strncmp.out: $(OBJ) test_strncmp.o unity.o
	gcc $(OBJ) test_strncmp.o unity.o -o test_strncmp.out

test_strncpy.out: $(OBJ) test_strncpy.o unity.o
	gcc $(OBJ) test_strncpy.o unity.o -o test_strncpy.out

test_strcspn.out: $(OBJ) test_strcspn.o unity.o
	gcc $(OBJ) test_strcspn.o unity.o -o test_strcspn.out

test_strerror.out: $(OBJ) test_strerror.o unity.o
	gcc $(OBJ) test_strerror.o unity.o -o test_strerror.out

test_strlen.out: $(OBJ) test_strlen.o unity.o
	gcc $(OBJ) test_strlen.o unity.o -o test_strlen.out

test_strpbrk.out: $(OBJ) test_strpbrk.o unity.o
	gcc $(OBJ) test_strpbrk.o unity.o -o test_strpbrk.out

test_strrchr.out: $(OBJ) test_strrchr.o unity.o
	gcc $(OBJ) test_strrchr.o unity.o -o test_strrchr.out

test_strstr.out: $(OBJ) test_strstr.o unity.o
	gcc $(OBJ) test_strstr.o unity.o -o test_strstr.out

test_strtok.out: $(OBJ) test_strtok.o unity.o
	gcc $(OBJ) test_strtok.o unity.o -o test_strtok.out

test_memchr.o: tests/test_memchr.c
	gcc tests/test_memchr.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_memchr.o

test_memcmp.o: tests/test_memcmp.c
	gcc tests/test_memcmp.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_memcmp.o

test_memcpy.o: tests/test_memcpy.c
	gcc tests/test_memcpy.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_memcpy.o

test_memset.o: tests/test_memset.c
	gcc tests/test_memset.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_memset.o

test_strncat.o: tests/test_strncat.c
	gcc tests/test_strncat.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strncat.o

test_strchr.o: tests/test_strchr.c
	gcc tests/test_strchr.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strchr.o

test_strncmp.o: tests/test_strncmp.c
	gcc tests/test_strncmp.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strncmp.o

test_strncpy.o: tests/test_strncpy.c
	gcc tests/test_strncpy.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strncpy.o

test_strcspn.o: tests/test_strcspn.c
	gcc tests/test_strcspn.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strcspn.o

test_strerror.o: tests/test_strerror.c
	gcc tests/test_strerror.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strerror.o

test_strlen.o: tests/test_strlen.c
	gcc tests/test_strlen.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strlen.o

test_strpbrk.o: tests/test_strpbrk.c
	gcc tests/test_strpbrk.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strpbrk.o

test_strrchr.o: tests/test_strrchr.c
	gcc tests/test_strrchr.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strrchr.o

test_strstr.o: tests/test_strstr.c
	gcc tests/test_strstr.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strstr.o

test_strtok.o: tests/test_strtok.c
	gcc tests/test_strtok.c $(FLAGS) $(INCLUDES_UNITY) -c -o test_strtok.o

unity.o: $(UNITY_SRC)
	gcc $(FLAGS) $(INCLUDES_UNITY) $(UNITY_SRC) -c -o unity.o


.PHONY:
	all test clean