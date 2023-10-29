

#include "render/inc/render.h"

#include <mimalloc.h>

render_t *panda_new_render(pmem *pm) {

    render_t *r = NULL;

    if (!pm) {
        r = mi_malloc(sizeof(render_t));
    } else {
        r = pm->alloc(sizeof(render_t), pm->_ptr);
    }

    if (!r)
        return NULL;

    r->mesh_id = 0;
    r->shader_id = 0;
    r->transform_id = 0;

    return r;
}

void panda_set_render_id(render_t *render, uint64_t transform_id,
                         uint64_t mesh_id, uint64_t shader_id) {
    if (!render)
        return;

    render->mesh_id = mesh_id;
    render->shader_id = shader_id;
    render->transform_id = transform_id;
}

void panda_free_render(pmem *pm, render_t *render) {

    if (!render)
        return;

    if (!pm) {
        mi_free(render);
        return;
    }

    pm->free(render, pm->_ptr);
}