
#include "jsc.h"
#include "log.h"
#include "pmalloc.h"

int main(int argc, char **argv){
#ifdef _MSC_VER
    win_jsc_fn_init(".\\engine\\bin\\jsc.dll");
#endif
    set_log(off);
    pmem *pma = pmem_new_alloc(0, normal);
    JSRuntime *rt = panda_jsc_new_rt(pma);

    panda_js *pjs = panda_js_to(rt, "./hello.js", obj);
    panda_js_run(pjs);
    panda_free_js(pjs);

    panda_jsc_free_rt(rt);
#ifdef _MSC_VER
    win_jsc_fn_free();
#endif
    return 0;
}
