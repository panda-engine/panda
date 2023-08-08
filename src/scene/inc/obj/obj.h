#ifndef panda_obj_h_
#define panda_obj_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "pmalloc.h"

#include <stdint.h>

typedef struct {
    char *name;
    int type;
    int is_enable;
    void *ptr;
    void (*fn)(void *ptr);
} component_t;

typedef struct {
    char *name;
    uint64_t id;
    component_t *array;
    int cap;
    int len;
} obj_t;

obj_t *panda_new_obj(pmem *pm);
void panda_free_obj(pmem *pm, obj_t *obj);

void panda_set_obj_name(pmem *pm, obj_t *obj, const char *name);
void panda_free_obj_name(pmem *pm, obj_t *obj);
void panda_set_obj_id(obj_t *obj, const uint64_t id);

void panda_set_component_name(pmem *pm, component_t *component,
                              const char *name);
void panda_free_component_name(pmem *pm, component_t *component);

void panda_obj_component_add(pmem *pm, obj_t *obj, component_t *cp);
void panda_obj_component_free_all(pmem *pm, obj_t *obj);
component_t *panda_obj_component_find(obj_t *obj, const int type);

#ifdef __cplusplus
}
#endif

#endif