#include "../include/functions.h"
#include <unity.h>

void setUp(void) {

}

void tearDown(void) {

}

void test_strrchr_1(void) {
    const char *str = "hello world";
    
    TEST_ASSERT_EQUAL_STRING("orld", strrchr(str, 'o'));
    TEST_ASSERT_EQUAL_STRING("d", strrchr(str, 'd'));
    TEST_ASSERT_EQUAL_STRING("ld", strrchr(str, 'l'));
}
void test_strrchr_2(void) {
    const char *str = "hello world";
    
    TEST_ASSERT_NULL(strrchr(str, 'x'));
    TEST_ASSERT_NULL(strrchr(str, 'A'));
    TEST_ASSERT_NULL(strrchr(str, '0'));
}
void test_strrchr_3(void) {
    const char *str = "unique";
    
    TEST_ASSERT_EQUAL_STRING("ue", strrchr(str, 'u'));
    TEST_ASSERT_EQUAL_STRING("e", strrchr(str, 'e'));
    TEST_ASSERT_EQUAL_STRING("nique", strrchr(str, 'n'));
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strrchr_1);
    RUN_TEST(test_strrchr_2);
    RUN_TEST(test_strrchr_3);

    return UNITY_END();
}
