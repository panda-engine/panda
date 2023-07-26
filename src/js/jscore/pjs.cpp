
#include "jsc.h"
#include "log.h"

static void run_obj(JSContext *ctx, JSValue obj, int load_only){
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
            exit(1);
        }
        JS_FreeValue(ctx, val);
    }
}


panda_js *panda_new_js(JSRuntime *rt, panda_js_type type){
    panda_js *r = (panda_js *)malloc(sizeof(panda_js));

    // r->ctx = pjsc(JS_NewContext)(rt);
    r->ctx = pjsc(JS_NewContextRaw)(rt);
    if (!r->ctx){
        panda_log.error("Can not alloc new ctx");
        exit(1);
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

    // if (type == bytecode) {
    //     r->ptr = (void *) panda_new_js_bc();
    // } else if (type == obj) {
    //     r->ptr = (void *) panda_new_js_obj();
    // }
    r->type = type;
    return r;
}

void panda_free_js(panda_js *pjs){
    if (pjs->type == bytecode) {
        panda_free_js_bc(pjs->ctx, (panda_js_bc *)pjs->ptr);
    } else if (pjs->type == obj) {
        panda_free_js_obj(pjs->ctx, (panda_js_obj *)pjs->ptr);
    }
    pjsc(JS_FreeContext)(pjs->ctx);
    free(pjs);
}

panda_js *panda_js_to(JSRuntime *rt, const char *filename, panda_js_type type){
    panda_js *pjs = panda_new_js(rt, type);

    if(type == bytecode){
        pjs->ptr = (void *)panda_js_toBytecode(rt, pjs->ctx, filename);
    } else if (type == obj) {
        pjs->ptr = (void *)panda_js_toObj(rt, pjs->ctx, filename);
    }
    pjsc(js_std_add_helpers)(pjs->ctx, 0, NULL);

    return pjs;
}


void panda_js_run(panda_js *pjs){
    if (pjs->type == bytecode) {
        panda_js_bc *bc = (panda_js_bc *)pjs->ptr;
        panda_js_bc *n = bc->next;
        while (n != NULL) {
            pjsc(js_std_eval_binary)(pjs->ctx, n->bytecode, n->bytecode_len, 1);
            n = n->next;
        }
        pjsc(js_std_eval_binary)(pjs->ctx, bc->bytecode, bc->bytecode_len, 0);
    } else if (pjs->type == obj) {
        panda_js_obj *obj = (panda_js_obj *)pjs->ptr;
        panda_js_obj *n = obj->next;
        while (n != NULL) {
            run_obj(pjs->ctx, n->obj, 1);
            n = n->next;
        }
        run_obj(pjs->ctx, obj->obj, 0);
    }
}