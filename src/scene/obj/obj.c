
#include "obj/obj.h"
#include "log.h"

static void obj_component_add_mi_malloc(obj_t *obj, component_t *cp) {
    if (obj->cap >= obj->len) {
        size_t new_cap = obj->cap + (obj->cap >> 1) + 4;

        component_t *new_array =
            mi_realloc(obj->array, sizeof(component_t) * new_cap);

        if (!new_array) {
            clog_error("apply mem error");
            return;
        }

        obj->array = new_array;
        obj->cap = new_cap;
    }

    obj->array[obj->len++] = *cp;
}

void obj_component_add(pmem *pm, obj_t *obj, component_t *cp) {

    if (!obj || !cp) {
        clog_error("obj_component_add: arg is null point!");
        return;
    }

    if (!pm) {
        obj_component_add_mi_malloc(obj, cp);
        return;
    }

    if (obj->cap >= obj->len) {
        size_t new_cap = obj->cap + (obj->cap >> 1) + 4;

        component_t *new_array =
            pm->realloc(obj->array, sizeof(component_t) * new_cap, pm->_ptr);

        if (!new_array) {
            clog_error("obj_component_add: apply mem error");
            return;
        }

        obj->array = new_array;
        obj->cap = new_cap;
    }

    obj->array[obj->len++] = *cp;
}

void obj_component_free(pmem *pm, obj_t *obj) {
    if (!obj)
        return;

    if (!pm) {
    }

    while (obj->len > 0) {
        component_t *p = &obj->array[--obj->len];
    }
}
