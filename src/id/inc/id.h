
#ifndef panda_id_h_
#define panda_id_h_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CTX_OBJ,
    CTX_COMPONENT,
} ctx_type;

typedef struct {
    ctx_type type;
    void *ctx;
} ctx_t;

typedef struct {
    char *name;
    ctx_t *ctx_list;
    uint64_t ctx_cnt;
    uint64_t cap;
    uint64_t len;
} id_list_t;

id_list_t *panda_new_id_list();
void panda_free_id_list(id_list_t *id_list);
uint64_t panda_add_id(id_list_t *id_list, void *ctx, ctx_type type);

void panda_set_id_list_name(id_list_t *id_list, const char *name);
ctx_t *panda_get_ctx_by_id(id_list_t *id_list, uint64_t id);

#ifdef __cplusplus
}
#endif

#endif // panda_id_h_