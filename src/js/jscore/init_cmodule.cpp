
#include "init_cmodule.h"
#include "log.h"
#include "pmalloc.h"
#include <atomic>
#include <string.h>

std::atomic<cmodule_list_t *> cmodule_list{nullptr};
#define cl_load cmodule_list.load(std::memory_order_acquire)

void cmodule_list_free() {

    while (cl_load->len > 0) {
        cmodule_t *t = &cl_load->array[--cl_load->len];
        mi_free(t->name);
    }
    mi_free(cl_load->array);
    cl_load->array = nullptr;
    cl_load->cap = 0;
}

void cmodule_list_add(char *name, init_module_t fn) {

    if (!cl_load) {
        cmodule_list.store((cmodule_list_t *)mi_malloc(sizeof(cmodule_list_t)),
                           std::memory_order_release);
        cl_load->array = nullptr;
        cl_load->cap = 0;
        cl_load->len = 0;
    }

    if (cl_load->len >= cl_load->cap) {
        size_t newcap = cl_load->cap + (cl_load->cap >> 1) + 4;
        cmodule_t *a = (cmodule_t *)mi_realloc(
            cl_load->array, sizeof(cl_load->array[0]) * newcap);

        if (!a) {
            log_error("cmodule_list_add: realloc error", 0);
            return;
        }

        cl_load->array = a;
        cl_load->cap = newcap;
    }

    cl_load->array[cl_load->len].name = mi_strdup(name);
    cl_load->array[cl_load->len].fn = fn;
    ++cl_load->len;
}

JSModuleDef *panda_js_init_cmodule(JSContext *ctx, const char *cmodule_name) {
    log_debug("panda_js_init_cmodule:{%s}", cmodule_name);

    if (!cmodule_name) {
        log_error("cmodule_name is null", 0);
        return nullptr;
    }

    if (!strcmp(cmodule_name, "std")) {
        log_warn("js_init_module_std be call!", 0);
        return pjsc(js_init_module_std)(ctx, cmodule_name);
    }
    if (!strcmp(cmodule_name, "os")) {
        log_warn("js_init_module_os be call!", 0);
        return pjsc(js_init_module_os)(ctx, cmodule_name);
    }

    if (!cl_load) {
        log_error("cmodule_list is not initialized!", 0);
        return nullptr;
    }

    int size = cl_load->len;

    for (int i = 0; i < size; ++i) {
        if (!strcmp(cmodule_name, cl_load->array[i].name)) {
            return cl_load->array[i].fn(ctx, cmodule_name);
        }
    }

    log_error("no found cmodule:{%s}", cmodule_name);
    return nullptr;
}