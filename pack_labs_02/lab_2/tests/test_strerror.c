#include "../include/functions.h"
#include <unity.h>
#include <errno.h>

void setUp(void) {

}

void tearDown(void) {

}

void test_strerror_1(void) {
    TEST_ASSERT_EQUAL_STRING("Success", strerror(0));
    TEST_ASSERT_EQUAL_STRING("Operation not permitted", strerror(EPERM));
    TEST_ASSERT_EQUAL_STRING("No such file or directory", strerror(ENOENT));
    TEST_ASSERT_EQUAL_STRING("No such process", strerror(ESRCH));
    TEST_ASSERT_EQUAL_STRING("Bad file descriptor", strerror(EBADF));
    TEST_ASSERT_EQUAL_STRING("Cannot allocate memory", strerror(ENOMEM));
    TEST_ASSERT_EQUAL_STRING("Permission denied", strerror(EACCES));
    TEST_ASSERT_EQUAL_STRING("Bad address", strerror(EFAULT));
    TEST_ASSERT_EQUAL_STRING("Invalid argument", strerror(EINVAL));
    TEST_ASSERT_EQUAL_STRING("Too many open files", strerror(EMFILE));
    TEST_ASSERT_EQUAL_STRING("Broken pipe", strerror(EPIPE));
    TEST_ASSERT_EQUAL_STRING("Connection refused", strerror(ECONNREFUSED));
}

void test_strerror_2(void) {
    TEST_ASSERT_EQUAL_STRING("Unknown error", strerror(-1));
    TEST_ASSERT_EQUAL_STRING("Unknown error", strerror(-100));
    
    TEST_ASSERT_EQUAL_STRING("Unknown error", strerror(9999));
    TEST_ASSERT_EQUAL_STRING("Unknown error", strerror(10000));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_strerror_1);
    RUN_TEST(test_strerror_2);

    return UNITY_END();
}