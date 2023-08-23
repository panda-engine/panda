#ifndef panda_level_h_
#define panda_level_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "obj.h"

typedef struct {
    char *name;
    uint64_t id;
    obj_t *array;
    int cap;
    int len;
} level_t;

// obj fn
level_t *panda_new_level(pmem *pm);
void panda_set_level_name(level_t *level, const char *name);
void panda_set_level_id(level_t *level, const uint64_t id);
void panda_free_level(pmem *pm, level_t *obj);
// utils fn
void panda_level_component_add(pmem *pm, level_t *level, obj_t *obj);
void panda_level_obj_free(pmem *pm, level_t *level);

#ifdef __cplusplus
}
#endif

#endif