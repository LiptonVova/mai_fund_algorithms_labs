#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}

void test_memset_1(void) {
    char buffer[10] = "abcdefghi";
    
    void* result = memset(buffer, 0, 8);
    
    TEST_ASSERT_EQUAL_PTR(buffer, result);
    for (int i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL(0, buffer[i]);
    }
    TEST_ASSERT_EQUAL('i', buffer[8]);
}
void test_memset_2(void) {
    char buffer[10];
    
    memset(buffer, 'A', 10);
    
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL('A', buffer[i]);
    }
}
void test_memset_3(void) {
    char buffer[] = "Original";
    char original[] = "Original";
    
    void* result = memset(buffer, 'X', 0);
    
    TEST_ASSERT_EQUAL_PTR(buffer, result);
    TEST_ASSERT_EQUAL_STRING(original, buffer);
}
void test_memset_4(void) {
    char buffer[] = "Hello";
    
    memset(buffer, 'X', 1);
    
    TEST_ASSERT_EQUAL('X', buffer[0]);
    TEST_ASSERT_EQUAL('e', buffer[1]);
    TEST_ASSERT_EQUAL('l', buffer[2]);
    TEST_ASSERT_EQUAL('l', buffer[3]);
    TEST_ASSERT_EQUAL('o', buffer[4]);
}
void test_memset_5(void) {
    signed char buffer[5];
    
    memset(buffer, -1, 5);
    
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL(-1, buffer[i]);
    }
}
void test_memset_6(void) {
    unsigned char buffer[10];
    const unsigned char test_values[] = {0x00, 0x01, 0x7F, 0x80, 0xFF};
    
    for (int i = 0; i < 5; i++) {
        memset(buffer, test_values[i], 10);
        for (int j = 0; j < 10; j++) {
            TEST_ASSERT_EQUAL_HEX8(test_values[i], buffer[j]);
        }
    }
}

int main() {
    UNITY_BEGIN();


    RUN_TEST(test_memset_1);
    RUN_TEST(test_memset_2);
    RUN_TEST(test_memset_3);
    RUN_TEST(test_memset_4);
    RUN_TEST(test_memset_5);
    RUN_TEST(test_memset_6);

    return UNITY_END();

}