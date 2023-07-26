
#ifndef jsc_h_
#define jsc_h_

#ifdef __cplusplus
extern "C" {
#endif
#include "cutils.h"
#include "quickjs-libc.h"


#ifdef _MSC_VER
#include "win_def.h"
#define pjsc(fun) WIN_##fun
#else
#define pjsc(fun) fun
#endif

//JSContext *panda_jsc_new_ctx(JSRuntime *rt);

typedef struct {
    char *name;
    char *short_name;
    int flags;
} namelist_entry_t;

typedef struct namelist_t {
    namelist_entry_t *array;
    int count;
    int size;
} namelist_t;

void namelist_add(namelist_t *lp, const char *name, const char *short_name, int flags);
void namelist_free(namelist_t *lp);
namelist_entry_t *namelist_find(namelist_t *lp, const char *name);

void namelist_init_add_cmoudule(namelist_t * n);
//js bytecode
typedef struct panda_js_bc{
    BOOL byte_swap;
    uint32_t bytecode_len;
    uint8_t *bytecode;
    namelist_t *cmodule_list;
    namelist_t *init_module_list;
    struct panda_js_bc *next;
}panda_js_bc;

panda_js_bc *panda_new_js_bc();
void panda_free_js_bc(JSContext *ctx, panda_js_bc *ptr);

panda_js_bc *panda_js_toBytecode(JSRuntime *rt, JSContext *ctx, const char *filename);

typedef struct panda_js_obj{
    BOOL byte_swap;
    JSValue obj;
    namelist_t *cmodule_list;
    namelist_t *init_module_list;
    struct panda_js_obj *next;
}panda_js_obj;

panda_js_obj *panda_new_js_obj();
void panda_free_js_obj(JSContext *ctx, panda_js_obj *ptr);

panda_js_obj *panda_js_toObj(JSRuntime *rt, JSContext *ctx, const char *filename);

typedef enum {
    bytecode,
    obj,
}panda_js_type;

typedef struct panda_js{
    panda_js_type type;
    void *ptr;
    JSContext *ctx;
}panda_js;

panda_js *panda_new_js();
void panda_free_js(panda_js *pjs);

panda_js *panda_js_to(JSRuntime *rt, const char *filename, panda_js_type type);

void panda_js_run(panda_js *pjs);


#ifdef __cplusplus
}
#endif

#endif