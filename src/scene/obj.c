
#include "obj.h"
#include "log.h"

static void obj_component_add_mi_malloc(obj_t *obj, component_t *cp) {

    if (obj->cap <= obj->len) {
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

static void obj_component_mi_free(obj_t *obj) {
    mi_free(obj->array);
    obj->cap = 0;
    obj->len = 0;
}

obj_t *panda_new_obj(pmem *pm) {

    obj_t *r = NULL;

    if (!pm) {
        r = mi_malloc(sizeof(obj_t));
    } else {
        r = pm->alloc(sizeof(obj_t), pm->_ptr);
    }

    if (!r)
        return NULL;

    r->array = NULL;
    r->cap = 0;
    r->len = 0;
    r->id = 0;
    r->name = NULL;

    return r;
}

void panda_set_obj_name(obj_t *obj, const char *name) {

    if (!obj)
        return;

    if (obj->name)
        mi_free(obj->name);

    obj->name = mi_strdup(name);
}

void panda_free_obj(pmem *pm, obj_t *obj) {

    if (!obj)
        return;

    mi_free(obj->name);

    if (!pm) {
        mi_free(obj);
        return;
    }

    pm->free(obj, pm->_ptr);
}

void panda_set_obj_id(obj_t *obj, const uint64_t id) {

    if (!obj)
        return;

    obj->id = id;
}

component_t *panda_new_component(pmem *pm) {

    component_t *r = NULL;
    if (!pm) {
        r = mi_malloc(sizeof(component_t));
    } else {
        r = pm->alloc(sizeof(component_t), pm->_ptr);
    }

    if (!r)
        return NULL;

    r->name = NULL;
    r->id = 0;
    r->type = 0;
    r->is_enable = 0;
    r->ptr = NULL;
    r->fn = NULL;

    return r;
}

void panda_set_component_name(component_t *component, const char *name) {

    if (!component)
        return;

    if (component->name)
        mi_free(component->name);

    component->name = mi_strdup(name);
}

void panda_free_component(pmem *pm, component_t *component) {

    if (!component)
        return;

    mi_free(component->name);

    if (!pm) {
        mi_free(component);
        return;
    }

    pm->free(component, pm->_ptr);
}

void panda_set_component_id(component_t *component, const uint64_t id) {

    if (!component)
        return;

    component->id = id;
}

void panda_obj_component_add(pmem *pm, obj_t *obj, component_t *cp) {

    if (!obj || !cp) {
        clog_error("obj_component_add: arg is null point!");
        return;
    }

    if (!pm) {
        obj_component_add_mi_malloc(obj, cp);
        return;
    }

    if (obj->cap <= obj->len) {
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

void panda_obj_component_free(pmem *pm, obj_t *obj) {

    if (!obj)
        return;

    if (!pm) {
        obj_component_mi_free(obj);
        return;
    }

    pm->free(obj->array, pm->_ptr);
    obj->cap = 0;
    obj->len = 0;
}
