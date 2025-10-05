#include "../include/functions.h"
#include <unity.h>

void setUp(void) {

}

void tearDown(void) {

}


void test_strpbrk_1(void) {
    const char *str = "hello world";
    
    TEST_ASSERT_EQUAL_STRING("ello world", strpbrk(str, "aeiou"));
    TEST_ASSERT_EQUAL_STRING("world", strpbrk(str, "wxyz"));
    TEST_ASSERT_EQUAL_STRING("llo world", strpbrk(str, "lmn"));
}
void test_strpbrk_2(void) {
    const char *str = "hello world";
    
    TEST_ASSERT_NULL(strpbrk(str, "xyz"));
    TEST_ASSERT_NULL(strpbrk(str, "ABC"));
    TEST_ASSERT_NULL(strpbrk(str, "123"));
}
void test_strpbrk_3(void) {
    const char *str = "hello world";
    
    TEST_ASSERT_NULL(strpbrk(str, ""));
    TEST_ASSERT_NULL(strpbrk("", "abc"));
    TEST_ASSERT_NULL(strpbrk("", ""));
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strpbrk_1);
    RUN_TEST(test_strpbrk_2);
    RUN_TEST(test_strpbrk_3);


    return UNITY_END();
}

