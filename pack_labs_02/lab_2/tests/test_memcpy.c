#include "../include/functions.h"
#include <unity.h>


void setUp(void) {

}

void tearDown(void) {

}



void test_memcpy_1(void) {
    const char src[] = "Hello, World!";
    char dest[20];
    
    void* result = memcpy(dest, src, strlen(src) + 1); // +1 для нулевого терминатора
    
    TEST_ASSERT_EQUAL_PTR(dest, result);
    TEST_ASSERT_EQUAL_STRING(src, dest);
}
void test_memcpy_2(void) {
    const unsigned char src[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    unsigned char dest[5];
    
    memcpy(dest, src, sizeof(src));
    
    TEST_ASSERT_EQUAL_HEX8_ARRAY(src, dest, sizeof(src));
}
void test_memcpy_3(void) {
    const char src[] = "X";
    char dest = 'Y';
    
    memcpy(&dest, src, 1);
    
    TEST_ASSERT_EQUAL('X', dest);

}
void test_memcpy_4(void) {
    typedef struct {
        int id;
        char name[20];
        double score;
    } Student;
    
    Student src = {123, "John Doe", 95.5f};
    Student dest;
    
    memcpy(&dest, &src, sizeof(Student));
    
    TEST_ASSERT_EQUAL(src.id, dest.id);
    TEST_ASSERT_EQUAL_STRING(src.name, dest.name);
    TEST_ASSERT_EQUAL_FLOAT(src.score, dest.score);
}


int main(void) {
    UNITY_BEGIN();

    
    RUN_TEST(test_memcpy_1);
    RUN_TEST(test_memcpy_2);
    RUN_TEST(test_memcpy_3);
    RUN_TEST(test_memcpy_4);

    return UNITY_END();
}