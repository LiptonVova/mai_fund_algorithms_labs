#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}

void test_memchr_1(void) {
    char str[] = "hello world";
    char* result = memchr(str, 'h', strlen(str));
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(str, result);
    TEST_ASSERT_EQUAL_CHAR('h', *result);
}

void test_memchr_2(void) {
    char str[] = "hello world";
    char* result = memchr(str, 'w', strlen(str));
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_CHAR('w', *result);
    TEST_ASSERT_EQUAL_PTR(str + 6, result);
}

void test_memchr_3(void) {
    char str[] = "hello";
    char* result = memchr(str, 'o', strlen(str));
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_CHAR('o', *result);
    TEST_ASSERT_EQUAL_PTR(str + 4, result);
}

void test_memchr_4(void) {
    char str[] = "hello";
    char* result = memchr(str, 'x', strlen(str));
    
    TEST_ASSERT_NULL(result);
}

void test_memchr_5(void) {
    char str[] = "hello world";
    char* result = memchr(str, 'o', 4);
    
    TEST_ASSERT_NULL(result);
}


void test_memchr_6(void) {
    char str[] = "";
    char* result = memchr(str, 'a', 0);
    
    TEST_ASSERT_NULL(result);
}

void test_memchr_7(void) {
    unsigned char data[] = {0xFF, 0x10, 0x08, 0x00};
    void* result = memchr(data, 0x08, sizeof(data));
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_HEX8(0x08, *(unsigned char*)result);
    TEST_ASSERT_EQUAL_PTR(data + 2, result);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_memchr_1);
    RUN_TEST(test_memchr_2);
    RUN_TEST(test_memchr_3);
    RUN_TEST(test_memchr_4);
    RUN_TEST(test_memchr_5);
    RUN_TEST(test_memchr_6);
    RUN_TEST(test_memchr_7);

    return UNITY_END();
}