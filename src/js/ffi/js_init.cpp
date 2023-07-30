
#include "js_init.h"
#include "jscore/jsc.h"

// static const char *suffix = p_suffix;

static const JSCFunctionListEntry js_ffi_funcs[] = {
    // JS_CFUNC_DEF("fib", 1, js_fib),
    JS_PROP_STRING_DEF("p_suffix", p_suffix, 0),
};

static int js_ffi_init(JSContext *ctx, JSModuleDef *m) {
    return pjsc(JS_SetModuleExportList)(ctx, m, js_ffi_funcs,
                                        countof(js_ffi_funcs));
}

JSModuleDef *js_init_module_ffi(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = pjsc(JS_NewCModule)(ctx, module_name, js_ffi_init);
    if (!m)
        return NULL;
    pjsc(JS_AddModuleExportList)(ctx, m, js_ffi_funcs, countof(js_ffi_funcs));
    return m;
}
