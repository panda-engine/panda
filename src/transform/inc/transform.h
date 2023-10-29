
#ifndef panda_transform_h_
#define panda_transform_h_

// #include "transform.h"
#include "pmem/inc/pmem.h"

// #include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    union {
        struct {
            float x, y, z, w;
        };
        float m[4];
    };
    float t[4][4];
    int can_move;
} transform_t;

// transform fn
transform_t *panda_new_transform(pmem *pm);
// m is x, y, z, w
void panda_set_transform_m(transform_t *transform, const float *m);
// t is t[4][4]
void panda_set_transform_t(transform_t *transform, const float **t);
void panda_set_transform_canmove(transform_t *transform, const int can_move);

void panda_free_transform(pmem *pm, transform_t *transform);

#ifdef __cplusplus
}
#endif

#endif
