

#include "jscore/win_def.h"
#include <windows.h>

std::atomic<JSRuntime *(*)()> WIN_JS_NewRuntime;
std::atomic<JSContext *(*)(JSRuntime *)> WIN_JS_NewContext;
std::atomic<void (*)(JSRuntime *rt, const char *info)> WIN_JS_SetRuntimeInfo;
std::atomic<void (*)(JSRuntime *rt, size_t limit)> WIN_JS_SetMemoryLimit;
std::atomic<void (*)(JSRuntime *rt, size_t gc_threshold)> WIN_JS_SetGCThreshold;
std::atomic<void (*)(JSRuntime *rt, size_t stack_size)> WIN_JS_SetMaxStackSize;
std::atomic<void (*)(JSRuntime *rt)> WIN_JS_UpdateStackTop;
std::atomic<JSRuntime *(*)(const JSMallocFunctions *mf, void *opaque)>
    WIN_JS_NewRuntime2;
std::atomic<void (*)(JSRuntime *rt)> WIN_JS_FreeRuntime;
std::atomic<void *(*)(JSRuntime *rt)> WIN_JS_GetRuntimeOpaque;
std::atomic<void (*)(JSRuntime *rt, void *opaque)> WIN_JS_SetRuntimeOpaque;
std::atomic<void (*)(JSRuntime *rt, JSValueConst val, JS_MarkFunc *mark_func)>
    WIN_JS_MarkValue;
std::atomic<void (*)(JSRuntime *rt)> WIN_JS_RunGC;
std::atomic<JS_BOOL (*)(JSRuntime *rt, JSValueConst obj)> WIN_JS_IsLiveObject;
// std::atomic<JSContext *(*)(JSRuntime *rt)> WIN_JS_NewContext;
std::atomic<void (*)(JSContext *s)> WIN_JS_FreeContext;
std::atomic<JSContext *(*)(JSContext *ctx)> WIN_JS_DupContext;
std::atomic<void *(*)(JSContext *ctx)> WIN_JS_GetContextOpaque;
std::atomic<void (*)(JSContext *ctx, void *opaque)> WIN_JS_SetContextOpaque;
std::atomic<JSRuntime *(*)(JSContext *ctx)> WIN_JS_GetRuntime;
std::atomic<void (*)(JSContext *ctx, JSClassID class_id, JSValue obj)>
    WIN_JS_SetClassProto;
std::atomic<JSValue (*)(JSContext *ctx, JSClassID class_id)>
    WIN_JS_GetClassProto;
std::atomic<JSContext *(*)(JSRuntime *rt)> WIN_JS_NewContextRaw;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicBaseObjects;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicDate;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicEval;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicStringNormalize;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicRegExpCompiler;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicRegExp;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicJSON;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicProxy;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicMapSet;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicTypedArrays;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicPromise;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicBigInt;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicBigFloat;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicBigDecimal;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_AddIntrinsicOperators;
std::atomic<void (*)(JSContext *ctx, JS_BOOL enable)> WIN_JS_EnableBignumExt;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst this_val, int argc,
                        JSValueConst *argv)>
    WIN_js_string_codePointRange;
std::atomic<void *(*)(JSRuntime *rt, size_t size)> WIN_js_malloc_rt;
std::atomic<void (*)(JSRuntime *rt, void *ptr)> WIN_js_free_rt;
std::atomic<void *(*)(JSRuntime *rt, void *ptr, size_t size)> WIN_js_realloc_rt;
std::atomic<size_t (*)(JSRuntime *rt, const void *ptr)>
    WIN_js_malloc_usable_size_rt;
std::atomic<void *(*)(JSRuntime *rt, size_t size)> WIN_js_mallocz_rt;
std::atomic<void *(*)(JSContext *ctx, size_t size)> WIN_js_malloc;
std::atomic<void (*)(JSContext *ctx, void *ptr)> WIN_js_free;
std::atomic<void *(*)(JSContext *ctx, void *ptr, size_t size)> WIN_js_realloc;
std::atomic<size_t (*)(JSContext *ctx, const void *ptr)>
    WIN_js_malloc_usable_size;
std::atomic<void *(*)(JSContext *ctx, void *ptr, size_t size, size_t *pslack)>
    WIN_js_realloc2;
std::atomic<void *(*)(JSContext *ctx, size_t size)> WIN_js_mallocz;
std::atomic<char *(*)(JSContext *ctx, const char *str)> WIN_js_strdup;
std::atomic<char *(*)(JSContext *ctx, const char *s, size_t n)> WIN_js_strndup;
std::atomic<void (*)(JSRuntime *rt, JSMemoryUsage *s)>
    WIN_JS_ComputeMemoryUsage;
std::atomic<void (*)(FILE *fp, const JSMemoryUsage *s, JSRuntime *rt)>
    WIN_JS_DumpMemoryUsage;
std::atomic<JSAtom (*)(JSContext *ctx, const char *str, size_t len)>
    WIN_JS_NewAtomLen;
std::atomic<JSAtom (*)(JSContext *ctx, const char *str)> WIN_JS_NewAtom;
std::atomic<JSAtom (*)(JSContext *ctx, uint32_t n)> WIN_JS_NewAtomUInt32;
std::atomic<JSAtom (*)(JSContext *ctx, JSAtom v)> WIN_JS_DupAtom;
std::atomic<void (*)(JSContext *ctx, JSAtom v)> WIN_JS_FreeAtom;
std::atomic<void (*)(JSRuntime *rt, JSAtom v)> WIN_JS_FreeAtomRT;
std::atomic<JSValue (*)(JSContext *ctx, JSAtom atom)> WIN_JS_AtomToValue;
std::atomic<JSValue (*)(JSContext *ctx, JSAtom atom)> WIN_JS_AtomToString;
std::atomic<const char *(*)(JSContext *ctx, JSAtom atom)> WIN_JS_AtomToCString;
std::atomic<JSAtom (*)(JSContext *ctx, JSValueConst val)> WIN_JS_ValueToAtom;
std::atomic<JSClassID (*)(JSClassID *pclass_id)> WIN_JS_NewClassID;
std::atomic<int (*)(JSRuntime *rt, JSClassID class_id,
                    const JSClassDef *class_def)>
    WIN_JS_NewClass;
std::atomic<int (*)(JSRuntime *rt, JSClassID class_id)>
    WIN_JS_IsRegisteredClass;
std::atomic<JSValue (*)(JSContext *ctx, int64_t v)> WIN_JS_NewBigInt64;
std::atomic<JSValue (*)(JSContext *ctx, uint64_t v)> WIN_JS_NewBigUint64;
std::atomic<JSValue (*)(JSContext *ctx, JSValue obj)> WIN_JS_Throw;
std::atomic<JSValue (*)(JSContext *ctx)> WIN_JS_GetException;
std::atomic<JS_BOOL (*)(JSContext *ctx, JSValueConst val)> WIN_JS_IsError;
std::atomic<void (*)(JSContext *ctx)> WIN_JS_ResetUncatchableError;
std::atomic<JSValue (*)(JSContext *ctx)> WIN_JS_NewError;
std::atomic<JSValue __js_printf_like(2, 3) (*)(JSContext *ctx, const char *fmt,
                                               ...)>
    WIN_JS_ThrowSyntaxError;
