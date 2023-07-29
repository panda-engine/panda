
#include "pmalloc.h"
#include <stdio.h>

int main() {
    pmem *p = pmem_new_alloc(0, normal);

    char *str = p->alloc(sizeof(char) * 20);
    str[0] = '9';
    str[5] = '\0';
    printf("%s", str);

    p->free(str);

    pmem_free_alloc(p);
}