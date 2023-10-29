

#include "id/inc/id.h"
#include "log/src/log.h"

#include <mimalloc.h>

id_list_t *panda_new_id_list() {
    id_list_t *r = mi_malloc(sizeof(id_list_t));

    if (!r)
        return NULL;

    r->name = NULL;
    r->ctx_list = NULL;
    r->ctx_cnt = 0;
    r->cap = 0;
    r->len = 0;

    return r;
}

void panda_free_id_list(id_list_t *id_list) {
    if (!id_list)
        return;

    mi_free(id_list->name);
    mi_free(id_list->ctx_list);
    mi_free(id_list);
}

uint64_t panda_add_id(id_list_t *id_list, void *ctx, ctx_type type) {
    if (!id_list)
        return 0;

    if (id_list->len >= id_list->cap) {
        size_t new_cap = id_list->cap + (id_list->cap >> 1) + 4;

        ctx_t *new_array =
            mi_realloc(id_list->ctx_list, sizeof(ctx_t) * new_cap);

        if (!new_array) {
            log_error("apply mem error");
            return 0;
        }

        id_list->ctx_list = new_array;
        id_list->cap = new_cap;
    }

    id_list->ctx_list[id_list->len].type = type;
    id_list->ctx_list[id_list->len].ctx = ctx;
    id_list->len++;

    return id_list->len - 1;
}

void panda_set_id_list_name(id_list_t *id_list, const char *name) {
    if (!id_list)
        return;

    if (id_list->name)
        mi_free(id_list->name);

    id_list->name = mi_strdup(name);
}

ctx_t *panda_get_ctx_by_id(id_list_t *id_list, uint64_t id) {
    if (!id_list)
        return NULL;

    if (id_list->len <= id)
        return NULL;

    return id_list->ctx_list + id;
}