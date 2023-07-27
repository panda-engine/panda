
#include "jsc.h"
#include "log.h"


int main(int argc, char **argv){
#ifdef _MSC_VER
    win_jsc_fn_init(".\\engine\\bin\\jsc.dll");
#endif
    set_log(all);
    JSRuntime *rt = pjsc(JS_NewRuntime)();
    pjsc(js_std_init_handlers)(rt);

    panda_js *pjs = panda_js_to(rt, "./hello.js", obj);
    panda_js_run(pjs);
    panda_free_js(pjs);

    pjsc(js_std_free_handlers)(rt);
    pjsc(JS_FreeRuntime)(rt);
#ifdef _MSC_VER
    win_jsc_fn_free();
#endif
    return 0;
}
