/*
 * panda-jsc
 *
 */
#include <cassert>
#include <cstring>

#include "jsc.h"
#include "log.h"

static void to_bytecode(JSContext *ctx, JSValueConst obj, panda_js_bc *jsc_b,
                        BOOL load_only) {
    log_debug("to_bytecode", 0);
    uint8_t *bytecode_buf;
    size_t bytecode_buf_len;
    int flags;
    flags = JS_WRITE_OBJ_BYTECODE;
    if (jsc_b->byte_swap)
        flags |= JS_WRITE_OBJ_BSWAP;
    bytecode_buf = pjsc(JS_WriteObject)(ctx, &bytecode_buf_len, obj, flags);

    if (!bytecode_buf) {
        log_error("JS_WriteObject return nullptr", 0);
        return;
    }

    jsc_b->bytecode_len = bytecode_buf_len;
    jsc_b->bytecode = bytecode_buf;
}

static int js_module_dummy_init(JSContext *ctx, JSModuleDef *m) {
    log_error("should never be called when compiling JS code", 0);
    return -1;
}

static JSModuleDef *jsc_module_loader(JSContext *ctx, const char *module_name,
                                      void *opaque) {
    log_debug("jsc_module_loader modulename:{%s}", module_name);
    JSModuleDef *m;
    char *find_buf;
    panda_js_bc *jsc_b = (panda_js_bc *)opaque;

    find_buf = namelist_find(jsc_b->cmodule_list, module_name);
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

        while (jsc_b->next != nullptr) {
            jsc_b = jsc_b->next;
        }
        jsc_b->next = panda_new_js_bc(ctx);
        to_bytecode(ctx, func_val, jsc_b->next, TRUE);

        /* the module is already referenced, so we must free it */
        m = (JSModuleDef *)JS_VALUE_GET_PTR(func_val);
        JS_FreeValue(ctx, func_val);
    }
    return m;
}

static void compile_file(JSContext *ctx, panda_js_bc *jsc_b,
                         const char *filename) {
    log_debug("complie_file_tobc", 0);
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

    to_bytecode(ctx, obj, jsc_b, FALSE);
    JS_FreeValue(ctx, obj);
}

panda_js_bc *panda_new_js_bc(JSContext *ctx) {
    log_debug("panda_new_js_bc", 0);
    panda_js_bc *r = (panda_js_bc *)pjsc(js_malloc)(ctx, sizeof(panda_js_bc));
    if (!r) {
        log_error("Cannot apply for memory", 0);
        return nullptr;
    }
    r->byte_swap = FALSE;
    r->bytecode = nullptr;
    r->bytecode_len = 0;
    r->cmodule_list = (namelist_t *)pjsc(js_malloc)(ctx, sizeof(namelist_t));
    r->cmodule_list->name_array = nullptr;
    r->cmodule_list->len = 0;
    r->cmodule_list->cap = 0;
    r->next = nullptr;
    return r;
}

void panda_free_js_bc(JSContext *ctx, panda_js_bc *ptr) {
    if (ptr == nullptr)
        return;
    log_debug("panda_free_js_bc", 0);
    namelist_free(ptr->cmodule_list);
    pjsc(js_free)(ctx, ptr->cmodule_list);
    pjsc(js_free)(ctx, ptr->bytecode);
    panda_free_js_bc(ctx, ptr->next);
    pjsc(js_free)(ctx, ptr);
}

panda_js_bc *panda_js_toBytecode(JSRuntime *rt, JSContext *ctx,
                                 const char *filename) {
    log_debug("panda_js_toBytecode filename: {%d}", filename);
    panda_js_bc *jsc_b = panda_new_js_bc(ctx);

    if (!jsc_b) {
        return nullptr;
    }

    namelist_add_cmodule(jsc_b->cmodule_list);
    pjsc(JS_SetModuleLoaderFunc)(rt, nullptr, jsc_module_loader, jsc_b);
    compile_file(ctx, jsc_b, filename);

    return jsc_b;
}
