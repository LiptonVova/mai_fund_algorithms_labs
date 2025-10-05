#include "../include/functions.h"
#include "../include/macros_for_errno.h"

void* memchr(const void* str, int c, size_t n) {
    const unsigned char* copy_str = (unsigned char*)str;
    const char* ptr_c = NULL; // указатель на первое вхождение c  
    const unsigned char char_c = (unsigned char)c;  
    for (size_t i = 0; i < n; ++i) {
        if (copy_str[i] == char_c) {
            ptr_c = copy_str + i;
            break;
        }        
    }
    return (void*)ptr_c;    
}

int memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char* char_str1 = (unsigned char*)str1;
    const unsigned char* char_str2 = (unsigned char*)str2;

    for (size_t i = 0; i < n; ++i) {
        if (char_str1[i] < char_str2[i]) {
            return -1;
        }
        else if (char_str1[i] > char_str2[i]) {
            return 1;
        }
    }

    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char* char_dest = (unsigned char*)dest;
    unsigned const char* char_src = (unsigned char*)src; 

    for (size_t i = 0; i < n; ++i) {
        char_dest[i] = char_src[i];
    }
    dest = (void*)char_dest;
    return dest;
}


void *memset(void *str, int c, size_t n) {
    const unsigned char char_c = (unsigned char)c;
    unsigned char* char_str = (unsigned char*)str;

    for (size_t i = 0; i < n; ++i) {
        char_str[i] = char_c;
    }

    str = (void*)char_str;
    return str;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t len = strlen(dest);
    size_t len_src = strlen(src);
    size_t i = 0;
    for ( ; i < n && i < len_src; ++i) {
        dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
    return dest;
}

char *strchr(const char *str, int c) {
    const unsigned char char_c = (unsigned char)c;
    size_t n = strlen(str);
    for (size_t i = 0; i < n; ++i) {
        if (str[i] == char_c) {
            return (char*)(str + i); 
        }
    }

    if (char_c == '\0') {
        return (char*)(str + n);
    }

    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    size_t len_str1 = strlen(str1) + 1; // для обработки терминирующего нуля
    const size_t len_str2 = strlen(str2) + 1;  

    if (len_str2 < len_str1) {
        len_str1 = len_str2;
    }

    for (size_t i = 0; i < len_str1 && i < n; ++i) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
    }

    return 0;
}

char *strncpy(char *dest, const char *src, size_t n) {
    // терминирующий ноль в любом случае ставится на позицию n (в 0 индексации)
    // поэтому программисту, который вызывает мою функцию, надо гарантировать, что для dest выделено (n + 1) памяти
    size_t i = 0;
    for ( ; i < n && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }

    for ( ; i < n; ++i) { // в случае, если strlen(src) < n
        dest[i] = '\0';
    }
    dest[n] = '\0';

    return dest;
}

size_t strcspn(const char *str1, const char *str2) {
    const size_t len_str1 = strlen(str1);
    const size_t len_str2 = strlen(str2);
    size_t i = 0;
    for ( ; i < len_str1; ++i) {
        const char c = str1[i];
        for (size_t j = 0; j < len_str2; ++j) {
            if (c == str2[j]) {
                return i;
            }
        }
    }
    return (size_t)len_str1;
}

char *strerror(int errnum) {
    const char* error_messages[] = ERROR_MESSAGES;

    #ifdef __APPLE__
        #define MAX_ERRNO 107
    #elif __linux__ 
        #define MAX_ERRNO 133
    #endif

    if (errnum < 0 || errnum > MAX_ERRNO) {
        return "Unknown error";
    }

    const char *msg = error_messages[errnum];
    return (char*)msg;
}


size_t strlen(const char *str) {
    size_t i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *strpbrk(const char *str1, const char *str2) {
    const size_t len_str1 = strlen(str1);
    const size_t len_str2 = strlen(str2);

    char c = '\0';
    for (size_t i = 0; i < len_str1; ++i) {
        c = str1[i];
        for (size_t j = 0; j < len_str2; ++j) {
            if (str2[j] == c) {
                return (char*)(str1 + i);
            }
        } 
    }

    return NULL;
}

char *strrchr(const char *str, int c) {
    const size_t len = strlen(str);

    for (size_t i = len; i > 0; ) {
        size_t j = --i;

        if (str[j] == c) {
            return (char*)(str + j);
        }
    }
    return NULL;
}

char *strstr(const char *haystack, const char *needle) {
    const size_t n = strlen(haystack);
    const size_t m = strlen(needle);

    int flag = 1;

    for (size_t i = 0; i < n; ++i) {
        flag = 1;
        size_t j = 0;
        for ( ; j < m; ++j) {
            if (i + j >= n) {
                flag = 0;
                break;
            }
            if (haystack[i + j] != needle[j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return (char*)(haystack + i);
        }
    }
    return NULL;
}


int is_delim(const char c, const char*delim) {
    size_t len = strlen(delim);
    for (size_t i = 0; i < len; ++i) {
        if (c == delim[i]) {
            return  1;
        }
    }
    return 0;
}


char *strtok(char *str, const char *delim) {
    static char* save_str = NULL;
    
    if (str == NULL) {
        str = save_str;
        if (str == NULL) {
            return NULL;
        }
    }

    while (*str != '\0' && is_delim(*str, delim)) {
        str++;
    }

    if (*str == '\0') {
        save_str = NULL;
        return NULL;
    }

    char * token = str;
    while (*str != '\0' && !is_delim(*str, delim)) {
        str++;
    }

    if (*str == '\0') {
        save_str = NULL;
    } 
    else {
        *str = '\0';
        save_str = str + 1;
    }

    return token;
}