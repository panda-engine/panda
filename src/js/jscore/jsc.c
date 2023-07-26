/*
 * panda-jsc
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#include <errno.h>
#if !defined(_WIN32)
#include <sys/wait.h>
#endif

#include "jsc.h"


void namelist_add(namelist_t *lp, const char *name, const char *short_name, int flags) {

    namelist_entry_t *e;
    if (lp->count == lp->size) {
        size_t newsize = lp->size + (lp->size >> 1) + 4;
        namelist_entry_t *a = realloc(lp->array, sizeof(lp->array[0]) * newsize);
        lp->array = a;
        lp->size = newsize;
    }
    e =  &lp->array[lp->count++];
    e->name = _strdup(name);
    if (short_name) {
        e->short_name = _strdup(short_name);
    }
    else {
        e->short_name = NULL;
    }
    e->flags = flags;
}

void namelist_free(namelist_t *lp) {

    while (lp->count > 0) {
        namelist_entry_t *e = &lp->array[--lp->count];
        free(e->name);
        free(e->short_name);
    }
    free(lp->array);
    lp->array = NULL;
    lp->size = 0;
}

namelist_entry_t *namelist_find(namelist_t *lp, const char *name) {
    int i;
    for(i = 0; i < lp->count; i++) {
        namelist_entry_t *e = &lp->array[i];
        if (!strcmp(e->name, name)) return e;
    }
    return NULL;
}

panda_js_bc *panda_new_js_bc(){
    panda_js_bc *r = malloc(sizeof(panda_js_bc));
    if(!r){
        //todo error
        printf("error\n");
        abort();
    }
    r->byte_swap = FALSE;
    r->bytecode = NULL;
    r->bytecode_len = 0;
    r->cmodule_list = malloc(sizeof(namelist_t));
    r->cmodule_list->array = NULL;
    r->cmodule_list->count = 0;
    r->cmodule_list->size = 0;
    r->init_module_list = malloc(sizeof(namelist_t));
    r->init_module_list->array = NULL;
    r->init_module_list->count = 0;
    r->init_module_list->size = 0;
    r->next = NULL;
    return r;
}

void panda_free_js_bc(JSContext *ctx, panda_js_bc *ptr){
    if(ptr == NULL) return;
    namelist_free(ptr->cmodule_list);
    namelist_free(ptr->init_module_list);
    free(ptr->cmodule_list);
    free(ptr->init_module_list);
    pjsc(js_free)(ctx, ptr->bytecode);
    panda_free_js_bc(ctx, ptr->next);
    free(ptr);
}

static void to_bytecode(JSContext *ctx, JSValueConst obj,
                            panda_js_bc *jsc_b, BOOL load_only) {
    uint8_t *bytecode_buf;
    size_t bytecode_buf_len;
    int flags;
    flags = JS_WRITE_OBJ_BYTECODE;
    if (jsc_b->byte_swap)
        flags |= JS_WRITE_OBJ_BSWAP;
    bytecode_buf = pjsc(JS_WriteObject)(ctx, &bytecode_buf_len, obj, flags);
    if (!bytecode_buf) {
        pjsc(js_std_dump_error)(ctx);
        exit(1);
    }

    jsc_b->bytecode_len = bytecode_buf_len;
    jsc_b->bytecode = bytecode_buf;
}

static int js_module_dummy_init(JSContext *ctx, JSModuleDef *m) {
    /* should never be called when compiling JS code */
    abort();
}

JSModuleDef *jsc_module_loader(JSContext *ctx,
                              const char *module_name, void *opaque) {
    JSModuleDef *m;
    namelist_entry_t *e;
    panda_js_bc * jsc_b = opaque;

    /* check if it is a declared C or system module */
    e = namelist_find(jsc_b->cmodule_list, module_name);
    if (e) {
        /* add in the static init module list */
        namelist_add(jsc_b->init_module_list, e->name, e->short_name, 0);
        /* create a dummy module */
        m = pjsc(JS_NewCModule)(ctx, module_name, js_module_dummy_init);
    } else if (has_suffix(module_name, ".so") || has_suffix(module_name, ".dll")) {
        fprintf(stderr, "Warning: binary module '%s' will be dynamically loaded\n", module_name);
        /* create a dummy module */
        m = pjsc(JS_NewCModule)(ctx, module_name, js_module_dummy_init);
        /* the resulting executable will export its symbols for the
           dynamic library */
        //dynamic_export = TRUE;
    } else {
        size_t buf_len;
        uint8_t *buf;
        JSValue func_val;
        
        if (has_suffix(module_name, ".js")) {
            buf = pjsc(js_load_file)(ctx, &buf_len, module_name);
        } else {
            size_t len = strlen(module_name);
            char *module_name_buf = malloc(len + 4);
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

        if (JS_IsException(func_val)) return NULL;

        while (jsc_b->next != NULL) {
            jsc_b = jsc_b->next;
        }
        jsc_b->next = panda_new_js_bc();
        to_bytecode(ctx, func_val, jsc_b->next, TRUE);
        
        /* the module is already referenced, so we must free it */
        m = JS_VALUE_GET_PTR(func_val);
        JS_FreeValue(ctx, func_val);
    }
    return m;
}

static void compile_file(JSContext *ctx, panda_js_bc *jsc_b,
                         const char *filename) {
    uint8_t *buf;
    int eval_flags;
    JSValue obj;
    size_t buf_len;
    
    buf = pjsc(js_load_file)(ctx, &buf_len, filename);
    if (!buf) {
        fprintf(stderr, "Could not load '%s'\n", filename);
        exit(1);
    }
    eval_flags = JS_EVAL_FLAG_COMPILE_ONLY;
    int module = pjsc(JS_DetectModule)((const char *)buf, buf_len);

    if (module) eval_flags |= JS_EVAL_TYPE_MODULE;
    else        eval_flags |= JS_EVAL_TYPE_GLOBAL;

    obj = pjsc(JS_Eval)(ctx, (const char *)buf, buf_len, filename, eval_flags);
    if (JS_IsException(obj)) {
        pjsc(js_std_dump_error)(ctx);
        exit(1);
    }
    pjsc(js_free)(ctx, buf);

    to_bytecode(ctx, obj, jsc_b, FALSE);
    JS_FreeValue(ctx, obj);
}

panda_js_bc *panda_js_tobytecode(JSRuntime *rt, JSContext *ctx, const char *filename) {
    panda_js_bc *jsc_b = panda_new_js_bc();

    namelist_add(jsc_b->cmodule_list, "std", "std", 0);
    namelist_add(jsc_b->cmodule_list, "os", "os", 0);

    pjsc(JS_SetModuleLoaderFunc)(rt, NULL, jsc_module_loader, jsc_b);
    compile_file(ctx, jsc_b, filename);

    return jsc_b;
}

