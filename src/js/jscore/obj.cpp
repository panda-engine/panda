
#include "jsc.h"
#include "log.h"
#include <cstring>

static int js_module_dummy_init(JSContext *ctx, JSModuleDef *m) {
    log_error("should never be called when compiling JS code", 0);
    return -1;
}

static JSModuleDef *jsc_module_loader(JSContext *ctx, const char *module_name,
                                      void *opaque) {
    log_debug("jsc_module_loader modulename:{%s}", module_name);
    JSModuleDef *m;
    char *find_buf;
    panda_js_obj *jsc_o = (panda_js_obj *)opaque;

    /* check if it is a declared C or system module */
    find_buf = namelist_find(jsc_o->cmodule_list, module_name);
    if (find_buf) {

        m = panda_js_init_cmodule(ctx, find_buf);

    } else if (has_suffix(module_name, ".so") ||
               has_suffix(module_name, ".dll")) {

        log_warn("binary module will be dynamically loaded", 0);
        /* create a dummy module */
        m = pjsc(JS_NewCModule)(ctx, module_name, js_module_dummy_init);

    } else {

        size_t buf_len;
        uint8_t *buf;
        JSValue func_val;

        if (has_suffix(module_name, ".js")) {
            buf = pjsc(js_load_file)(ctx, &buf_len, module_name);
        } else {
            size_t len = strlen(module_name);
            char *module_name_buf = (char *)pjsc(js_malloc)(ctx, len + 4);
            memcpy(module_name_buf, module_name, len);
            snprintf(module_name_buf, len + 4, "%s.js", module_name);
            buf = pjsc(js_load_file)(ctx, &buf_len, module_name_buf);
            pjsc(js_free)(ctx, module_name_buf);
        }
        if (!buf) {
            log_error("could not load module filename '%s'", module_name);
            return nullptr;
        }

        /* compile the module */
        func_val =
            pjsc(JS_Eval)(ctx, (char *)buf, buf_len, module_name,
                          JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
        pjsc(js_free)(ctx, buf);

        if (JS_IsException(func_val)) {
            log_error("eval error", 0);
            pjsc(js_std_dump_error)(ctx);
            return nullptr;
        }

        while (jsc_o->next != nullptr) {
            jsc_o = jsc_o->next;
        }
        jsc_o->next = panda_new_js_obj(ctx);
        jsc_o->obj = func_val;

        /* the module is already referenced, so we must free it */
        m = (JSModuleDef *)JS_VALUE_GET_PTR(func_val);
    }
    return m;
}

static void compile_file(JSContext *ctx, panda_js_obj *jsc_o,
                         const char *filename) {
    log_debug("complie_file_toobj", 0);
    uint8_t *buf;
    int eval_flags;
    JSValue obj;
    size_t buf_len;

    buf = pjsc(js_load_file)(ctx, &buf_len, filename);
    if (!buf) {
        log_error("Could not load '%s'\n", filename);
        return;
    }
    eval_flags = JS_EVAL_FLAG_COMPILE_ONLY;
    int module = pjsc(JS_DetectModule)((const char *)buf, buf_len);

    if (module)
        eval_flags |= JS_EVAL_TYPE_MODULE;
    else
        eval_flags |= JS_EVAL_TYPE_GLOBAL;

    obj = pjsc(JS_Eval)(ctx, (const char *)buf, buf_len, filename, eval_flags);
    pjsc(js_free)(ctx, buf);

    if (JS_IsException(obj)) {
        log_error("eval error", 0);
        pjsc(js_std_dump_error)(ctx);
        return;
    }

    jsc_o->obj = obj;
}

panda_js_obj *panda_new_js_obj(JSContext *ctx) {
    log_debug("panda_new_js_obj", 0);
    panda_js_obj *r =
        (panda_js_obj *)pjsc(js_malloc)(ctx, sizeof(panda_js_obj));
    if (!r) {
        log_error("Cannot apply for memory", 0);
        return nullptr;
    }
    r->byte_swap = FALSE;
    r->cmodule_list = (namelist_t *)pjsc(js_malloc)(ctx, sizeof(namelist_t));
    r->cmodule_list->name_array = nullptr;
    r->cmodule_list->len = 0;
    r->cmodule_list->cap = 0;
    r->next = nullptr;
    return r;
}

void panda_free_js_obj(JSContext *ctx, panda_js_obj *ptr) {
    if (ptr == nullptr)
        return;
    log_debug("panda_free_js_obj", 0);
    namelist_free(ptr->cmodule_list);
    pjsc(js_free)(ctx, ptr->cmodule_list);
    panda_free_js_obj(ctx, ptr->next);
    pjsc(js_free)(ctx, ptr);
}

panda_js_obj *panda_js_toObj(JSRuntime *rt, JSContext *ctx,
                             const char *filename) {
    log_debug("panda_js_toObj filename: {%s}", filename);
    panda_js_obj *jsc_o = panda_new_js_obj(ctx);

    if (!jsc_o) {
        return nullptr;
    }

    namelist_add_cmodule(jsc_o->cmodule_list);
    pjsc(JS_SetModuleLoaderFunc)(rt, nullptr, jsc_module_loader, jsc_o);
    compile_file(ctx, jsc_o, filename);

    return jsc_o;
}