std::atomic<JSValue __js_printf_like(2, 3) (*)(JSContext *ctx, const char *fmt,
                                               ...)>
    WIN_JS_ThrowTypeError;
std::atomic<JSValue __js_printf_like(2, 3) (*)(JSContext *ctx, const char *fmt,
                                               ...)>
    WIN_JS_ThrowReferenceError;
std::atomic<JSValue __js_printf_like(2, 3) (*)(JSContext *ctx, const char *fmt,
                                               ...)>
    WIN_JS_ThrowRangeError;
std::atomic<JSValue __js_printf_like(2, 3) (*)(JSContext *ctx, const char *fmt,
                                               ...)>
    WIN_JS_ThrowInternalError;
std::atomic<JSValue (*)(JSContext *ctx)> WIN_JS_ThrowOutOfMemory;

std::atomic<void (*)(JSContext *ctx, JSValue v)> WIN___JS_FreeValue;
std::atomic<void (*)(JSRuntime *rt, JSValue v)> WIN___JS_FreeValueRT;

std::atomic<int (*)(JSContext *ctx, JSValueConst val)> WIN_JS_ToBool;
std::atomic<int (*)(JSContext *ctx, int32_t *pres, JSValueConst val)>
    WIN_JS_ToInt32;
std::atomic<int (*)(JSContext *ctx, int64_t *pres, JSValueConst val)>
    WIN_JS_ToInt64;
std::atomic<int (*)(JSContext *ctx, uint64_t *plen, JSValueConst val)>
    WIN_JS_ToIndex;
std::atomic<int (*)(JSContext *ctx, double *pres, JSValueConst val)>
    WIN_JS_ToFloat64;
std::atomic<int (*)(JSContext *ctx, int64_t *pres, JSValueConst val)>
    WIN_JS_ToBigInt64;
std::atomic<int (*)(JSContext *ctx, int64_t *pres, JSValueConst val)>
    WIN_JS_ToInt64Ext;
std::atomic<JSValue (*)(JSContext *ctx, const char *str1, size_t len1)>
    WIN_JS_NewStringLen;
std::atomic<JSValue (*)(JSContext *ctx, const char *str)> WIN_JS_NewString;
std::atomic<JSValue (*)(JSContext *ctx, const char *str)> WIN_JS_NewAtomString;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst val)> WIN_JS_ToString;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst val)> WIN_JS_ToPropertyKey;
std::atomic<const char *(*)(JSContext *ctx, size_t *plen, JSValueConst val1,
                            JS_BOOL cesu8)>
    WIN_JS_ToCStringLen2;
std::atomic<void (*)(JSContext *ctx, const char *ptr)> WIN_JS_FreeCString;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst proto, JSClassID class_id)>
    WIN_JS_NewObjectProtoClass;
std::atomic<JSValue (*)(JSContext *ctx, int class_id)> WIN_JS_NewObjectClass;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst proto)>
    WIN_JS_NewObjectProto;
std::atomic<JSValue (*)(JSContext *ctx)> WIN_JS_NewObject;
std::atomic<JS_BOOL (*)(JSContext *ctx, JSValueConst val)> WIN_JS_IsFunction;
std::atomic<JS_BOOL (*)(JSContext *ctx, JSValueConst val)> WIN_JS_IsConstructor;
std::atomic<JS_BOOL (*)(JSContext *ctx, JSValueConst func_obj, JS_BOOL val)>
    WIN_JS_SetConstructorBit;
std::atomic<JSValue (*)(JSContext *ctx)> WIN_JS_NewArray;
std::atomic<int (*)(JSContext *ctx, JSValueConst val)> WIN_JS_IsArray;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst obj, JSAtom prop,
                        JSValueConst receiver, JS_BOOL throw_ref_error)>
    WIN_JS_GetPropertyInternal;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst this_obj,
                        const char *prop)>
    WIN_JS_GetPropertyStr;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst this_obj, uint32_t idx)>
    WIN_JS_GetPropertyUint32;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop,
                    JSValue val, int flags)>
    WIN_JS_SetPropertyInternal;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, uint32_t idx,
                    JSValue val)>
    WIN_JS_SetPropertyUint32;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, int64_t idx,
                    JSValue val)>
    WIN_JS_SetPropertyInt64;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, const char *prop,
                    JSValue val)>
    WIN_JS_SetPropertyStr;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop)>
    WIN_JS_HasProperty;
std::atomic<int (*)(JSContext *ctx, JSValueConst obj)> WIN_JS_IsExtensible;
std::atomic<int (*)(JSContext *ctx, JSValueConst obj)> WIN_JS_PreventExtensions;
std::atomic<int (*)(JSContext *ctx, JSValueConst obj, JSAtom prop, int flags)>
    WIN_JS_DeleteProperty;
std::atomic<int (*)(JSContext *ctx, JSValueConst obj, JSValueConst proto_val)>
    WIN_JS_SetPrototype;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst val)> WIN_JS_GetPrototype;
std::atomic<int (*)(JSContext *ctx, JSPropertyEnum **ptab, uint32_t *plen,
                    JSValueConst obj, int flags)>
    WIN_JS_GetOwnPropertyNames;
std::atomic<int (*)(JSContext *ctx, JSPropertyDescriptor *desc,
                    JSValueConst obj, JSAtom prop)>
    WIN_JS_GetOwnProperty;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst func_obj,
                        JSValueConst this_obj, int argc, JSValueConst *argv)>
    WIN_JS_Call;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst this_val, JSAtom atom,
                        int argc, JSValueConst *argv)>
    WIN_JS_Invoke;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst func_obj, int argc,
                        JSValueConst *argv)>
    WIN_JS_CallConstructor;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst func_obj,
                        JSValueConst new_target, int argc, JSValueConst *argv)>
    WIN_JS_CallConstructor2;
std::atomic<JS_BOOL (*)(const char *input, size_t input_len)>
    WIN_JS_DetectModule;
std::atomic<JSValue (*)(JSContext *ctx, const char *input, size_t input_len,
                        const char *filename, int eval_flags)>
    WIN_JS_Eval;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst this_obj,
                        const char *input, size_t input_len,
                        const char *filename, int eval_flags)>
    WIN_JS_EvalThis;
std::atomic<JSValue (*)(JSContext *ctx)> WIN_JS_GetGlobalObject;
std::atomic<int (*)(JSContext *ctx, JSValueConst val, JSValueConst obj)>
    WIN_JS_IsInstanceOf;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop,
                    JSValueConst val, JSValueConst getter, JSValueConst setter,
                    int flags)>
    WIN_JS_DefineProperty;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop,
                    JSValue val, int flags)>
    WIN_JS_DefinePropertyValue;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, uint32_t idx,
                    JSValue val, int flags)>
    WIN_JS_DefinePropertyValueUint32;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, const char *prop,
                    JSValue val, int flags)>
    WIN_JS_DefinePropertyValueStr;
std::atomic<int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop,
                    JSValue getter, JSValue setter, int flags)>
    WIN_JS_DefinePropertyGetSet;
