
#include "render.h"

void panda_process_render(void *ptr) {

    render_t *render = (render_t *)ptr;

    if (!render->mesh_id || !render->shader_id || !render->transform_id) {
        return;
    }

    //
}