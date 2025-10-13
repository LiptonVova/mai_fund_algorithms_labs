#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/print.h"

static FILE *test_file = NULL;

char* read_test_file(void) {
    static char buffer[1024];
    rewind(test_file);
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, test_file);
    buffer[bytes_read] = '\0';
    return buffer;
}

void setUp(void) {
    test_file = tmpfile();
    TEST_ASSERT_NOT_NULL(test_file);
}

void tearDown(void) {
    if (test_file) {
        fclose(test_file);
        test_file = NULL;
    }
}


void test_overfprintf_1(void) {
    int result = overfprintf(test_file, "Number: %d", 42);
    TEST_ASSERT_EQUAL_STRING("Number: 42", read_test_file());
    TEST_ASSERT_EQUAL(10, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "String: %s", "test");
    TEST_ASSERT_EQUAL_STRING("String: test", read_test_file());
    TEST_ASSERT_EQUAL(12, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "Number: %.2f", 3.14);
    TEST_ASSERT_EQUAL_STRING("Number: 3.14", read_test_file());
    TEST_ASSERT_EQUAL(12, result);
}

void test_overfprintf_2(void) {
    int result = overfprintf(test_file, "%Ro", 1994);
    TEST_ASSERT_EQUAL_STRING("MCMXCIV", read_test_file());
    TEST_ASSERT_EQUAL(7, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%Ro", 2023);
    TEST_ASSERT_EQUAL_STRING("MMXXIII", read_test_file());
    TEST_ASSERT_EQUAL(7, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "Number %d: %Ro", 49, 49);
    TEST_ASSERT_EQUAL_STRING("Number 49: XLIX", read_test_file());
    TEST_ASSERT_EQUAL(15, result);
}

void test_overfprintf_3(void) {
    int result = overfprintf(test_file, "%Zr", 34u);
    TEST_ASSERT_EQUAL_STRING("0010011", read_test_file());
    TEST_ASSERT_EQUAL(7, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%Zr", 20u);
    TEST_ASSERT_EQUAL_STRING("00101011", read_test_file());
    TEST_ASSERT_EQUAL(8, result);
}

void test_overfprintf_4(void) {
    int result = overfprintf(test_file, "%Cv", 255, 16);
    TEST_ASSERT_EQUAL_STRING("ff", read_test_file());
    TEST_ASSERT_EQUAL(2, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%CV", 255, 16);
    TEST_ASSERT_EQUAL_STRING("FF", read_test_file());
    TEST_ASSERT_EQUAL(2, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%Cv", 123, 8);
    TEST_ASSERT_EQUAL_STRING("173", read_test_file());
    TEST_ASSERT_EQUAL(3, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%Cv", 42, 2);
    TEST_ASSERT_EQUAL_STRING("101010", read_test_file());
    TEST_ASSERT_EQUAL(6, result);
}

void test_overfprintf_5(void) {
    int result = overfprintf(test_file, "%to", "-1010", 2);
    TEST_ASSERT_EQUAL_STRING("-10", read_test_file());
    TEST_ASSERT_EQUAL(2, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%to", "-fe", 16);
    TEST_ASSERT_EQUAL_STRING("-254", read_test_file());
    TEST_ASSERT_EQUAL(3, result);
    
    rewind(test_file);
    result = overfprintf(test_file, "%TO", "FF", 16);
    TEST_ASSERT_EQUAL_STRING("255", read_test_file());
    TEST_ASSERT_EQUAL(3, result);
    
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_overfprintf_1);
    RUN_TEST(test_overfprintf_2);
    RUN_TEST(test_overfprintf_3);
    RUN_TEST(test_overfprintf_4);
    RUN_TEST(test_overfprintf_5);


    return UNITY_END();
}