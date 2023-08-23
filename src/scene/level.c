
#include "level.h"

level_t *panda_new_level(pmem *pm);
void panda_set_level_name(level_t *level, const char *name);
void panda_set_level_id(level_t *level, const uint64_t id);
void panda_free_level(pmem *pm, level_t *obj);

void panda_level_component_add(pmem *pm, level_t *level, obj_t *obj);
void panda_level_obj_free(pmem *pm, level_t *level);