#include "../include/functions.h"
#include <unity.h>



void setUp(void) {

}

void tearDown(void) {

}

void test_strstr_1(void) {
    const char *haystack = "hello world";
    
    TEST_ASSERT_EQUAL_STRING("hello world", strstr(haystack, "hello"));
    TEST_ASSERT_EQUAL_STRING("world", strstr(haystack, "world"));
    TEST_ASSERT_EQUAL_STRING("lo world", strstr(haystack, "lo"));
    TEST_ASSERT_EQUAL_STRING("o world", strstr(haystack, "o w"));
}

void test_strstr_2(void) {
    const char *haystack = "hello world";
    
    TEST_ASSERT_NULL(strstr(haystack, "xyz"));
    TEST_ASSERT_NULL(strstr(haystack, "worlds"));
    TEST_ASSERT_NULL(strstr(haystack, "helloo"));
    TEST_ASSERT_NULL(strstr(haystack, "HELLO"));
}

void test_strstr_3(void) {
    const char *haystack = "hello world";
    
    TEST_ASSERT_EQUAL_STRING("hello world", strstr(haystack, ""));
    TEST_ASSERT_NULL(strstr("", "hello"));
    TEST_ASSERT_EQUAL_STRING("", strstr("", ""));
}

void test_strstr_4(void) {
    const char *haystack = "hello world";
    
    TEST_ASSERT_NULL(strstr(haystack, "hellx"));
    TEST_ASSERT_NULL(strstr(haystack, "world!"));
}

void test_strstr_5(void) {
    const char *haystack = "hello world, hello universe";
    
    TEST_ASSERT_EQUAL_STRING("hello world, hello universe", strstr(haystack, "hello"));
    TEST_ASSERT_EQUAL_STRING("lo world, hello universe", strstr(haystack, "lo"));
}

void test_strstr_6(void) {
    const char *str = "hello world";
    
    TEST_ASSERT_EQUAL_STRING("hello world", strstr(str, "hello world"));
    TEST_ASSERT_EQUAL_STRING("test", strstr("test", "test"));
}

void test_strstr_7(void) {
    const char *haystack = "ababab";
    
    TEST_ASSERT_EQUAL_STRING("ababab", strstr(haystack, "ab"));
    TEST_ASSERT_EQUAL_STRING("ababab", strstr(haystack, "abab"));
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strstr_1);
    RUN_TEST(test_strstr_2);
    RUN_TEST(test_strstr_3);
    RUN_TEST(test_strstr_4);
    RUN_TEST(test_strstr_5);
    RUN_TEST(test_strstr_6);
    RUN_TEST(test_strstr_7);

    return UNITY_END();
}