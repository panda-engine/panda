
#include "transform.h"

transform_t *panda_new_transform(pmem *pm);
void panda_set_transform_canmove(transform_t *transform, const int can_move);
void panda_free_transform(pmem *pm, transform_t *transform);