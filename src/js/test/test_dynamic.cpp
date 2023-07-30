#include "jscore/jsc.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static int fib(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}

static JSValue js_fib(JSContext *ctx, JSValueConst this_val, int argc,
                      JSValueConst *argv) {
    int n, res;
    if (pjsc(JS_ToInt32)(ctx, &n, argv[0]))
        return JS_EXCEPTION;
    res = fib(n);
    return JS_NewInt32(ctx, res);
}

static const JSCFunctionListEntry js_fib_funcs[] = {
    JS_CFUNC_DEF("fib", 1, js_fib),
};

static int js_fib_init(JSContext *ctx, JSModuleDef *m) {
    return pjsc(JS_SetModuleExportList)(ctx, m, js_fib_funcs,
                                        countof(js_fib_funcs));
}

extern "C" JSModuleDef *js_init_module(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = pjsc(JS_NewCModule)(ctx, module_name, js_fib_init);
    if (!m)
        return NULL;
    pjsc(JS_AddModuleExportList)(ctx, m, js_fib_funcs, countof(js_fib_funcs));
    return m;
}