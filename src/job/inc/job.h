
#ifndef panda_job_h_
#define panda_job_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "malloc/inc/pmalloc.h"

typedef void (*job_fn_t)(void *ptr);

typedef struct {
    uint64_t id;
    void *ptr;
    job_fn_t fn;
} job_t;

typedef struct {
    job_t *array;
    int cap;
    int len;
} job_list_t;

// job fn
job_t *panda_new_job(pmem *pm);
// set job ptr and fn
void panda_set_job(job_t *job, void *ptr, job_fn_t fn);
// set job id
void panda_set_job_id(job_t *job, const uint64_t id);
// free job
void panda_free_job(pmem *pm, job_t *job);

// job list fn
job_list_t *panda_new_job_list(pmem *pm);
// add job to job list
void panda_job_list_add(pmem *pm, job_list_t *job_list, job_t *job);
// free job list
void panda_free_job_list(pmem *pm, job_list_t *job_list);
// process job list
void panda_process_job_list(pmem *pm, job_list_t *job_list);

#ifdef __cplusplus
}
#endif

#endif // panda_job_h_