std::atomic<void (*)(JSValue obj, void *opaque)> WIN_JS_SetOpaque;
std::atomic<void *(*)(JSValueConst obj, JSClassID class_id)> WIN_JS_GetOpaque;
std::atomic<void *(*)(JSContext *ctx, JSValueConst obj, JSClassID class_id)>
    WIN_JS_GetOpaque2;
std::atomic<JSValue (*)(JSContext *ctx, const char *buf, size_t buf_len,
                        const char *filename)>
    WIN_JS_ParseJSON;
std::atomic<JSValue (*)(JSContext *ctx, const char *buf, size_t buf_len,
                        const char *filename, int flags)>
    WIN_JS_ParseJSON2;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst obj, JSValueConst replacer,
                        JSValueConst space0)>
    WIN_JS_JSONStringify;
std::atomic<JSValue (*)(JSContext *ctx, uint8_t *buf, size_t len,
                        JSFreeArrayBufferDataFunc *free_func, void *opaque,
                        JS_BOOL is_shared)>
    WIN_JS_NewArrayBuffer;
std::atomic<JSValue (*)(JSContext *ctx, const uint8_t *buf, size_t len)>
    WIN_JS_NewArrayBufferCopy;
std::atomic<void (*)(JSContext *ctx, JSValueConst obj)>
    WIN_JS_DetachArrayBuffer;
std::atomic<uint8_t *(*)(JSContext *ctx, size_t *psize, JSValueConst obj)>
    WIN_JS_GetArrayBuffer;
std::atomic<JSValue (*)(JSContext *ctx, JSValueConst obj, size_t *pbyte_offset,
                        size_t *pbyte_length, size_t *pbytes_per_element)>
    WIN_JS_GetTypedArrayBuffer;
std::atomic<void (*)(JSRuntime *rt, const JSSharedArrayBufferFunctions *sf)>
    WIN_JS_SetSharedArrayBufferFunctions;
std::atomic<JSValue (*)(JSContext *ctx, JSValue *resolving_funcs)>
    WIN_JS_NewPromiseCapability;
std::atomic<void (*)(JSRuntime *rt, JSHostPromiseRejectionTracker *cb,
                     void *opaque)>
    WIN_JS_SetHostPromiseRejectionTracker;
std::atomic<void (*)(JSRuntime *rt, JSInterruptHandler *cb, void *opaque)>
    WIN_JS_SetInterruptHandler;
std::atomic<void (*)(JSRuntime *rt, JS_BOOL can_block)> WIN_JS_SetCanBlock;
std::atomic<void (*)(JSContext *ctx, JSValueConst obj)> WIN_JS_SetIsHTMLDDA;
std::atomic<void (*)(JSRuntime *rt, JSModuleNormalizeFunc *module_normalize,
                     JSModuleLoaderFunc *module_loader, void *opaque)>
    WIN_JS_SetModuleLoaderFunc;
std::atomic<JSValue (*)(JSContext *ctx, JSModuleDef *m)> WIN_JS_GetImportMeta;
std::atomic<JSAtom (*)(JSContext *ctx, JSModuleDef *m)> WIN_JS_GetModuleName;
std::atomic<int (*)(JSContext *ctx, JSJobFunc *job_func, int argc,
                    JSValueConst *argv)>
    WIN_JS_EnqueueJob;
std::atomic<JS_BOOL (*)(JSRuntime *rt)> WIN_JS_IsJobPending;
std::atomic<int (*)(JSRuntime *rt, JSContext **pctx)> WIN_JS_ExecutePendingJob;
std::atomic<uint8_t *(*)(JSContext *ctx, size_t *psize, JSValueConst obj,
                         int flags)>
    WIN_JS_WriteObject;
std::atomic<uint8_t *(*)(JSContext *ctx, size_t *psize, JSValueConst obj,
                         int flags, uint8_t ***psab_tab, size_t *psab_tab_len)>
    WIN_JS_WriteObject2;
std::atomic<JSValue (*)(JSContext *ctx, const uint8_t *buf, size_t buf_len,
                        int flags)>
    WIN_JS_ReadObject;
std::atomic<JSValue (*)(JSContext *ctx, JSValue fun_obj)> WIN_JS_EvalFunction;
std::atomic<int (*)(JSContext *ctx, JSValueConst obj)> WIN_JS_ResolveModule;
std::atomic<JSAtom (*)(JSContext *ctx, int n_stack_levels)>
    WIN_JS_GetScriptOrModuleName;
std::atomic<JSModuleDef *(*)(JSContext *ctx, const char *basename,
                             const char *filename)>
    WIN_JS_RunModule;
std::atomic<JSValue (*)(JSContext *ctx, JSCFunction *func, const char *name,
                        int length, JSCFunctionEnum cproto, int magic)>
    WIN_JS_NewCFunction2;
std::atomic<JSValue (*)(JSContext *ctx, JSCFunctionData *func, int length,
                        int magic, int data_len, JSValueConst *data)>
    WIN_JS_NewCFunctionData;
std::atomic<void (*)(JSContext *ctx, JSValueConst func_obj, JSValueConst proto)>
    WIN_JS_SetConstructor;
std::atomic<void (*)(JSContext *ctx, JSValueConst obj,
                     const JSCFunctionListEntry *tab, int len)>
    WIN_JS_SetPropertyFunctionList;
std::atomic<JSModuleDef *(*)(JSContext *ctx, const char *name_str,
                             JSModuleInitFunc *func)>
    WIN_JS_NewCModule;
std::atomic<int (*)(JSContext *ctx, JSModuleDef *m, const char *name_str)>
    WIN_JS_AddModuleExport;
std::atomic<int (*)(JSContext *ctx, JSModuleDef *m,
                    const JSCFunctionListEntry *tab, int len)>
    WIN_JS_AddModuleExportList;
std::atomic<int (*)(JSContext *ctx, JSModuleDef *m, const char *export_name,
                    JSValue val)>
    WIN_JS_SetModuleExport;
std::atomic<int (*)(JSContext *ctx, JSModuleDef *m,
                    const JSCFunctionListEntry *tab, int len)>
    WIN_JS_SetModuleExportList;
std::atomic<JSModuleDef *(*)(JSContext *ctx, const char *module_name)>
    WIN_js_init_module_std;
std::atomic<JSModuleDef *(*)(JSContext *ctx, const char *module_name)>
    WIN_js_init_module_os;
std::atomic<void (*)(JSContext *ctx, int argc, char **argv)>
    WIN_js_std_add_helpers;
std::atomic<void (*)(JSContext *ctx)> WIN_js_std_loop;
std::atomic<void (*)(JSRuntime *rt)> WIN_js_std_init_handlers;
std::atomic<void (*)(JSRuntime *rt)> WIN_js_std_free_handlers;
std::atomic<void (*)(JSContext *ctx)> WIN_js_std_dump_error;
std::atomic<uint8_t *(*)(JSContext *ctx, size_t *pbuf_len,
                         const char *filename)>
    WIN_js_load_file;
std::atomic<int (*)(JSContext *ctx, JSValueConst func_val, JS_BOOL use_realpath,
                    JS_BOOL is_main)>
    WIN_js_module_set_import_meta;
