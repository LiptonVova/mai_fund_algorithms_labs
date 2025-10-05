#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}

void test_strlen_1(void) {
    TEST_ASSERT_EQUAL(0, strlen(""));
    TEST_ASSERT_EQUAL(1, strlen("a"));
    TEST_ASSERT_EQUAL(5, strlen("hello"));
    TEST_ASSERT_EQUAL(11, strlen("hello world"));
}
void test_strlen_2(void) { 
    TEST_ASSERT_EQUAL(4, strlen("tab\t"));
    TEST_ASSERT_EQUAL(3, strlen("\\n\n")); 
    TEST_ASSERT_EQUAL(6, strlen("sp ace"));
}
void test_strlen_3(void) {
    TEST_ASSERT_EQUAL(10, strlen("1234567890"));
    TEST_ASSERT_EQUAL(7, strlen("!@#$%^&"));
    TEST_ASSERT_EQUAL(8, strlen("test1234"));
}
void test_strlen_4(void) {
    TEST_ASSERT_EQUAL(3, strlen("   "));
    TEST_ASSERT_EQUAL(5, strlen("  a  "));
    TEST_ASSERT_EQUAL(8, strlen("  test  "));
}
void test_strlen_5(void) {
    TEST_ASSERT_EQUAL(0, strlen("\0"));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strlen_1);
    RUN_TEST(test_strlen_2);
    RUN_TEST(test_strlen_3);
    RUN_TEST(test_strlen_4);
    RUN_TEST(test_strlen_5);

    return UNITY_END();
}