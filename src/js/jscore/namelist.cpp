
#include "jsc.h"
#include "log.h"

#include <pmalloc.h>

void namelist_add(namelist_t *lp, const char *name, const char *short_name, int flags) {

    namelist_entry_t *e;
    if (lp->count == lp->size) {
        size_t newsize = lp->size + (lp->size >> 1) + 4;
        namelist_entry_t *a = 
                    (namelist_entry_t *)mi_realloc(lp->array, sizeof(lp->array[0]) * newsize);
        if(!a) {

        }
        lp->array = a;
        lp->size = newsize;
    }
    e =  &lp->array[lp->count++];
    e->name = mi_strdup(name);
    if (short_name) {
        e->short_name = mi_strdup(short_name);
    }
    else {
        e->short_name = nullptr;
    }
    e->flags = flags;
}

void namelist_free(namelist_t *lp) {

    while (lp->count > 0) {
        namelist_entry_t *e = &lp->array[--lp->count];
        mi_free(e->name);
        mi_free(e->short_name);
    }
    mi_free(lp->array);
    lp->array = nullptr;
    lp->size = 0;
}

namelist_entry_t *namelist_find(namelist_t *lp, const char *name) {
    int i;
    for(i = 0; i < lp->count; i++) {
        namelist_entry_t *e = &lp->array[i];
        if (!strcmp(e->name, name)) return e;
    }
    return nullptr;
}

void namelist_init_add_cmoudule(namelist_t * n) {
    namelist_add(n, "std", "std", 0);
    namelist_add(n, "os", "os", 0);
}