std::atomic<JSModuleDef *(*)(JSContext *ctx, const char *module_name,
                             void *opaque)>
    WIN_js_module_loader;
std::atomic<void (*)(JSContext *ctx, const uint8_t *buf, size_t buf_len,
                     int flags)>
    WIN_js_std_eval_binary;
std::atomic<void (*)(JSContext *ctx, JSValueConst promise, JSValueConst reason,
                     JS_BOOL is_handled, void *opaque)>
    WIN_js_std_promise_rejection_tracker;
std::atomic<void (*)(JSContext *(*func)(JSRuntime *rt))>
    WIN_js_std_set_worker_new_context_func;

static HMODULE _jsc_hl;
static int load_ok = 0;

void win_jsc_fn_init(const char *const path) {
    if (load_ok)
        return;

    _jsc_hl = LoadLibrary(path);

    WIN_JS_NewRuntime =
        (JSRuntime * (*)())(GetProcAddress(_jsc_hl, "JS_NewRuntime"));
    WIN_JS_NewContext = (JSContext * (*)(JSRuntime *))(
        GetProcAddress(_jsc_hl, "JS_NewContext"));
    WIN_JS_SetRuntimeInfo = (void (*)(JSRuntime *rt, const char *info))(
        GetProcAddress(_jsc_hl, "JS_SetRuntimeInfo"));
    WIN_JS_SetMemoryLimit = (void (*)(JSRuntime *rt, size_t limit))(
        GetProcAddress(_jsc_hl, "JS_SetMemoryLimit"));
    WIN_JS_SetGCThreshold = (void (*)(JSRuntime *rt, size_t gc_threshold))(
        GetProcAddress(_jsc_hl, "JS_SetGCThreshold"));
    WIN_JS_SetMaxStackSize = (void (*)(JSRuntime *rt, size_t stack_size))(
        GetProcAddress(_jsc_hl, "JS_SetMaxStackSize"));
    WIN_JS_UpdateStackTop =
        (void (*)(JSRuntime *rt))(GetProcAddress(_jsc_hl, "JS_UpdateStackTop"));
    WIN_JS_NewRuntime2 =
        (JSRuntime * (*)(const JSMallocFunctions *mf, void *opaque))(
            GetProcAddress(_jsc_hl, "JS_NewRuntime2"));
    WIN_JS_FreeRuntime =
        (void (*)(JSRuntime *rt))(GetProcAddress(_jsc_hl, "JS_FreeRuntime"));
    WIN_JS_GetRuntimeOpaque = (void *(*)(JSRuntime *rt))(
        GetProcAddress(_jsc_hl, "JS_GetRuntimeOpaque"));
    WIN_JS_SetRuntimeOpaque = (void (*)(JSRuntime *rt, void *opaque))(
        GetProcAddress(_jsc_hl, "JS_SetRuntimeOpaque"));
    WIN_JS_MarkValue =
        (void (*)(JSRuntime *rt, JSValueConst val, JS_MarkFunc *mark_func))(
            GetProcAddress(_jsc_hl, "JS_MarkValue"));
    WIN_JS_RunGC =
        (void (*)(JSRuntime *rt))(GetProcAddress(_jsc_hl, "JS_RunGC"));
    WIN_JS_IsLiveObject = (JS_BOOL(*)(JSRuntime * rt, JSValueConst obj))(
        GetProcAddress(_jsc_hl, "JS_IsLiveObject"));
    WIN_JS_NewContext = (JSContext * (*)(JSRuntime * rt))(
        GetProcAddress(_jsc_hl, "JS_NewContext"));
    WIN_JS_FreeContext =
        (void (*)(JSContext *s))(GetProcAddress(_jsc_hl, "JS_FreeContext"));
    WIN_JS_DupContext = (JSContext * (*)(JSContext * ctx))(
        GetProcAddress(_jsc_hl, "JS_DupContext"));
    WIN_JS_GetContextOpaque = (void *(*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_GetContextOpaque"));
    WIN_JS_SetContextOpaque = (void (*)(JSContext *ctx, void *opaque))(
        GetProcAddress(_jsc_hl, "JS_SetContextOpaque"));
    WIN_JS_GetRuntime = (JSRuntime * (*)(JSContext * ctx))(
        GetProcAddress(_jsc_hl, "JS_GetRuntime"));
    WIN_JS_SetClassProto =
        (void (*)(JSContext *ctx, JSClassID class_id, JSValue obj))(
            GetProcAddress(_jsc_hl, "JS_SetClassProto"));
    WIN_JS_GetClassProto = (JSValue(*)(JSContext * ctx, JSClassID class_id))(
        GetProcAddress(_jsc_hl, "JS_GetClassProto"));
    WIN_JS_NewContextRaw = (JSContext * (*)(JSRuntime * rt))(
        GetProcAddress(_jsc_hl, "JS_NewContextRaw"));
    WIN_JS_AddIntrinsicBaseObjects = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicBaseObjects"));
    WIN_JS_AddIntrinsicDate = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicDate"));
    WIN_JS_AddIntrinsicEval = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicEval"));
    WIN_JS_AddIntrinsicStringNormalize = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicStringNormalize"));
    WIN_JS_AddIntrinsicRegExpCompiler = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicRegExpCompiler"));
    WIN_JS_AddIntrinsicRegExp = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicRegExp"));
    WIN_JS_AddIntrinsicJSON = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicJSON"));
    WIN_JS_AddIntrinsicProxy = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicProxy"));
    WIN_JS_AddIntrinsicMapSet = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicMapSet"));
    WIN_JS_AddIntrinsicTypedArrays = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicTypedArrays"));
    WIN_JS_AddIntrinsicPromise = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicPromise"));
    WIN_JS_AddIntrinsicBigInt = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicBigInt"));
    WIN_JS_AddIntrinsicBigFloat = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicBigFloat"));
    WIN_JS_AddIntrinsicBigDecimal = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicBigDecimal"));
    WIN_JS_AddIntrinsicOperators = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_AddIntrinsicOperators"));
    WIN_JS_EnableBignumExt = (void (*)(JSContext *ctx, JS_BOOL enable))(
        GetProcAddress(_jsc_hl, "JS_EnableBignumExt"));
    WIN_js_string_codePointRange = (JSValue(*)(
        JSContext * ctx, JSValueConst this_val, int argc, JSValueConst *argv))(
        GetProcAddress(_jsc_hl, "js_string_codePointRange"));
    WIN_js_malloc_rt = (void *(*)(JSRuntime *rt, size_t size))(
        GetProcAddress(_jsc_hl, "js_malloc_rt"));
    WIN_js_free_rt = (void (*)(JSRuntime *rt, void *ptr))(
        GetProcAddress(_jsc_hl, "js_free_rt"));
    WIN_js_realloc_rt = (void *(*)(JSRuntime *rt, void *ptr, size_t size))(
        GetProcAddress(_jsc_hl, "js_realloc_rt"));
    WIN_js_malloc_usable_size_rt = (size_t(*)(JSRuntime * rt, const void *ptr))(
        GetProcAddress(_jsc_hl, "js_malloc_usable_size_rt"));
    WIN_js_mallocz_rt = (void *(*)(JSRuntime *rt, size_t size))(
        GetProcAddress(_jsc_hl, "js_mallocz_rt"));
    WIN_js_malloc = (void *(*)(JSContext *ctx, size_t size))(
        GetProcAddress(_jsc_hl, "js_malloc"));
    WIN_js_free = (void (*)(JSContext *ctx, void *ptr))(
        GetProcAddress(_jsc_hl, "js_free"));
    WIN_js_realloc = (void *(*)(JSContext *ctx, void *ptr, size_t size))(
        GetProcAddress(_jsc_hl, "js_realloc"));
    WIN_js_malloc_usable_size = (size_t(*)(JSContext * ctx, const void *ptr))(
        GetProcAddress(_jsc_hl, "js_malloc_usable_size"));
    WIN_js_realloc2 =
        (void *(*)(JSContext *ctx, void *ptr, size_t size, size_t *pslack))(
            GetProcAddress(_jsc_hl, "js_realloc2"));
    WIN_js_mallocz = (void *(*)(JSContext *ctx, size_t size))(
        GetProcAddress(_jsc_hl, "js_mallocz"));
    WIN_js_strdup = (char *(*)(JSContext *ctx, const char *str))(
        GetProcAddress(_jsc_hl, "js_strdup"));
    WIN_js_strndup = (char *(*)(JSContext *ctx, const char *s, size_t n))(
        GetProcAddress(_jsc_hl, "js_strndup"));
    WIN_JS_ComputeMemoryUsage = (void (*)(JSRuntime *rt, JSMemoryUsage *s))(
        GetProcAddress(_jsc_hl, "JS_ComputeMemoryUsage"));
    WIN_JS_DumpMemoryUsage =
        (void (*)(FILE *fp, const JSMemoryUsage *s, JSRuntime *rt))(
            GetProcAddress(_jsc_hl, "JS_DumpMemoryUsage"));
    WIN_JS_NewAtomLen =
        (JSAtom(*)(JSContext * ctx, const char *str, size_t len))(
            GetProcAddress(_jsc_hl, "JS_NewAtomLen"));
    WIN_JS_NewAtom = (JSAtom(*)(JSContext * ctx, const char *str))(
        GetProcAddress(_jsc_hl, "JS_NewAtom"));
    WIN_JS_NewAtomUInt32 = (JSAtom(*)(JSContext * ctx, uint32_t n))(
        GetProcAddress(_jsc_hl, "JS_NewAtomUInt32"));
    WIN_JS_DupAtom = (JSAtom(*)(JSContext * ctx, JSAtom v))(
        GetProcAddress(_jsc_hl, "JS_DupAtom"));
    WIN_JS_FreeAtom = (void (*)(JSContext *ctx, JSAtom v))(
        GetProcAddress(_jsc_hl, "JS_FreeAtom"));
    WIN_JS_FreeAtomRT = (void (*)(JSRuntime *rt, JSAtom v))(
        GetProcAddress(_jsc_hl, "JS_FreeAtomRT"));
    WIN_JS_AtomToValue = (JSValue(*)(JSContext * ctx, JSAtom atom))(
        GetProcAddress(_jsc_hl, "JS_AtomToValue"));
    WIN_JS_AtomToString = (JSValue(*)(JSContext * ctx, JSAtom atom))(
        GetProcAddress(_jsc_hl, "JS_AtomToString"));
    WIN_JS_AtomToCString = (const char *(*)(JSContext *ctx, JSAtom atom))(
        GetProcAddress(_jsc_hl, "JS_AtomToCString"));
    WIN_JS_ValueToAtom = (JSAtom(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_ValueToAtom"));
    WIN_JS_NewClassID = (JSClassID(*)(JSClassID * pclass_id))(
        GetProcAddress(_jsc_hl, "JS_NewClassID"));
    WIN_JS_NewClass = (int (*)(JSRuntime *rt, JSClassID class_id,
                               const JSClassDef *class_def))(
        GetProcAddress(_jsc_hl, "JS_NewClass"));
    WIN_JS_IsRegisteredClass = (int (*)(JSRuntime *rt, JSClassID class_id))(
        GetProcAddress(_jsc_hl, "JS_IsRegisteredClass"));
    WIN_JS_NewBigInt64 = (JSValue(*)(JSContext * ctx, int64_t v))(
        GetProcAddress(_jsc_hl, "JS_NewBigInt64"));
    WIN_JS_NewBigUint64 = (JSValue(*)(JSContext * ctx, uint64_t v))(
        GetProcAddress(_jsc_hl, "JS_NewBigUint64"));
    WIN_JS_Throw = (JSValue(*)(JSContext * ctx, JSValue obj))(
        GetProcAddress(_jsc_hl, "JS_Throw"));
    WIN_JS_GetException = (JSValue(*)(JSContext * ctx))(
        GetProcAddress(_jsc_hl, "JS_GetException"));
    WIN_JS_IsError = (JS_BOOL(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_IsError"));
    WIN_JS_ResetUncatchableError = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "JS_ResetUncatchableError"));
    WIN_JS_NewError =
        (JSValue(*)(JSContext * ctx))(GetProcAddress(_jsc_hl, "JS_NewError"));
    WIN_JS_ThrowSyntaxError = (JSValue __js_printf_like(2, 3)(*)(
        JSContext * ctx, const char *fmt, ...))(
        GetProcAddress(_jsc_hl, "JS_ThrowSyntaxError"));
    WIN_JS_ThrowTypeError = (JSValue __js_printf_like(2, 3)(*)(
        JSContext * ctx, const char *fmt, ...))(
        GetProcAddress(_jsc_hl, "JS_ThrowTypeError"));
    WIN_JS_ThrowReferenceError = (JSValue __js_printf_like(2, 3)(*)(
        JSContext * ctx, const char *fmt, ...))(
        GetProcAddress(_jsc_hl, "JS_ThrowReferenceError"));
    WIN_JS_ThrowRangeError = (JSValue __js_printf_like(2, 3)(*)(
        JSContext * ctx, const char *fmt, ...))(
        GetProcAddress(_jsc_hl, "JS_ThrowRangeError"));
    WIN_JS_ThrowInternalError = (JSValue __js_printf_like(2, 3)(*)(
        JSContext * ctx, const char *fmt, ...))(
        GetProcAddress(_jsc_hl, "JS_ThrowInternalError"));
    WIN_JS_ThrowOutOfMemory = (JSValue(*)(JSContext * ctx))(
        GetProcAddress(_jsc_hl, "JS_ThrowOutOfMemory"));
    WIN___JS_FreeValue = (void (*)(JSContext *ctx, JSValue v))(
        GetProcAddress(_jsc_hl, "__JS_FreeValue"));
    WIN___JS_FreeValueRT = (void (*)(JSRuntime *rt, JSValue v))(
        GetProcAddress(_jsc_hl, "__JS_FreeValueRT"));
    WIN_JS_ToBool = (int (*)(JSContext *ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_ToBool"));
    WIN_JS_ToInt32 = (int (*)(JSContext *ctx, int32_t *pres, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_ToInt32"));
    WIN_JS_ToInt64 = (int (*)(JSContext *ctx, int64_t *pres, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_ToInt64"));
    WIN_JS_ToIndex =
        (int (*)(JSContext *ctx, uint64_t *plen, JSValueConst val))(
            GetProcAddress(_jsc_hl, "JS_ToIndex"));
    WIN_JS_ToFloat64 =
        (int (*)(JSContext *ctx, double *pres, JSValueConst val))(
            GetProcAddress(_jsc_hl, "JS_ToFloat64"));
    WIN_JS_ToBigInt64 =
        (int (*)(JSContext *ctx, int64_t *pres, JSValueConst val))(
            GetProcAddress(_jsc_hl, "JS_ToBigInt64"));
    WIN_JS_ToInt64Ext =
        (int (*)(JSContext *ctx, int64_t *pres, JSValueConst val))(
            GetProcAddress(_jsc_hl, "JS_ToInt64Ext"));
    WIN_JS_NewStringLen =
        (JSValue(*)(JSContext * ctx, const char *str1, size_t len1))(
            GetProcAddress(_jsc_hl, "JS_NewStringLen"));
    WIN_JS_NewString = (JSValue(*)(JSContext * ctx, const char *str))(
        GetProcAddress(_jsc_hl, "JS_NewString"));
    WIN_JS_NewAtomString = (JSValue(*)(JSContext * ctx, const char *str))(
        GetProcAddress(_jsc_hl, "JS_NewAtomString"));
    WIN_JS_ToString = (JSValue(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_ToString"));
    WIN_JS_ToPropertyKey = (JSValue(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_ToPropertyKey"));
    WIN_JS_ToCStringLen2 = (const char *(*)(JSContext *ctx, size_t *plen,
                                            JSValueConst val1, JS_BOOL cesu8))(
        GetProcAddress(_jsc_hl, "JS_ToCStringLen2"));
    WIN_JS_FreeCString = (void (*)(JSContext *ctx, const char *ptr))(
        GetProcAddress(_jsc_hl, "JS_FreeCString"));
    WIN_JS_NewObjectProtoClass =
        (JSValue(*)(JSContext * ctx, JSValueConst proto, JSClassID class_id))(
            GetProcAddress(_jsc_hl, "JS_NewObjectProtoClass"));
    WIN_JS_NewObjectClass = (JSValue(*)(JSContext * ctx, int class_id))(
        GetProcAddress(_jsc_hl, "JS_NewObjectClass"));
    WIN_JS_NewObjectProto = (JSValue(*)(JSContext * ctx, JSValueConst proto))(
        GetProcAddress(_jsc_hl, "JS_NewObjectProto"));
    WIN_JS_NewObject =
        (JSValue(*)(JSContext * ctx))(GetProcAddress(_jsc_hl, "JS_NewObject"));
    WIN_JS_IsFunction = (JS_BOOL(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_IsFunction"));
    WIN_JS_IsConstructor = (JS_BOOL(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_IsConstructor"));
    WIN_JS_SetConstructorBit =
        (JS_BOOL(*)(JSContext * ctx, JSValueConst func_obj, JS_BOOL val))(
            GetProcAddress(_jsc_hl, "JS_SetConstructorBit"));
    WIN_JS_NewArray =
        (JSValue(*)(JSContext * ctx))(GetProcAddress(_jsc_hl, "JS_NewArray"));
    WIN_JS_IsArray = (int (*)(JSContext *ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_IsArray"));
    WIN_JS_GetPropertyInternal =
        (JSValue(*)(JSContext * ctx, JSValueConst obj, JSAtom prop,
                    JSValueConst receiver, JS_BOOL throw_ref_error))(
            GetProcAddress(_jsc_hl, "JS_GetPropertyInternal"));
    WIN_JS_GetPropertyStr =
        (JSValue(*)(JSContext * ctx, JSValueConst this_obj, const char *prop))(
            GetProcAddress(_jsc_hl, "JS_GetPropertyStr"));
    WIN_JS_GetPropertyUint32 =
        (JSValue(*)(JSContext * ctx, JSValueConst this_obj, uint32_t idx))(
            GetProcAddress(_jsc_hl, "JS_GetPropertyUint32"));
    WIN_JS_SetPropertyInternal = (int (*)(JSContext *ctx, JSValueConst this_obj,
                                          JSAtom prop, JSValue val, int flags))(
        GetProcAddress(_jsc_hl, "JS_SetPropertyInternal"));
    WIN_JS_SetPropertyUint32 =
        (int (*)(JSContext *ctx, JSValueConst this_obj, uint32_t idx,
                 JSValue val))(GetProcAddress(_jsc_hl, "JS_SetPropertyUint32"));
    WIN_JS_SetPropertyInt64 =
        (int (*)(JSContext *ctx, JSValueConst this_obj, int64_t idx,
                 JSValue val))(GetProcAddress(_jsc_hl, "JS_SetPropertyInt64"));
    WIN_JS_SetPropertyStr =
        (int (*)(JSContext *ctx, JSValueConst this_obj, const char *prop,
                 JSValue val))(GetProcAddress(_jsc_hl, "JS_SetPropertyStr"));
    WIN_JS_HasProperty =
        (int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop))(
            GetProcAddress(_jsc_hl, "JS_HasProperty"));
    WIN_JS_IsExtensible = (int (*)(JSContext *ctx, JSValueConst obj))(
        GetProcAddress(_jsc_hl, "JS_IsExtensible"));
    WIN_JS_PreventExtensions = (int (*)(JSContext *ctx, JSValueConst obj))(
        GetProcAddress(_jsc_hl, "JS_PreventExtensions"));
    WIN_JS_DeleteProperty =
        (int (*)(JSContext *ctx, JSValueConst obj, JSAtom prop, int flags))(
            GetProcAddress(_jsc_hl, "JS_DeleteProperty"));
    WIN_JS_SetPrototype =
        (int (*)(JSContext *ctx, JSValueConst obj, JSValueConst proto_val))(
            GetProcAddress(_jsc_hl, "JS_SetPrototype"));
    WIN_JS_GetPrototype = (JSValue(*)(JSContext * ctx, JSValueConst val))(
        GetProcAddress(_jsc_hl, "JS_GetPrototype"));
    WIN_JS_GetOwnPropertyNames = (int (*)(
        JSContext *ctx, JSPropertyEnum **ptab, uint32_t *plen, JSValueConst obj,
        int flags))(GetProcAddress(_jsc_hl, "JS_GetOwnPropertyNames"));
    WIN_JS_GetOwnProperty =
        (int (*)(JSContext *ctx, JSPropertyDescriptor *desc, JSValueConst obj,
                 JSAtom prop))(GetProcAddress(_jsc_hl, "JS_GetOwnProperty"));
    WIN_JS_Call = (JSValue(*)(
        JSContext * ctx, JSValueConst func_obj, JSValueConst this_obj, int argc,
        JSValueConst *argv))(GetProcAddress(_jsc_hl, "JS_Call"));
    WIN_JS_Invoke = (JSValue(*)(JSContext * ctx, JSValueConst this_val,
                                JSAtom atom, int argc, JSValueConst *argv))(
        GetProcAddress(_jsc_hl, "JS_Invoke"));
    WIN_JS_CallConstructor = (JSValue(*)(JSContext * ctx, JSValueConst func_obj,
                                         int argc, JSValueConst *argv))(
        GetProcAddress(_jsc_hl, "JS_CallConstructor"));
    WIN_JS_CallConstructor2 =
        (JSValue(*)(JSContext * ctx, JSValueConst func_obj,
                    JSValueConst new_target, int argc, JSValueConst *argv))(
            GetProcAddress(_jsc_hl, "JS_CallConstructor2"));
    WIN_JS_DetectModule = (JS_BOOL(*)(const char *input, size_t input_len))(
        GetProcAddress(_jsc_hl, "JS_DetectModule"));
    WIN_JS_Eval =
        (JSValue(*)(JSContext * ctx, const char *input, size_t input_len,
                    const char *filename,
                    int eval_flags))(GetProcAddress(_jsc_hl, "JS_Eval"));
    WIN_JS_EvalThis =
        (JSValue(*)(JSContext * ctx, JSValueConst this_obj, const char *input,
                    size_t input_len, const char *filename,
                    int eval_flags))(GetProcAddress(_jsc_hl, "JS_EvalThis"));
    WIN_JS_GetGlobalObject = (JSValue(*)(JSContext * ctx))(
        GetProcAddress(_jsc_hl, "JS_GetGlobalObject"));
    WIN_JS_IsInstanceOf =
        (int (*)(JSContext *ctx, JSValueConst val, JSValueConst obj))(
            GetProcAddress(_jsc_hl, "JS_IsInstanceOf"));
    WIN_JS_DefineProperty =
        (int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop,
                 JSValueConst val, JSValueConst getter, JSValueConst setter,
                 int flags))(GetProcAddress(_jsc_hl, "JS_DefineProperty"));
    WIN_JS_DefinePropertyValue = (int (*)(JSContext *ctx, JSValueConst this_obj,
                                          JSAtom prop, JSValue val, int flags))(
        GetProcAddress(_jsc_hl, "JS_DefinePropertyValue"));
    WIN_JS_DefinePropertyValueUint32 = (int (*)(
        JSContext *ctx, JSValueConst this_obj, uint32_t idx, JSValue val,
        int flags))(GetProcAddress(_jsc_hl, "JS_DefinePropertyValueUint32"));
    WIN_JS_DefinePropertyValueStr = (int (*)(
        JSContext *ctx, JSValueConst this_obj, const char *prop, JSValue val,
        int flags))(GetProcAddress(_jsc_hl, "JS_DefinePropertyValueStr"));
    WIN_JS_DefinePropertyGetSet =
        (int (*)(JSContext *ctx, JSValueConst this_obj, JSAtom prop,
                 JSValue getter, JSValue setter, int flags))(
            GetProcAddress(_jsc_hl, "JS_DefinePropertyGetSet"));
    WIN_JS_SetOpaque = (void (*)(JSValue obj, void *opaque))(
        GetProcAddress(_jsc_hl, "JS_SetOpaque"));
    WIN_JS_GetOpaque = (void *(*)(JSValueConst obj, JSClassID class_id))(
        GetProcAddress(_jsc_hl, "JS_GetOpaque"));
    WIN_JS_GetOpaque2 =
        (void *(*)(JSContext *ctx, JSValueConst obj, JSClassID class_id))(
            GetProcAddress(_jsc_hl, "JS_GetOpaque2"));
    WIN_JS_ParseJSON = (JSValue(*)(JSContext * ctx, const char *buf,
                                   size_t buf_len, const char *filename))(
        GetProcAddress(_jsc_hl, "JS_ParseJSON"));
    WIN_JS_ParseJSON2 = (JSValue(*)(
        JSContext * ctx, const char *buf, size_t buf_len, const char *filename,
        int flags))(GetProcAddress(_jsc_hl, "JS_ParseJSON2"));
    WIN_JS_JSONStringify = (JSValue(*)(
        JSContext * ctx, JSValueConst obj, JSValueConst replacer,
        JSValueConst space0))(GetProcAddress(_jsc_hl, "JS_JSONStringify"));
    WIN_JS_NewArrayBuffer = (JSValue(*)(
        JSContext * ctx, uint8_t * buf, size_t len,
        JSFreeArrayBufferDataFunc * free_func, void *opaque,
        JS_BOOL is_shared))(GetProcAddress(_jsc_hl, "JS_NewArrayBuffer"));
    WIN_JS_NewArrayBufferCopy =
        (JSValue(*)(JSContext * ctx, const uint8_t *buf, size_t len))(
            GetProcAddress(_jsc_hl, "JS_NewArrayBufferCopy"));
    WIN_JS_DetachArrayBuffer = (void (*)(JSContext *ctx, JSValueConst obj))(
        GetProcAddress(_jsc_hl, "JS_DetachArrayBuffer"));
    WIN_JS_GetArrayBuffer =
        (uint8_t * (*)(JSContext * ctx, size_t * psize, JSValueConst obj))(
            GetProcAddress(_jsc_hl, "JS_GetArrayBuffer"));
    WIN_JS_GetTypedArrayBuffer =
        (JSValue(*)(JSContext * ctx, JSValueConst obj, size_t * pbyte_offset,
                    size_t * pbyte_length, size_t * pbytes_per_element))(
            GetProcAddress(_jsc_hl, "JS_GetTypedArrayBuffer"));
    WIN_JS_SetSharedArrayBufferFunctions =
        (void (*)(JSRuntime *rt, const JSSharedArrayBufferFunctions *sf))(
            GetProcAddress(_jsc_hl, "JS_SetSharedArrayBufferFunctions"));
    WIN_JS_NewPromiseCapability =
        (JSValue(*)(JSContext * ctx, JSValue * resolving_funcs))(
            GetProcAddress(_jsc_hl, "JS_NewPromiseCapability"));
    WIN_JS_SetHostPromiseRejectionTracker = (void (*)(
        JSRuntime *rt, JSHostPromiseRejectionTracker *cb, void *opaque))(
        GetProcAddress(_jsc_hl, "JS_SetHostPromiseRejectionTracker"));
    WIN_JS_SetInterruptHandler =
        (void (*)(JSRuntime *rt, JSInterruptHandler *cb, void *opaque))(
            GetProcAddress(_jsc_hl, "JS_SetInterruptHandler"));
    WIN_JS_SetCanBlock = (void (*)(JSRuntime *rt, JS_BOOL can_block))(
        GetProcAddress(_jsc_hl, "JS_SetCanBlock"));
    WIN_JS_SetIsHTMLDDA = (void (*)(JSContext *ctx, JSValueConst obj))(
        GetProcAddress(_jsc_hl, "JS_SetIsHTMLDDA"));
    WIN_JS_SetModuleLoaderFunc =
        (void (*)(JSRuntime *rt, JSModuleNormalizeFunc *module_normalize,
                  JSModuleLoaderFunc *module_loader, void *opaque))(
            GetProcAddress(_jsc_hl, "JS_SetModuleLoaderFunc"));
    WIN_JS_GetImportMeta = (JSValue(*)(JSContext * ctx, JSModuleDef * m))(
        GetProcAddress(_jsc_hl, "JS_GetImportMeta"));
    WIN_JS_GetModuleName = (JSAtom(*)(JSContext * ctx, JSModuleDef * m))(
        GetProcAddress(_jsc_hl, "JS_GetModuleName"));
    WIN_JS_EnqueueJob =
        (int (*)(JSContext *ctx, JSJobFunc *job_func, int argc,
                 JSValueConst *argv))(GetProcAddress(_jsc_hl, "JS_EnqueueJob"));
    WIN_JS_IsJobPending = (JS_BOOL(*)(JSRuntime * rt))(
        GetProcAddress(_jsc_hl, "JS_IsJobPending"));
    WIN_JS_ExecutePendingJob = (int (*)(JSRuntime *rt, JSContext **pctx))(
        GetProcAddress(_jsc_hl, "JS_ExecutePendingJob"));
    WIN_JS_WriteObject =
        (uint8_t * (*)(JSContext * ctx, size_t * psize, JSValueConst obj,
                       int flags))(GetProcAddress(_jsc_hl, "JS_WriteObject"));
    WIN_JS_WriteObject2 =
        (uint8_t * (*)(JSContext * ctx, size_t * psize, JSValueConst obj,
                       int flags, uint8_t ***psab_tab, size_t *psab_tab_len))(
            GetProcAddress(_jsc_hl, "JS_WriteObject2"));
    WIN_JS_ReadObject =
        (JSValue(*)(JSContext * ctx, const uint8_t *buf, size_t buf_len,
                    int flags))(GetProcAddress(_jsc_hl, "JS_ReadObject"));
    WIN_JS_EvalFunction = (JSValue(*)(JSContext * ctx, JSValue fun_obj))(
        GetProcAddress(_jsc_hl, "JS_EvalFunction"));
    WIN_JS_ResolveModule = (int (*)(JSContext *ctx, JSValueConst obj))(
        GetProcAddress(_jsc_hl, "JS_ResolveModule"));
    WIN_JS_GetScriptOrModuleName =
        (JSAtom(*)(JSContext * ctx, int n_stack_levels))(
            GetProcAddress(_jsc_hl, "JS_GetScriptOrModuleName"));
    WIN_JS_RunModule = (JSModuleDef * (*)(JSContext * ctx, const char *basename,
                                          const char *filename))(
        GetProcAddress(_jsc_hl, "JS_RunModule"));
    WIN_JS_NewCFunction2 =
        (JSValue(*)(JSContext * ctx, JSCFunction * func, const char *name,
                    int length, JSCFunctionEnum cproto,
                    int magic))(GetProcAddress(_jsc_hl, "JS_NewCFunction2"));
    WIN_JS_NewCFunctionData =
        (JSValue(*)(JSContext * ctx, JSCFunctionData * func, int length,
                    int magic, int data_len, JSValueConst *data))(
            GetProcAddress(_jsc_hl, "JS_NewCFunctionData"));
    WIN_JS_SetConstructor =
        (void (*)(JSContext *ctx, JSValueConst func_obj, JSValueConst proto))(
            GetProcAddress(_jsc_hl, "JS_SetConstructor"));
    WIN_JS_SetPropertyFunctionList = (void (*)(
        JSContext *ctx, JSValueConst obj, const JSCFunctionListEntry *tab,
        int len))(GetProcAddress(_jsc_hl, "JS_SetPropertyFunctionList"));
    WIN_JS_NewCModule =
        (JSModuleDef *
         (*)(JSContext * ctx, const char *name_str, JSModuleInitFunc *func))(
            GetProcAddress(_jsc_hl, "JS_NewCModule"));
    WIN_JS_AddModuleExport =
        (int (*)(JSContext *ctx, JSModuleDef *m, const char *name_str))(
            GetProcAddress(_jsc_hl, "JS_AddModuleExport"));
    WIN_JS_AddModuleExportList = (int (*)(
        JSContext *ctx, JSModuleDef *m, const JSCFunctionListEntry *tab,
        int len))(GetProcAddress(_jsc_hl, "JS_AddModuleExportList"));
    WIN_JS_SetModuleExport =
        (int (*)(JSContext *ctx, JSModuleDef *m, const char *export_name,
                 JSValue val))(GetProcAddress(_jsc_hl, "JS_SetModuleExport"));
    WIN_JS_SetModuleExportList = (int (*)(
        JSContext *ctx, JSModuleDef *m, const JSCFunctionListEntry *tab,
        int len))(GetProcAddress(_jsc_hl, "JS_SetModuleExportList"));
    WIN_js_init_module_std =
        (JSModuleDef * (*)(JSContext * ctx, const char *module_name))(
            GetProcAddress(_jsc_hl, "js_init_module_std"));
    WIN_js_init_module_os =
        (JSModuleDef * (*)(JSContext * ctx, const char *module_name))(
            GetProcAddress(_jsc_hl, "js_init_module_os"));
    WIN_js_std_add_helpers = (void (*)(JSContext *ctx, int argc, char **argv))(
        GetProcAddress(_jsc_hl, "js_std_add_helpers"));
    WIN_js_std_loop =
        (void (*)(JSContext *ctx))(GetProcAddress(_jsc_hl, "js_std_loop"));
    WIN_js_std_init_handlers = (void (*)(JSRuntime *rt))(
        GetProcAddress(_jsc_hl, "js_std_init_handlers"));
    WIN_js_std_free_handlers = (void (*)(JSRuntime *rt))(
        GetProcAddress(_jsc_hl, "js_std_free_handlers"));
    WIN_js_std_dump_error = (void (*)(JSContext *ctx))(
        GetProcAddress(_jsc_hl, "js_std_dump_error"));
    WIN_js_load_file = (uint8_t * (*)(JSContext * ctx, size_t * pbuf_len,
                                      const char *filename))(
        GetProcAddress(_jsc_hl, "js_load_file"));
    WIN_js_module_set_import_meta = (int (*)(
        JSContext *ctx, JSValueConst func_val, JS_BOOL use_realpath,
        JS_BOOL is_main))(GetProcAddress(_jsc_hl, "js_module_set_import_meta"));
    WIN_js_module_loader =
        (JSModuleDef *
         (*)(JSContext * ctx, const char *module_name, void *opaque))(
            GetProcAddress(_jsc_hl, "js_module_loader"));
    WIN_js_std_eval_binary =
        (void (*)(JSContext *ctx, const uint8_t *buf, size_t buf_len,
                  int flags))(GetProcAddress(_jsc_hl, "js_std_eval_binary"));
    WIN_js_std_promise_rejection_tracker =
        (void (*)(JSContext *ctx, JSValueConst promise, JSValueConst reason,
                  JS_BOOL is_handled, void *opaque))(
            GetProcAddress(_jsc_hl, "js_std_promise_rejection_tracker"));
    WIN_js_std_set_worker_new_context_func =
        (void (*)(JSContext *(*func)(JSRuntime *rt)))(
            GetProcAddress(_jsc_hl, "js_std_set_worker_new_context_func"));

    load_ok = 1;
}

int win_jsc_fn_free() {
    if (!load_ok)
        return 0;

    return FreeLibrary(_jsc_hl);
}