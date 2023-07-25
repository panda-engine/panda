
#include "jsc.h"


int main(int argc, char **argv){
#ifdef _MSC_VER
    win_jsc_fn_init(".\\engine\\bin\\jsc.dll");
#endif
    JSRuntime *rt = pjsc(JS_NewRuntime)();
    //pjsc(js_std_set_worker_new_context_func)(panda_jsc_new_ctx);
    pjsc(js_std_init_handlers)(rt);
    JSContext *ctx = pjsc(JS_NewContext)(rt);
    panda_js_bc *code = panda_js_tobytecode(rt, ctx, "./hello.js");
    pjsc(js_std_loop)(ctx);
    pjsc(js_std_add_helpers)(ctx, 0, NULL);

    panda_js_bc *n = code->next;
    while (n != NULL) {
        pjsc(js_std_eval_binary)(ctx, n->bytecode, n->bytecode_len, 1);
        n = n->next;
    }
    pjsc(js_std_eval_binary)(ctx, code->bytecode, code->bytecode_len, 0);

    panda_free_js_bc(ctx, code);

    pjsc(JS_FreeContext)(ctx);
    pjsc(JS_FreeRuntime)(rt);
#ifdef _MSC_VER
    win_jsc_fn_free();
#endif
    return 0;
}
