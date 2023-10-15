
#include "level.h"

static void level_obj_mi_add(level_t *level, obj_t *obj) {

    if (level->cap <= level->len) {
        size_t new_cap = level->cap + (level->cap >> 1) + 4;

        obj_t *new_array = mi_realloc(level->array, sizeof(obj_t) * new_cap);

        if (!new_array) {
            // clog_error
            return;
        }

        level->array = new_array;
        level->cap = new_cap;
    }

    level->array[level->len] = *obj;
}

static void level_obj_mi_free(level_t *level) {

    mi_free(level->array);
    level->cap = 0;
    level->len = 0;
}

level_t *panda_new_level(pmem *pm) {

    level_t *r = NULL;

    if (!pm) {
        r = mi_malloc(sizeof(level_t));
    } else {
        r = pm->alloc(sizeof(level_t), pm->_ptr);
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

void panda_set_level_name(level_t *level, const char *name) {

    if (!level)
        return;

    if (level->name)
        mi_free(level->name);

    level->name = mi_strdup(name);
}

void panda_set_level_id(level_t *level, const uint64_t id) {

    if (!level)
        return;

    level->id = id;
}

void panda_free_level(pmem *pm, level_t *level) {

    if (!level)
        return;

    mi_free(level->name);

    if (!pm) {
        mi_free(level);
        return;
    }

    pm->free(level, pm->_ptr);
}

void panda_level_obj_add(pmem *pm, level_t *level, obj_t *obj) {

    if (!level || !obj) {
        //
        return;
    }

    if (!pm) {
        level_obj_mi_add(level, obj);
        return;
    }

    if (level->cap <= level->len) {
        size_t new_cap = level->cap + (level->cap >> 1) + 4;

        obj_t *new_array =
            pm->realloc(level->array, sizeof(obj_t) * new_cap, pm->_ptr);

        if (!new_array) {
            // clog_error
            return;
        }

        level->array = new_array;
        level->cap = new_cap;
    }

    level->array[level->len] = *obj;
}

void panda_level_obj_free(pmem *pm, level_t *level) {
    if (!level)
        return;

    if (!pm) {
        level_obj_mi_free(level);
        return;
    }

    pm->free(level->array, pm->_ptr);
    level->cap = 0;
    level->len = 0;
}