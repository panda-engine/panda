

#include "ffi/ffi.h"
#include "js_init.h"
#include "jscore/jsc.h"
#include "load_dynamic.h"
#include "log.h"
#include "pmalloc.h"
#include <stdio.h>

std::atomic<cmodule_list_t *> cmodule_list{nullptr};
#define cl_load cmodule_list.load(std::memory_order_acquire)
#define MAX_NAME 128

void cmodule_list_free() {

    if (cl_load == nullptr) 
        return;
    while (cl_load->len > 0) {
        cmodule_t *t = &cl_load->array[--cl_load->len];
        mi_free(t->name);
    }
    mi_free(cl_load->array);
    cl_load->array = nullptr;
    cl_load->cap = 0;
}

void cmodule_list_add(const char *name, ffi_cmodule_t fn) {

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

void panda_js_init_ffi() { cmodule_list_add("ffi", js_init_module_ffi); }

void panda_js_free_ffi() {
    cmodule_list_free();
    mi_free((void *)cl_load);
    lib_list_free();
}

static ffi_cmodule_t ffi_call_init_cmodule(const char *cmodule_name) {
    return load_dynamic(cmodule_name, "js_init_module");
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

    if (has_suffix(cmodule_name, p_suffix)) {
        char module_name[MAX_NAME];
        int module_len = strlen(cmodule_name) - strlen(p_suffix);

        if (module_len > 127) {
            log_error("module_name too len (< 128)\nname:%s", cmodule_name);
            return nullptr;
        }
        int pos = 0;
        for (int i = 0; i < module_len; ++i) {
            if(cmodule_name[i] == '\\' or cmodule_name[i] == '/')
                pos = i;
        }
        snprintf(module_name, MAX_NAME - 1, "%.*s", module_len - pos - 1, cmodule_name + pos + 1);
        // printf("name:%s\n", cmodule_name);
        // printf("name:%s\n", module_name);
        ffi_cmodule_t fn = ffi_call_init_cmodule(cmodule_name);

        if(fn == nullptr)
            return nullptr;

        return fn(ctx, module_name);
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
