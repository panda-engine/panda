
#include "transform/inc/transform.h"

#include <mimalloc.h>

transform_t *panda_new_transform(pmem *pm) {
    transform_t *r = NULL;

    if (!pm) {
        r = mi_malloc(sizeof(transform_t));
    } else {
        r = pm->alloc(sizeof(transform_t), pm->_ptr);
    }

    if (!r)
        return NULL;

    for (int i = 0; i < 4; ++i)
        r->m[i] = 0.0f;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            r->t[i][j] = 0;

    r->can_move = 0;

    return r;
}

void panda_set_transform_m(transform_t *transform, const float *m) {

    if (!transform)
        return;

    for (int i = 0; i < 4; ++i)
        transform->m[i] = m[i];
}

void panda_set_transform_t(transform_t *transform, const float **t) {

    if (!transform)
        return;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            transform->t[i][j] = t[i][j];
}

void panda_set_transform_canmove(transform_t *transform, const int can_move) {
    if (!transform)
        return;

    transform->can_move = can_move;
}

void panda_free_transform(pmem *pm, transform_t *transform) {

    if (!transform)
        return;

    if (!pm) {
        mi_free(transform);
        return;
    }

    pm->free(transform, pm->_ptr);
}