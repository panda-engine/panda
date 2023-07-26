
#include "jsc.h"
#include "log.h"
#include <cstring>

static int js_module_dummy_init(JSContext *ctx, JSModuleDef *m) {
    /* should never be called when compiling JS code */
    abort();
}

static JSModuleDef *jsc_module_loader(JSContext *ctx,
                              const char *module_name, void *opaque) {
    JSModuleDef *m;
    namelist_entry_t *e;
    panda_js_obj * jsc_o = (panda_js_obj *)opaque;

    /* check if it is a declared C or system module */
    e = namelist_find(jsc_o->cmodule_list, module_name);
    if (e) {
        /* add in the static init module list */
        namelist_add(jsc_o->init_module_list, e->name, e->short_name, 0);
        /* create a dummy module */
        m = pjsc(JS_NewCModule)(ctx, module_name, js_module_dummy_init);
    } else if (has_suffix(module_name, ".so") || has_suffix(module_name, ".dll")) {
        panda_log.warn("Warning: binary module '%s' will be dynamically loaded\n", module_name);
        /* create a dummy module */
        m = pjsc(JS_NewCModule)(ctx, module_name, js_module_dummy_init);
        /* the resulting executable will export its symbols for the
           dynamic library */
    } else {
        size_t buf_len;
        uint8_t *buf;
        JSValue func_val;
        
        if (has_suffix(module_name, ".js")) {
            buf = pjsc(js_load_file)(ctx, &buf_len, module_name);
        } else {
            size_t len = strlen(module_name);
            char *module_name_buf = (char *)malloc(len + 4);
            memcpy(module_name_buf, module_name, len);
            snprintf(module_name_buf, len + 4, "%s.js", module_name);
            buf = pjsc(js_load_file)(ctx, &buf_len, module_name_buf);
            free(module_name_buf);
        }
        if (!buf) {
            pjsc(JS_ThrowReferenceError)(ctx, "could not load module filename '%s'",
                                   module_name);
            return NULL;
        }
        
        /* compile the module */
        func_val = pjsc(JS_Eval)(ctx, (char *)buf, buf_len, module_name,
                           JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
        pjsc(js_free)(ctx, buf);

        if (JS_IsException(func_val)) {
            panda_log.error("Eval error: %s\\%d\n%s",__FILE__, __LINE__, __func__);
            pjsc(js_free)(ctx, buf);
            JS_FreeValue(ctx, func_val);
            return NULL;
        }
        while (jsc_o->next != NULL) {
            jsc_o = jsc_o->next;
        }
        jsc_o->next = panda_new_js_obj();
        jsc_o->obj = func_val;
        
        /* the module is already referenced, so we must free it */
        m = (JSModuleDef *)JS_VALUE_GET_PTR(func_val);
    }
    return m;
}

static void compile_file(JSContext *ctx, panda_js_obj *jsc_o, const char *filename) {
    uint8_t *buf;
    int eval_flags;
    JSValue obj;
    size_t buf_len;
    
    buf = pjsc(js_load_file)(ctx, &buf_len, filename);
    if (!buf) {
        panda_log.error("Could not load file: %s\n", filename);
        exit(1);
    }
    eval_flags = JS_EVAL_FLAG_COMPILE_ONLY;
    int module = pjsc(JS_DetectModule)((const char *)buf, buf_len);

    if (module) eval_flags |= JS_EVAL_TYPE_MODULE;
    else        eval_flags |= JS_EVAL_TYPE_GLOBAL;

    obj = pjsc(JS_Eval)(ctx, (const char *)buf, buf_len, filename, eval_flags);
    if (JS_IsException(obj)) {
        panda_log.error("Can not eval %s to obj (JS_IsExcption)\n", filename);
        pjsc(js_std_dump_error)(ctx);
        exit(1);
    }

    jsc_o->obj = obj;

    pjsc(js_free)(ctx, buf);
}

panda_js_obj *panda_new_js_obj(){
    panda_js_obj *r = (panda_js_obj *)malloc(sizeof(panda_js_obj));
    if(!r){
        panda_log.error("Can not alloc panda_js_obj");
        exit(1);
    }
    r->byte_swap = FALSE;
    r->cmodule_list = (namelist_t *)malloc(sizeof(namelist_t));
    r->cmodule_list->array = NULL;
    r->cmodule_list->count = 0;
    r->cmodule_list->size = 0;
    r->init_module_list = (namelist_t *)malloc(sizeof(namelist_t));
    r->init_module_list->array = NULL;
    r->init_module_list->count = 0;
    r->init_module_list->size = 0;
    r->next = NULL;
    return r;
}

void panda_free_js_obj(JSContext *ctx, panda_js_obj *ptr){
    if(ptr == NULL) return;
    namelist_free(ptr->cmodule_list);
    namelist_free(ptr->init_module_list);
    free(ptr->cmodule_list);
    free(ptr->init_module_list);
    panda_free_js_obj(ctx, ptr->next);
    free(ptr);
}

panda_js_obj *panda_js_toObj(JSRuntime *rt, JSContext *ctx, const char *filename) {
    panda_js_obj *jsc_o = panda_new_js_obj();

    namelist_init_add_cmoudule(jsc_o->cmodule_list);
    pjsc(JS_SetModuleLoaderFunc)(rt, NULL, jsc_module_loader, jsc_o);
    compile_file(ctx, jsc_o, filename);

    return jsc_o;
}
