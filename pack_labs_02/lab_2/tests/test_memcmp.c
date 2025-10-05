#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}

void test_memcmp_1(void) {
    const char str1[] = "Hello, World!";
    const char str2[] = "Hello, World!";
    
    int result = memcmp(str1, str2, strlen(str1));
    TEST_ASSERT_EQUAL(0, result);
}
void test_memcmp_2(void) {
    const unsigned char arr1[] = {0x01, 0x02, 0x03, 0x04};
    const unsigned char arr2[] = {0x01, 0x02, 0x03, 0x04};
    
    int result = memcmp(arr1, arr2, sizeof(arr1));
    TEST_ASSERT_EQUAL(0, result);
}
void test_memcmp_3(void) {
    const char str1[] = "Apple";
    const char str2[] = "Banana";
    
    int result = memcmp(str1, str2, 5);
    TEST_ASSERT_EQUAL(-1, result);
}
void test_memcmp_4(void) {
    const char str1[] = "Cat";
    const char str2[] = "Bat";
    
    int result = memcmp(str1, str2, 3);
    TEST_ASSERT_EQUAL(1, result);

}
void test_memcmp_5(void) {
    const char str1[] = "Hello";
    const char str2[] = "Hello, World!";
    
    int result = memcmp(str1, str2, 5); 
    TEST_ASSERT_EQUAL(0, result);
}
void test_memcmp_6(void) {
    const unsigned char arr1[] = {0x10, 0x20, 0x30, 0x40};
    const unsigned char arr2[] = {0x10, 0x20, 0x31, 0x40};
    
    int result = memcmp(arr1, arr2, 4);
    TEST_ASSERT_EQUAL(-1, result); 
}

void test_memcmp_7(void) {
    typedef struct {
        int id;
        char name[10];
        float value;
    } TestStruct;
    
    TestStruct struct1 = {1, "Test", 3.14f};
    TestStruct struct2 = {1, "Test", 3.14f};
    
    int result = memcmp(&struct1, &struct2, sizeof(TestStruct));
    TEST_ASSERT_EQUAL(0, result);
}


int main() {
    UNITY_BEGIN();

    
    RUN_TEST(test_memcmp_1);
    RUN_TEST(test_memcmp_2);
    RUN_TEST(test_memcmp_3);
    RUN_TEST(test_memcmp_4);
    RUN_TEST(test_memcmp_5);
    RUN_TEST(test_memcmp_6);
    RUN_TEST(test_memcmp_7);

    return UNITY_END();

}