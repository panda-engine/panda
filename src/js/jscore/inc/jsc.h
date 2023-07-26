
#ifndef jsc_h_
#define jsc_h_

#include <stdint.h>
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

panda_js_bc *panda_js_tobytecode(JSRuntime *rt, JSContext *ctx, const char *filename);

#ifdef __cplusplus
}
#endif

#endif