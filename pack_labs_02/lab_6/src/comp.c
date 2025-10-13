#include "../include/comp.h"


int comp_id(const void *void_student_1, const void *void_student_2) {
    const Student* student_1 = *(const Student**)void_student_1;
    const Student* student_2 = *(const Student**)void_student_2;
    if (student_1->id < student_2->id) {
        return -1;
    }
    else if (student_1->id == student_2->id) {
        return 0;
    }
    return 1;
}

int comp_surname(const void *void_student_1, const void *void_student_2) {
    const Student* student_1 = *(const Student**)void_student_1;
    const Student* student_2 = *(const Student**)void_student_2;
    return strcmp(student_1->surname, student_2->surname);
}
int comp_name(const void *void_student_1, const void *void_student_2) {
    const Student* student_1 = *(const Student**)void_student_1;
    const Student* student_2 = *(const Student**)void_student_2;
    return strcmp(student_1->name, student_2->name);
}
int comp_group(const void *void_student_1, const void *void_student_2){
    const Student* student_1 = *(const Student**)void_student_1;
    const Student* student_2 = *(const Student**)void_student_2;
    return strcmp(student_1->group, student_2->group);  
}
