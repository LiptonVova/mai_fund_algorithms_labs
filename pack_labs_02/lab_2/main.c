// #include "include/functions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char dest[10];
    dest[0] = '\0';
    char src[] = "klngeknmgemgmejjjjjjjmgme";
    strncat(dest, src, 20);
    printf("%s\n", dest);

    return 0;
}