
#include "job/inc/job.h"

job_t *panda_new_job(pmem *pm) {
    job_t *r = NULL;

    if (!pm) {
        r = mi_malloc(sizeof(job_t));
    } else {
        r = pm->alloc(sizeof(job_t), pm->_ptr);
    }

    if (!r)
        return NULL;

    r->id = 0;
    r->ptr = NULL;
    r->fn = NULL;

    return r;
}

void panda_set_job(job_t *job, void *ptr, job_fn_t fn) {

    if (!job)
        return;

    job->ptr = ptr;
    job->fn = fn;
}

void panda_set_job_id(job_t *job, const uint64_t id) {

    if (!job)
        return;

    job->id = id;
}

void panda_free_job(pmem *pm, job_t *job) {

    if (!job)
        return;

    if (!pm) {
        mi_free(job);
        return;
    }

    pm->free(job, pm->_ptr);
}

job_list_t *panda_new_job_list(pmem *pm) {
    job_list_t *r = NULL;

    if (!pm) {
        r = mi_malloc(sizeof(job_list_t));
    } else {
        r = pm->alloc(sizeof(job_list_t), pm->_ptr);
    }

    if (!r)
        return NULL;

    r->array = NULL;
    r->cap = 0;
    r->len = 0;

    return r;
}

void panda_job_list_add(pmem *pm, job_list_t *job_list, job_t *job) {
    if (!job_list)
        return;

    if (job_list->len == job_list->cap) {
        job_list->cap = job_list->cap * 2 + 1;
        if (!pm) {
            job_list->array =
                mi_realloc(job_list->array, sizeof(job_t) * job_list->cap);
        } else {
            job_list->array = pm->realloc(
                job_list->array, sizeof(job_t) * job_list->cap, pm->_ptr);
        }
    }

    job_list->array[job_list->len++] = *job;
}

void panda_free_job_list(pmem *pm, job_list_t *job_list) {
    if (!job_list)
        return;

    if (!pm) {
        mi_free(job_list->array);
        mi_free(job_list);
        return;
    }

    pm->free(job_list->array, pm->_ptr);
    pm->free(job_list, pm->_ptr);
}

void panda_process_job_list(pmem *pm, job_list_t *job_list) {
    if (!job_list)
        return;

    for (int i = 0; i < job_list->len; ++i) {
        job_t *job = &job_list->array[i];
        job->fn(job->ptr);
    }
}