
#ifndef init_cmodule_h_
#define init_cmodule_h_

#include "jsc.h"

#ifdef __cplusplus
#include <atomic>
extern "C" {
#endif

typedef JSModuleDef *(*init_module_t)(JSContext *, const char *);

typedef struct {
    char *name;
    init_module_t fn;
} cmodule_t;

typedef struct {
    cmodule_t *array;
    int cap;
    int len;
} cmodule_list_t;

void cmodule_list_free();

void cmodule_list_add(char *name, init_module_t fn);

#ifdef __cplusplus
extern std::atomic<cmodule_list_t *> cmodule_list;
}
#endif

#endif