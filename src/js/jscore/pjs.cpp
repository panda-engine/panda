
#include "jsc.h"
#include "log.h"
//#include "p_malloc.h"
#include <corecrt_malloc.h>
#include <stddef.h>


// static void *pjs_def_malloc(JSMallocState *s, size_t size){
//     size_t ptr;
//     /* Do not allocate zero bytes: behavior is platform dependent */
//     assert(size != 0);
//     ptr = p_malloc_malloc((struct p_malloc* )s->opaque, size);
//     if (ptr == PANDA_MALLOC_ALLOCATE_FAILED) {
//         log_error("pjs_def_malloc: p_malloc_malloc alloc size{%d}", size);
//         return nullptr;
//     }
//     return (void *)ptr;
// }

// static void pjs_def_free(JSMallocState *s, void *ptr){
//     size_t p = (size_t)ptr;
//     if (p == PANDA_MALLOC_ALLOCATE_FAILED) {
//         log_error("pjs_def_free: ptr is nullptr");
//         return;
//     }
//     p_malloc_free((struct p_malloc* )s->opaque, p);
// }


// static void *pjs_def_realloc(JSMallocState *s, void *ptr, size_t size) {
//     size_t p = (size_t)ptr;
//     size_t old_size = p_malloc_usable_size((struct p_malloc* )s->opaque, p);

//     //assert(size != 0);

//     if (p == PANDA_MALLOC_ALLOCATE_FAILED) {
//         if (size == 0) {
//             log_warn("ojs_def_realloc: size = 0!");
//             return nullptr;
//         }
//         return pjs_def_malloc(s, size);
//     }

//     if (size == 0) {
//         p_malloc_free((struct p_malloc* )s->opaque, p);
//         return nullptr;
//     }

//     size_t new_p = p_malloc_malloc((struct p_malloc* )s->opaque, size);
//     ptr = realloc(ptr, size);
//     if (!ptr)
//         return nullptr;


//     return ptr;
// }


// static const JSMallocFunctions def_malloc_funcs = {
//     pjs_def_malloc,
//     pjs_def_free,
//     pjs_realloc,
//     nullptr
// };

// JSRuntime *panda_jsc_new_rt(){
//     pjsc(JS_NewRuntime2)()
// }

static void run_obj(JSContext *ctx, JSValue obj, int load_only){
    log_debug("run_obj: obj_tag{%d} load_only{%d}", obj.tag, load_only);
    JSValue val;
    if (load_only) {
        if (JS_VALUE_GET_TAG(obj) == JS_TAG_MODULE) {
            pjsc(js_module_set_import_meta)(ctx, obj, FALSE, FALSE);
        }
    } else {
        if (JS_VALUE_GET_TAG(obj) == JS_TAG_MODULE) {
            if (pjsc(JS_ResolveModule)(ctx, obj) < 0) {
                JS_FreeValue(ctx, obj);
                goto exception;
            }
            pjsc(js_module_set_import_meta)(ctx, obj, FALSE, TRUE);
        }
        val = pjsc(JS_EvalFunction)(ctx, obj);
        if (JS_IsException(val)) {
        exception:
            pjsc(js_std_dump_error)(ctx);
            return;
        }
        JS_FreeValue(ctx, val);
    }
}


panda_js *panda_new_js(JSRuntime *rt, panda_js_type type){
    panda_js *r = (panda_js *)malloc(sizeof(panda_js));

    if (!r) {
        log_error("Cannot apply for memory", 0);
        return nullptr;
    }

    r->ctx = pjsc(JS_NewContextRaw)(rt);
    if (!r->ctx){
        free(r);
        log_error("Can not alloc new ctx",0);
        return nullptr;
    }
    pjsc(JS_AddIntrinsicBaseObjects)(r->ctx);
    pjsc(JS_AddIntrinsicDate)(r->ctx);
    pjsc(JS_AddIntrinsicEval)(r->ctx);
    pjsc(JS_AddIntrinsicStringNormalize)(r->ctx);
    pjsc(JS_AddIntrinsicRegExp)(r->ctx);
    pjsc(JS_AddIntrinsicJSON)(r->ctx);
    pjsc(JS_AddIntrinsicProxy)(r->ctx);
    pjsc(JS_AddIntrinsicMapSet)(r->ctx);
    pjsc(JS_AddIntrinsicTypedArrays)(r->ctx);
    pjsc(JS_AddIntrinsicPromise)(r->ctx);

    r->ptr = nullptr;
    r->type = type;
    return r;
}

void panda_free_js(panda_js *pjs) {
    if (pjs->type == bytecode) {
        panda_free_js_bc(pjs->ctx, (panda_js_bc *)pjs->ptr);
    } else if (pjs->type == obj) {
        panda_free_js_obj(pjs->ctx, (panda_js_obj *)pjs->ptr);
    }
    pjsc(JS_FreeContext)(pjs->ctx);
    free(pjs);
}

panda_js *panda_js_to(JSRuntime *rt, const char *filename, panda_js_type type){
    log_debug("panda_{%s}_to_{%d}", filename, type);
    panda_js *pjs = panda_new_js(rt, type);

    if(!pjs or !pjs->ctx) {
        return nullptr;
    }

    if(type == bytecode){
        pjs->ptr = (void *)panda_js_toBytecode(rt, pjs->ctx, filename);
    } else if (type == obj) {
        pjs->ptr = (void *)panda_js_toObj(rt, pjs->ctx, filename);
    }

    if(!pjs->ptr) {
        panda_free_js(pjs);
        return nullptr;
    }

    pjsc(js_std_add_helpers)(pjs->ctx, 0, nullptr);

    return pjs;
}


void panda_js_run(panda_js *pjs){
    log_debug("panda_js_run: type{%s}", (pjs->type)?"obj":"bc");
    if (pjs->type == bytecode) {
        panda_js_bc *bc = (panda_js_bc *)pjs->ptr;
        panda_js_bc *n = bc->next;
        while (n != nullptr) {
            if(n->bytecode == nullptr) return;
            pjsc(js_std_eval_binary)(pjs->ctx, n->bytecode, n->bytecode_len, 1);
            n = n->next;
        }
        if(bc->bytecode == nullptr) return;
        pjsc(js_std_eval_binary)(pjs->ctx, bc->bytecode, bc->bytecode_len, 0);
    } else if (pjs->type == obj) {
        panda_js_obj *obj = (panda_js_obj *)pjs->ptr;
        panda_js_obj *n = obj->next;
        while (n != nullptr) {
            run_obj(pjs->ctx, n->obj, 1);
            n = n->next;
        }
        run_obj(pjs->ctx, obj->obj, 0);
    }
}