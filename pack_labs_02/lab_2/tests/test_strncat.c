#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}


void test_strncat_1(void) {
    char dest[20] = "Hello";
    const char src[] = " World!";
    
    char* result = strncat(dest, src, 10); // n больше длины src
    
    TEST_ASSERT_EQUAL_PTR(dest, result);
    TEST_ASSERT_EQUAL_STRING("Hello World!", dest);
}

void test_strncat_2(void) {
    char dest[20] = "Hello";
    const char src[] = " World!";
    
    strncat(dest, src, 3); // Добавляем только " Wo"
    
    TEST_ASSERT_EQUAL_STRING("Hello Wo", dest);
}
void test_strncat_3(void) {
    char dest[20] = "Hello";
    const char src[] = "!";
    
    strncat(dest, src, 5); // n больше длины src
    
    TEST_ASSERT_EQUAL_STRING("Hello!", dest);
}
void test_strncat_4(void) {
    char dest[20] = "";
    const char src[] = "Hello";
    
    strncat(dest, src, 5);
    
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
}
void test_strncat_5(void) {
    char dest[50] = "A";
    const char src1[] = "B";
    const char src2[] = "C";
    const char src3[] = "D";
    
    strncat(dest, src1, 1);
    strncat(dest, src2, 1);
    strncat(dest, src3, 1);
    
    TEST_ASSERT_EQUAL_STRING("ABCD", dest);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_strncat_1);
    RUN_TEST(test_strncat_2);
    RUN_TEST(test_strncat_3);
    RUN_TEST(test_strncat_4);
    RUN_TEST(test_strncat_5);

    return UNITY_END();

}