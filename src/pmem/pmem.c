

#include "pmem/inc/pmem.h"

#include <mimalloc.h>

extern void pmem_free_normal(pmem *ptr);

void pmem_free_alloc(pmem *ptr) {
#ifdef PMEM_DEBUG
    // LOG_F(INFO, "pmem_free_alloc");
#endif
    pmem_free_normal(ptr);
}

extern void pmem_new_normal(pmem *p);

pmem *pmem_new_alloc(size_t size, pmem_t type, void *_ptr) {
    pmem *r = (pmem *)mi_malloc(sizeof(pmem));
    if (type == normal) {
#ifdef PMEM_DEBUG
        LOG_F(INFO, "pmem_new_alloc: normal");
#endif
        pmem_new_normal(r);
    } else {
        // LOG_F(ERROR, "not support this type:{%d}", type);
        mi_free(r);
        return NULL;
    }

    return r;
}
