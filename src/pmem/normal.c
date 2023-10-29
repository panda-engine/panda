
#ifdef PMEM_DEBUG
#include "log/src/log.h"
#endif
#include "pmem/inc/pmem.h"

#include <mimalloc.h>
#include <sys/stat.h>

static void *_malloc(size_t size, void *_ptr) { return mi_malloc(size); }

static void *_realloc(void *ptr, size_t newsize, void *_ptr) {
    return mi_realloc(ptr, newsize);
}

static size_t _usable_size(const void *ptr, void *_ptr) {
    return mi_usable_size(ptr);
}

static void _free(void *ptr, void *_ptr) { return mi_free(ptr); }

void pmem_new_normal(pmem *p) {
    if (!p)
        return;

    p->type = normal;
    p->_ptr = NULL;
    p->alloc = _malloc;
    p->free = _free;
    p->realloc = _realloc;
    p->usable_size = _usable_size;
}

void pmem_free_normal(pmem *ptr) {
#ifdef PMEM_DEBUG
    log_info("pmem_free_alloc");
#endif

    mi_free(ptr);
    ptr = NULL;
}