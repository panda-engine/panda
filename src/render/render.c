
#include "render/inc/render.h"

void panda_process_render(void *ptr) {

    render_t *render = ptr;

    if (!render->mesh_id || !render->shader_id || !render->transform_id) {
        return;
    }

    //
}