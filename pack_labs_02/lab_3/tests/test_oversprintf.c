#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/print.h"

void setUp(void) {

}

void tearDown(void) {

}


void test_oversprintf_1(void) {
    char buffer[256];
    int result;
    
    result = oversprintf(buffer, "Number: %d", 42);
    TEST_ASSERT_EQUAL_STRING("Number: 42", buffer);
    TEST_ASSERT_EQUAL(10, result);
    
    result = oversprintf(buffer, "String: %s", "test");
    TEST_ASSERT_EQUAL_STRING("String: test", buffer);
    TEST_ASSERT_EQUAL(12, result);
    
    result = oversprintf(buffer, "Number: %.2f", 3.14);
    TEST_ASSERT_EQUAL_STRING("Number: 3.14", buffer);
    TEST_ASSERT_EQUAL(12, result);
}

void test_oversprintf_2(void) {
    char buffer[256];
    int result;
    
    result = oversprintf(buffer, "%Ro", 1994);
    TEST_ASSERT_EQUAL_STRING("MCMXCIV", buffer);
    TEST_ASSERT_EQUAL(7, result);
    
    result = oversprintf(buffer, "%Ro", 2023);
    TEST_ASSERT_EQUAL_STRING("MMXXIII", buffer);
    TEST_ASSERT_EQUAL(7, result);
    
    result = oversprintf(buffer, "%Ro", 49);
    TEST_ASSERT_EQUAL_STRING("XLIX", buffer);
    TEST_ASSERT_EQUAL(4, result);
    
    result = oversprintf(buffer, "%Ro", 1);
    TEST_ASSERT_EQUAL_STRING("I", buffer);
    TEST_ASSERT_EQUAL(1, result);
}

void test_oversprintf_3(void) {
    char buffer[256];
    int result;
    
    result = oversprintf(buffer, "%Zr", 10u);
    TEST_ASSERT_EQUAL_STRING("0010011", buffer);
    TEST_ASSERT_EQUAL(7, result);
    
    result = oversprintf(buffer, "%Zr", 20u);
    TEST_ASSERT_EQUAL_STRING("00101011", buffer);
    TEST_ASSERT_EQUAL(8, result);
    
    result = oversprintf(buffer, "%Zr", 15u);
    TEST_ASSERT_EQUAL_STRING("00100011", buffer);
    TEST_ASSERT_EQUAL(8, result);

    result = oversprintf(buffer, "%Zr", 34u);
    TEST_ASSERT_EQUAL_STRING("0000000011", buffer);
    TEST_ASSERT_EQUAL(10, result);
}

void test_oversprintf_4(void) {
    char buffer[256];
    int result;
    
    result = oversprintf(buffer, "%Cv", 255, 16);
    TEST_ASSERT_EQUAL_STRING("ff", buffer);
    TEST_ASSERT_EQUAL(2, result);
    
    result = oversprintf(buffer, "%CV", 255, 16);
    TEST_ASSERT_EQUAL_STRING("FF", buffer);
    TEST_ASSERT_EQUAL(2, result);
    
    result = oversprintf(buffer, "%Cv", 123, 8);
    TEST_ASSERT_EQUAL_STRING("173", buffer);
    TEST_ASSERT_EQUAL(3, result);
    
    result = oversprintf(buffer, "%Cv", 42, 2);
    TEST_ASSERT_EQUAL_STRING("101010", buffer);
    TEST_ASSERT_EQUAL(6, result);
    
    result = oversprintf(buffer, "%Cv", 123, 50);
    TEST_ASSERT_EQUAL_STRING("123", buffer);
    TEST_ASSERT_EQUAL(3, result);
}

void test_oversprintf_5(void) {    
    char buffer[256];
    int result;

    result = oversprintf(buffer, "%to", "ff", 16);
    TEST_ASSERT_EQUAL_STRING("255", buffer);
    TEST_ASSERT_EQUAL(3, result);
    
    result = oversprintf(buffer, "%TO", "FF", 16);
    TEST_ASSERT_EQUAL_STRING("255", buffer);
    TEST_ASSERT_EQUAL(3, result);
    
    result = oversprintf(buffer, "%to", "1010", 2);
    TEST_ASSERT_EQUAL_STRING("10", buffer);
    TEST_ASSERT_EQUAL(2, result);
    
    result = oversprintf(buffer, "%to", "123", 50);
    TEST_ASSERT_EQUAL_STRING("123", buffer);
    TEST_ASSERT_EQUAL(3, result);
}


void test_oversprintf_6(void) {
    char buffer[256];
    int result;
    
    result = oversprintf(buffer, "%Ro", 0);
    TEST_ASSERT_EQUAL_STRING("NaN", buffer);
    TEST_ASSERT_TRUE(result == 3);
    
    result = oversprintf(buffer, "%Zr", 0u);
    TEST_ASSERT_EQUAL_STRING("1", buffer);
    TEST_ASSERT_TRUE(result == 1);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_oversprintf_1);
    RUN_TEST(test_oversprintf_2);
    RUN_TEST(test_oversprintf_3);
    RUN_TEST(test_oversprintf_4);
    RUN_TEST(test_oversprintf_5);
    RUN_TEST(test_oversprintf_6);


    return UNITY_END();
}