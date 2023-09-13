

#ifndef panda_render_h_
#define panda_render_h_

#include <stdint.h>

#include "pmalloc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t transform_id;
    uint64_t mesh_id;
    uint64_t shader_id;
} render_t;

render_t *panda_new_render(pmem *pm);

void panda_set_render_id(render_t *render, uint64_t transform_id,
                         uint64_t mesh_id, uint64_t shader_id);

void panda_free_render(pmem *pm, render_t *render);

void panda_process_render(void *ptr);

#ifdef __cplusplus
}
#endif

#endif