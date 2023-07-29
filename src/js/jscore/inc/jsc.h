
#ifndef jsc_h_
#define jsc_h_

#ifdef __cplusplus

#ifdef _MSC_VER
#include "win_def.h"
#define pjsc(fun) WIN_##fun.load(std::memory_order_acquire)
#else
#define pjsc(fun) fun
#endif

static inline void JS_FreeValue(JSContext *ctx, JSValue v) {
    if (JS_VALUE_HAS_REF_COUNT(v)) {
        JSRefCountHeader *p = (JSRefCountHeader *)JS_VALUE_GET_PTR(v);
        if (--p->ref_count <= 0) {
            pjsc(__JS_FreeValue)(ctx, v);
        }
    }
}

static inline void JS_FreeValueRT(JSRuntime *rt, JSValue v) {
    if (JS_VALUE_HAS_REF_COUNT(v)) {
        JSRefCountHeader *p = (JSRefCountHeader *)JS_VALUE_GET_PTR(v);
        if (--p->ref_count <= 0) {
            pjsc(__JS_FreeValueRT)(rt, v);
        }
    }
}

extern "C" {
#endif

#include "cutils.h"
#include "quickjs-libc.h"

#include "pmalloc.h"

extern void win_jsc_fn_init(const char *const path);
extern int win_jsc_fn_free();

JSRuntime *panda_jsc_new_rt(pmem *alloc);
void panda_jsc_free_rt(JSRuntime *p);

typedef struct namelist_t {
    char **name_array;
    int len;
    int cap;
} namelist_t;

void namelist_add(namelist_t *lp, const char *name);
void namelist_free(namelist_t *lp);
char *namelist_find(namelist_t *lp, const char *name);
void namelist_add_cmodule(namelist_t *n);

// js bytecode
typedef struct panda_js_bc {
    BOOL byte_swap;
    uint32_t bytecode_len;
    uint8_t *bytecode;
    namelist_t *cmodule_list;
    struct panda_js_bc *next;
} panda_js_bc;

panda_js_bc *panda_new_js_bc(JSContext *ctx);
void panda_free_js_bc(JSContext *ctx, panda_js_bc *ptr);

panda_js_bc *panda_js_toBytecode(JSRuntime *rt, JSContext *ctx,
                                 const char *filename);

typedef struct panda_js_obj {
    BOOL byte_swap;
    JSValue obj;
    namelist_t *cmodule_list;
    struct panda_js_obj *next;
} panda_js_obj;

panda_js_obj *panda_new_js_obj(JSContext *ctx);
void panda_free_js_obj(JSContext *ctx, panda_js_obj *ptr);

panda_js_obj *panda_js_toObj(JSRuntime *rt, JSContext *ctx,
                             const char *filename);

JSModuleDef *panda_js_init_cmodule(JSContext *ctx, const char *cmodule);

typedef enum {
    bytecode,
    obj,
} panda_js_t;

typedef struct panda_js {
    panda_js_t type;
    void *ptr;
    JSContext *ctx;
} panda_js;

panda_js *panda_new_js();
void panda_free_js(panda_js *pjs);

panda_js *panda_js_to(JSRuntime *rt, const char *filename, panda_js_t type);

void panda_js_run(panda_js *pjs);

#ifdef __cplusplus
}
#endif

#endif