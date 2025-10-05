#include "../include/functions.h"
#include <unity.h>

void setUp(void) {

}

void tearDown(void) {

}

void test_strncpy_1(void) {
    char src[] = "Hello";
    char dest[10];
    
    char *result = strncpy(dest, src, 5);
    
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
    TEST_ASSERT_EQUAL_PTR(dest, result);
}

void test_strncpy_2(void) {
    char src[] = "Hello";
    char dest[10];
    
    strncpy(dest, src, 8);
    
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
    // Проверяем, что остальные символы заполнены нулями
    TEST_ASSERT_EQUAL_CHAR('\0', dest[5]);
    TEST_ASSERT_EQUAL_CHAR('\0', dest[6]);
    TEST_ASSERT_EQUAL_CHAR('\0', dest[7]);
}
void test_strncpy_3(void) {
    char src[] = "Hello World";
    char dest[20];
    
    strncpy(dest, src, 5);
    
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
}
void test_strncpy_4(void) {
    char src[] = "";
    char dest[10];
    
    strncpy(dest, src, 5);
    
    // Вся строка должна быть заполнена нулями
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL_CHAR('\0', dest[i]);
    }
}
void test_strncpy_5(void) {
    char src[] = "Hello";
    char dest[10] = "Test";
    
    strncpy(dest, src, 0);
    // не должно изменяться    
    TEST_ASSERT_EQUAL_STRING("Test", dest);
}



int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_strncpy_1);
    RUN_TEST(test_strncpy_2);
    RUN_TEST(test_strncpy_3);
    RUN_TEST(test_strncpy_4);
    RUN_TEST(test_strncpy_5);

    return UNITY_END();
}