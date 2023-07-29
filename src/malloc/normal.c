
#include "log.h"
#include "pmalloc.h"


#include <mimalloc.h>

void pmem_free_alloc(pmem *ptr) { mi_free(ptr); }

pmem *pmem_new_alloc(size_t size, pmem_t type) {
    pmem *r = mi_malloc(sizeof(pmem));
    if (type == normal) {
        r->alloc = mi_malloc;
        r->realloc = mi_realloc;
        r->usable_size = mi_usable_size;
        r->free = mi_free;
    } else {
        clog_error("not support this type:{%d}", type);
        mi_free(r);
        return NULL;
    }

    return r;
}