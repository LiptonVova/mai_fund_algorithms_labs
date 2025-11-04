#include <stdio.h>
#include <string.h>
#include "include/binary_heap.h"


typedef struct {
    int id;
    char surname[100];
} Student;

void delete_student(Student s) {

}

Student copy_student(const Student s) {
    Student new_student;
    new_student.id = s.id;
    strcpy(new_student.surname, s.surname);
    return new_student;
}

int comp_student(Student s1, Student s2) {
    // Сравниваем по ID
    if (s1.id < s2.id) return -1;
    if (s1.id > s2.id) return 1;
    return 0;
}

Student default_student() {
    Student s = {0, ""};
    return s;
}

void swap_student(Student* s1, Student* s2) {
    Student temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

DEFINE_BINARY_MIN_HEAP(Student)

void print_student(Student s) {
    printf("Student{id: %d, surname: %s}", s.id, s.surname);
}

int main() {
    printf("\n=== ДЕМОНСТРАЦИЯ ДЛЯ Student ===\n");
    
    Heap_Student heap = create_heap_Student(5, delete_student, copy_student, comp_student, default_student, swap_student);
    
    Student students[] = {
        {103, "Ivanov"},
        {101, "Petrov"},
        {105, "Sidorov"},
        {100, "Kuznetsov"},
        {102, "Smirnov"}
    };
    
    printf("Добавляем студентов:\n");
    for (int i = 0; i < 5; i++) {
        push_heap_Student(&heap, students[i]);
        print_student(students[i]);
        printf(" ");
    }
    printf("\n");
    
    printf("Размер кучи: %zu\n", size_heap_Student(&heap));
    printf("Студент с минимальным ID: ");
    print_student(peek_heap_Student(&heap));
    printf("\n");
    
    printf("\nИзвлекаем студентов в порядке возрастания ID:\n");
    while (!is_empty_heap_Student(&heap)) {
        Student s = pop_heap_Student(&heap);
        print_student(s);
        printf(" ");
    }
    printf("\n");
    
    delete_heap_Student(&heap);
    return 0;
}