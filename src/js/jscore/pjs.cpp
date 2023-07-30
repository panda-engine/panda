
#include "jscore/jsc.h"
#include "log.h"

#if defined(__APPLE__)
#define MALLOC_OVERHEAD 0
#else
#define MALLOC_OVERHEAD 8
#endif

static void *pjs_def_malloc(JSMallocState *s, size_t size) {
    void *ptr;

    if (size == 0 or unlikely(s->malloc_size + size > s->malloc_limit))
        return nullptr;

    pmem *pm = (pmem *)s->opaque;
    ptr = pm->alloc(size);
    if (!ptr)
        return nullptr;

    s->malloc_count++;
    s->malloc_size += pm->usable_size(ptr) + MALLOC_OVERHEAD;
    return ptr;
}

static void pjs_def_free(JSMallocState *s, void *ptr) {
    if (!ptr)
        return;
    pmem *pm = (pmem *)s->opaque;
    s->malloc_count--;
    s->malloc_size -= pm->usable_size(ptr) + MALLOC_OVERHEAD;
    pm->free(ptr);
}

static void *pjs_def_realloc(JSMallocState *s, void *ptr, size_t size) {
    size_t old_size;

    if (!ptr) {
        if (size == 0)
            return nullptr;
        return pjs_def_malloc(s, size);
    }
    pmem *pm = (pmem *)s->opaque;
    old_size = pm->usable_size(ptr);
    if (size == 0) {
        s->malloc_count--;
        s->malloc_size -= old_size + MALLOC_OVERHEAD;
        pm->free(ptr);
        return nullptr;
    }
    if (s->malloc_size + size - old_size > s->malloc_limit)
        return nullptr;

    ptr = pm->realloc(ptr, size);
    if (!ptr)
        return nullptr;

    s->malloc_size += pm->usable_size(ptr) - old_size;
    return ptr;
}

static const JSMallocFunctions def_malloc_funcs = {
    pjs_def_malloc,
    pjs_def_free,
    pjs_def_realloc,
    nullptr,
};

JSRuntime *panda_jsc_new_rt(pmem *alloc) {
    JSRuntime *p = pjsc(JS_NewRuntime2)(&def_malloc_funcs, alloc);
    pjsc(js_std_init_handlers)(p);
    return p;
}

void panda_jsc_free_rt(JSRuntime *p) {
    pjsc(js_std_free_handlers)(p);
    pjsc(JS_FreeRuntime)(p);
}

static void run_obj(JSContext *ctx, JSValue obj, int load_only) {
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

panda_js *panda_new_js(JSRuntime *rt, panda_js_t type) {
    panda_js *r = (panda_js *)mi_malloc(sizeof(panda_js));

    if (!r) {
        log_error("Cannot apply for memory", 0);
        return nullptr;
    }

    r->ctx = pjsc(JS_NewContextRaw)(rt);
    if (!r->ctx) {
        mi_free(r);
        log_error("Can not alloc new ctx", 0);
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
    mi_free(pjs);
}

panda_js *panda_js_to(JSRuntime *rt, const char *filename, panda_js_t type) {
    log_debug("panda_{%s}_to_{%d}", filename, type);
    panda_js *pjs = panda_new_js(rt, type);

    if (!pjs or !pjs->ctx) {
        return nullptr;
    }

    if (type == bytecode) {
        pjs->ptr = (void *)panda_js_toBytecode(rt, pjs->ctx, filename);
    } else if (type == obj) {
        pjs->ptr = (void *)panda_js_toObj(rt, pjs->ctx, filename);
    }

    if (!pjs->ptr) {
        panda_free_js(pjs);
        return nullptr;
    }

    pjsc(js_std_add_helpers)(pjs->ctx, 0, nullptr);

    return pjs;
}

void panda_js_run(panda_js *pjs) {
    log_debug("panda_js_run: type{%s}", (pjs->type) ? "obj" : "bc");
    if (pjs->type == bytecode) {
        panda_js_bc *bc = (panda_js_bc *)pjs->ptr;
        panda_js_bc *n = bc->next;
        while (n != nullptr) {
            if (n->bytecode == nullptr)
                return;
            pjsc(js_std_eval_binary)(pjs->ctx, n->bytecode, n->bytecode_len, 1);
            n = n->next;
        }
        if (bc->bytecode == nullptr)
            return;
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