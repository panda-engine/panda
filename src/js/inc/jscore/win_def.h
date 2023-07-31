
#ifndef win_def_h_
#define win_def_h_


#include "quickjs-libc.h"
#include <windows.h>

#ifdef __cplusplus
#include <atomic>
extern std::atomic<HMODULE> _jsc_hl;
extern "C"{
#endif

typedef JSRuntime * (*JS_NewRuntime_t)();
typedef JSContext * (*JS_NewContext_t)(JSRuntime *);
typedef void (*JS_SetRuntimeInfo_t)(JSRuntime *rt, const char *info);
typedef void (*JS_SetMemoryLimit_t)(JSRuntime *rt, size_t limit);
typedef void (*JS_SetGCThreshold_t)(JSRuntime *rt, size_t gc_threshold);
typedef void (*JS_SetMaxStackSize_t)(JSRuntime *rt, size_t stack_size);
typedef void (*JS_UpdateStackTop_t)(JSRuntime *rt);
typedef JSRuntime *(*JS_NewRuntime2_t)(const JSMallocFunctions *mf, void *opaque);
typedef void (*JS_FreeRuntime_t)(JSRuntime *rt);
typedef void *(*JS_GetRuntimeOpaque_t)(JSRuntime *rt);
typedef void (*JS_SetRuntimeOpaque_t)(JSRuntime *rt, void *opaque);
typedef void (*JS_MarkValue_t)(JSRuntime *rt, JSValueConst val, JS_MarkFunc *mark_func);
typedef void (*JS_RunGC_t)(JSRuntime *rt);
typedef JS_BOOL (*JS_IsLiveObject_t)(JSRuntime *rt, JSValueConst obj);
typedef JSContext *(*JS_NewContext_t)(JSRuntime *rt);
typedef void (*JS_FreeContext_t)(JSContext *s);
typedef JSContext *(*JS_DupContext_t)(JSContext *ctx);
typedef void *(*JS_GetContextOpaque_t)(JSContext *ctx);
typedef void (*JS_SetContextOpaque_t)(JSContext *ctx, void *opaque);
typedef JSRuntime *(*JS_GetRuntime_t)(JSContext *ctx);
typedef void (*JS_SetClassProto_t)(JSContext *ctx, JSClassID class_id, JSValue obj);
typedef JSValue (*JS_GetClassProto_t)(JSContext *ctx, JSClassID class_id);
typedef JSContext *(*JS_NewContextRaw_t)(JSRuntime *rt);
typedef void (*JS_AddIntrinsicBaseObjects_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicDate_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicEval_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicStringNormalize_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicRegExpCompiler_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicRegExp_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicJSON_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicProxy_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicMapSet_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicTypedArrays_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicPromise_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicBigInt_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicBigFloat_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicBigDecimal_t)(JSContext *ctx);
typedef void (*JS_AddIntrinsicOperators_t)(JSContext *ctx);
typedef void (*JS_EnableBignumExt_t)(JSContext *ctx, JS_BOOL enable);
typedef JSValue (*js_string_codePointRange_t)(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);
typedef void *(*js_malloc_rt_t)(JSRuntime *rt, size_t size);
typedef void (*js_free_rt_t)(JSRuntime *rt, void *ptr);
typedef void *(*js_realloc_rt_t)(JSRuntime *rt, void *ptr, size_t size);
typedef size_t (*js_malloc_usable_size_rt_t)(JSRuntime *rt, const void *ptr);
typedef void *(*js_mallocz_rt_t)(JSRuntime *rt, size_t size);
typedef void *(*js_malloc_t)(JSContext *ctx, size_t size);
typedef void (*js_free_t)(JSContext *ctx, void *ptr);
typedef void *(*js_realloc_t)(JSContext *ctx, void *ptr, size_t size);
typedef size_t (*js_malloc_usable_size_t)(JSContext *ctx, const void *ptr);
typedef void *(*js_realloc2_t)(JSContext *ctx, void *ptr, size_t size, size_t *pslack);
typedef void *(*js_mallocz_t)(JSContext *ctx, size_t size);
typedef char *(*js_strdup_t)(JSContext *ctx, const char *str);
typedef char *(*js_strndup_t)(JSContext *ctx, const char *s, size_t n);
typedef void (*JS_ComputeMemoryUsage_t)(JSRuntime *rt, JSMemoryUsage *s);
typedef void (*JS_DumpMemoryUsage_t)(FILE *fp, const JSMemoryUsage *s, JSRuntime *rt);
typedef JSAtom (*JS_NewAtomLen_t)(JSContext *ctx, const char *str, size_t len);
typedef JSAtom (*JS_NewAtom_t)(JSContext *ctx, const char *str);
typedef JSAtom (*JS_NewAtomUInt32_t)(JSContext *ctx, uint32_t n);
typedef JSAtom (*JS_DupAtom_t)(JSContext *ctx, JSAtom v);
typedef void (*JS_FreeAtom_t)(JSContext *ctx, JSAtom v);
typedef void (*JS_FreeAtomRT_t)(JSRuntime *rt, JSAtom v);
typedef JSValue (*JS_AtomToValue_t)(JSContext *ctx, JSAtom atom);
typedef JSValue (*JS_AtomToString_t)(JSContext *ctx, JSAtom atom);
typedef const char *(*JS_AtomToCString_t)(JSContext *ctx, JSAtom atom);
typedef JSAtom (*JS_ValueToAtom_t)(JSContext *ctx, JSValueConst val);
typedef JSClassID (*JS_NewClassID_t)(JSClassID *pclass_id);
typedef int (*JS_NewClass_t)(JSRuntime *rt, JSClassID class_id, const JSClassDef *class_def);
typedef int (*JS_IsRegisteredClass_t)(JSRuntime *rt, JSClassID class_id);
typedef JSValue (*JS_NewBigInt64_t)(JSContext *ctx, int64_t v);
typedef JSValue (*JS_NewBigUint64_t)(JSContext *ctx, uint64_t v);
typedef JSValue (*JS_Throw_t)(JSContext *ctx, JSValue obj);
typedef JSValue (*JS_GetException_t)(JSContext *ctx);
typedef JS_BOOL (*JS_IsError_t)(JSContext *ctx, JSValueConst val);
typedef void (*JS_ResetUncatchableError_t)(JSContext *ctx);
typedef JSValue (*JS_NewError_t)(JSContext *ctx);
typedef JSValue __js_printf_like(2, 3) (*JS_ThrowSyntaxError_t)(JSContext *ctx, const char *fmt, ...);
typedef JSValue __js_printf_like(2, 3) (*JS_ThrowTypeError_t)(JSContext *ctx, const char *fmt, ...);
typedef JSValue __js_printf_like(2, 3) (*JS_ThrowReferenceError_t)(JSContext *ctx, const char *fmt, ...);
typedef JSValue __js_printf_like(2, 3) (*JS_ThrowRangeError_t)(JSContext *ctx, const char *fmt, ...);
typedef JSValue __js_printf_like(2, 3) (*JS_ThrowInternalError_t)(JSContext *ctx, const char *fmt, ...);
typedef JSValue (*JS_ThrowOutOfMemory_t)(JSContext *ctx);
typedef void (*__JS_FreeValue_t)(JSContext *ctx, JSValue v);
typedef void (*__JS_FreeValueRT_t)(JSRuntime *rt, JSValue v);
typedef int (*JS_ToBool_t)(JSContext *ctx, JSValueConst val);
typedef int (*JS_ToInt32_t)(JSContext *ctx, int32_t *pres, JSValueConst val);
typedef int (*JS_ToInt64_t)(JSContext *ctx, int64_t *pres, JSValueConst val);
typedef int (*JS_ToIndex_t)(JSContext *ctx, uint64_t *plen, JSValueConst val);
typedef int (*JS_ToFloat64_t)(JSContext *ctx, double *pres, JSValueConst val);
typedef int (*JS_ToBigInt64_t)(JSContext *ctx, int64_t *pres, JSValueConst val);
typedef int (*JS_ToInt64Ext_t)(JSContext *ctx, int64_t *pres, JSValueConst val);
typedef JSValue (*JS_NewStringLen_t)(JSContext *ctx, const char *str1, size_t len1);
typedef JSValue (*JS_NewString_t)(JSContext *ctx, const char *str);
typedef JSValue (*JS_NewAtomString_t)(JSContext *ctx, const char *str);
typedef JSValue (*JS_ToString_t)(JSContext *ctx, JSValueConst val);
typedef JSValue (*JS_ToPropertyKey_t)(JSContext *ctx, JSValueConst val);
typedef const char *(*JS_ToCStringLen2_t)(JSContext *ctx, size_t *plen, JSValueConst val1, JS_BOOL cesu8);
typedef void (*JS_FreeCString_t)(JSContext *ctx, const char *ptr);
typedef JSValue (*JS_NewObjectProtoClass_t)(JSContext *ctx, JSValueConst proto, JSClassID class_id);
typedef JSValue (*JS_NewObjectClass_t)(JSContext *ctx, int class_id);
typedef JSValue (*JS_NewObjectProto_t)(JSContext *ctx, JSValueConst proto);
typedef JSValue (*JS_NewObject_t)(JSContext *ctx);
typedef JS_BOOL (*JS_IsFunction_t)(JSContext* ctx, JSValueConst val);
typedef JS_BOOL (*JS_IsConstructor_t)(JSContext* ctx, JSValueConst val);
typedef JS_BOOL (*JS_SetConstructorBit_t)(JSContext *ctx, JSValueConst func_obj, JS_BOOL val);
typedef JSValue (*JS_NewArray_t)(JSContext *ctx);
typedef int (*JS_IsArray_t)(JSContext *ctx, JSValueConst val);
typedef JSValue (*JS_GetPropertyInternal_t)(JSContext *ctx, JSValueConst obj,JSAtom prop, JSValueConst receiver,JS_BOOL throw_ref_error);
typedef JSValue (*JS_GetPropertyStr_t)(JSContext *ctx, JSValueConst this_obj,const char *prop);
typedef JSValue (*JS_GetPropertyUint32_t)(JSContext *ctx, JSValueConst this_obj,uint32_t idx);
typedef int (*JS_SetPropertyInternal_t)(JSContext *ctx, JSValueConst this_obj,JSAtom prop, JSValue val,int flags);
typedef int (*JS_SetPropertyUint32_t)(JSContext *ctx, JSValueConst this_obj,uint32_t idx, JSValue val);
typedef int (*JS_SetPropertyInt64_t)(JSContext *ctx, JSValueConst this_obj,int64_t idx, JSValue val);
typedef int (*JS_SetPropertyStr_t)(JSContext *ctx, JSValueConst this_obj, const char *prop, JSValue val);
typedef int (*JS_HasProperty_t)(JSContext *ctx, JSValueConst this_obj, JSAtom prop);
typedef int (*JS_IsExtensible_t)(JSContext *ctx, JSValueConst obj);
typedef int (*JS_PreventExtensions_t)(JSContext *ctx, JSValueConst obj);
typedef int (*JS_DeleteProperty_t)(JSContext *ctx, JSValueConst obj, JSAtom prop, int flags);
typedef int (*JS_SetPrototype_t)(JSContext *ctx, JSValueConst obj, JSValueConst proto_val);
typedef JSValue (*JS_GetPrototype_t)(JSContext *ctx, JSValueConst val);
typedef int (*JS_GetOwnPropertyNames_t)(JSContext *ctx, JSPropertyEnum **ptab, uint32_t *plen, JSValueConst obj, int flags);
typedef int (*JS_GetOwnProperty_t)(JSContext *ctx, JSPropertyDescriptor *desc, JSValueConst obj, JSAtom prop);
typedef JSValue (*JS_Call_t)(JSContext *ctx, JSValueConst func_obj, JSValueConst this_obj, int argc, JSValueConst *argv);
typedef JSValue (*JS_Invoke_t)(JSContext *ctx, JSValueConst this_val, JSAtom atom, int argc, JSValueConst *argv);
typedef JSValue (*JS_CallConstructor_t)(JSContext *ctx, JSValueConst func_obj, int argc, JSValueConst *argv);
typedef JSValue (*JS_CallConstructor2_t)(JSContext *ctx, JSValueConst func_obj,JSValueConst new_target, int argc, JSValueConst *argv);
typedef JS_BOOL (*JS_DetectModule_t)(const char *input, size_t input_len);
typedef JSValue (*JS_Eval_t)(JSContext *ctx, const char *input, size_t input_len,const char *filename, int eval_flags);
typedef JSValue (*JS_EvalThis_t)(JSContext *ctx, JSValueConst this_obj, const char *input, size_t input_len, const char *filename, int eval_flags);
typedef JSValue (*JS_GetGlobalObject_t)(JSContext *ctx);
typedef int (*JS_IsInstanceOf_t)(JSContext *ctx, JSValueConst val, JSValueConst obj);
typedef int (*JS_DefineProperty_t)(JSContext *ctx, JSValueConst this_obj, JSAtom prop, JSValueConst val, JSValueConst getter, JSValueConst setter, int flags);
typedef int (*JS_DefinePropertyValue_t)(JSContext *ctx, JSValueConst this_obj,JSAtom prop, JSValue val, int flags);
typedef int (*JS_DefinePropertyValueUint32_t)(JSContext *ctx, JSValueConst this_obj,uint32_t idx, JSValue val, int flags);
typedef int (*JS_DefinePropertyValueStr_t)(JSContext *ctx, JSValueConst this_obj,  const char *prop, JSValue val, int flags);
typedef int (*JS_DefinePropertyGetSet_t)(JSContext *ctx, JSValueConst this_obj, JSAtom prop, JSValue getter, JSValue setter,int flags);
typedef void (*JS_SetOpaque_t)(JSValue obj, void *opaque);
typedef void *(*JS_GetOpaque_t)(JSValueConst obj, JSClassID class_id);
typedef void *(*JS_GetOpaque2_t)(JSContext *ctx, JSValueConst obj, JSClassID class_id);
typedef JSValue (*JS_ParseJSON_t)(JSContext *ctx, const char *buf, size_t buf_len, const char *filename);
typedef JSValue (*JS_ParseJSON2_t)(JSContext *ctx, const char *buf, size_t buf_len, const char *filename, int flags);
typedef JSValue (*JS_JSONStringify_t)(JSContext *ctx, JSValueConst obj, JSValueConst replacer, JSValueConst space0);
typedef JSValue (*JS_NewArrayBuffer_t)(JSContext *ctx, uint8_t *buf, size_t len, JSFreeArrayBufferDataFunc *free_func, void *opaque, JS_BOOL is_shared);
typedef JSValue (*JS_NewArrayBufferCopy_t)(JSContext *ctx, const uint8_t *buf, size_t len);
typedef void (*JS_DetachArrayBuffer_t)(JSContext *ctx, JSValueConst obj);
typedef uint8_t *(*JS_GetArrayBuffer_t)(JSContext *ctx, size_t *psize, JSValueConst obj);
typedef JSValue (*JS_GetTypedArrayBuffer_t)(JSContext *ctx, JSValueConst obj, size_t *pbyte_offset, size_t *pbyte_length, size_t *pbytes_per_element);
typedef void (*JS_SetSharedArrayBufferFunctions_t)(JSRuntime *rt, const JSSharedArrayBufferFunctions *sf);
typedef JSValue (*JS_NewPromiseCapability_t)(JSContext *ctx, JSValue *resolving_funcs);
typedef void (*JS_SetHostPromiseRejectionTracker_t)(JSRuntime *rt, JSHostPromiseRejectionTracker *cb, void *opaque);
typedef void (*JS_SetInterruptHandler_t)(JSRuntime *rt, JSInterruptHandler *cb, void *opaque);
typedef void (*JS_SetCanBlock_t)(JSRuntime *rt, JS_BOOL can_block);
typedef void (*JS_SetIsHTMLDDA_t)(JSContext *ctx, JSValueConst obj);
typedef void (*JS_SetModuleLoaderFunc_t)(JSRuntime *rt, JSModuleNormalizeFunc *module_normalize, JSModuleLoaderFunc *module_loader, void *opaque);
typedef JSValue (*JS_GetImportMeta_t)(JSContext *ctx, JSModuleDef *m);
typedef JSAtom (*JS_GetModuleName_t)(JSContext *ctx, JSModuleDef *m);
typedef int (*JS_EnqueueJob_t)(JSContext *ctx, JSJobFunc *job_func, int argc, JSValueConst *argv);
typedef JS_BOOL (*JS_IsJobPending_t)(JSRuntime *rt);
typedef int (*JS_ExecutePendingJob_t)(JSRuntime *rt, JSContext **pctx);
typedef uint8_t *(*JS_WriteObject_t)(JSContext *ctx, size_t *psize, JSValueConst obj, int flags);
typedef uint8_t *(*JS_WriteObject2_t)(JSContext *ctx, size_t *psize, JSValueConst obj, int flags, uint8_t ***psab_tab, size_t *psab_tab_len);
typedef JSValue (*JS_ReadObject_t)(JSContext *ctx, const uint8_t *buf, size_t buf_len, int flags);
typedef JSValue (*JS_EvalFunction_t)(JSContext *ctx, JSValue fun_obj);
typedef int (*JS_ResolveModule_t)(JSContext *ctx, JSValueConst obj);
typedef JSAtom (*JS_GetScriptOrModuleName_t)(JSContext *ctx, int n_stack_levels);
typedef JSModuleDef *(*JS_RunModule_t)(JSContext *ctx, const char *basename, const char *filename);
typedef JSValue (*JS_NewCFunction2_t)(JSContext *ctx, JSCFunction *func, const char *name,int length, JSCFunctionEnum cproto, int magic);
typedef JSValue (*JS_NewCFunctionData_t)(JSContext *ctx, JSCFunctionData *func, int length, int magic, int data_len,JSValueConst *data);
typedef void (*JS_SetConstructor_t)(JSContext *ctx, JSValueConst func_obj, JSValueConst proto);
typedef void (*JS_SetPropertyFunctionList_t)(JSContext *ctx, JSValueConst obj,const JSCFunctionListEntry *tab,int len);
typedef JSModuleDef *(*JS_NewCModule_t)(JSContext *ctx, const char *name_str,  JSModuleInitFunc *func);
typedef int (*JS_AddModuleExport_t)(JSContext *ctx, JSModuleDef *m, const char *name_str);
typedef int (*JS_AddModuleExportList_t)(JSContext *ctx, JSModuleDef *m, const JSCFunctionListEntry *tab, int len);
typedef int (*JS_SetModuleExport_t)(JSContext *ctx, JSModuleDef *m, const char *export_name, JSValue val);
typedef int (*JS_SetModuleExportList_t)(JSContext *ctx, JSModuleDef *m, const JSCFunctionListEntry *tab, int len);
typedef JSModuleDef *(*js_init_module_std_t)(JSContext *ctx, const char *module_name);
typedef JSModuleDef *(*js_init_module_os_t)(JSContext *ctx, const char *module_name);
typedef void (*js_std_add_helpers_t)(JSContext *ctx, int argc, char **argv);
typedef void (*js_std_loop_t)(JSContext *ctx);
typedef void (*js_std_init_handlers_t)(JSRuntime *rt);
typedef void (*js_std_free_handlers_t)(JSRuntime *rt);
typedef void (*js_std_dump_error_t)(JSContext *ctx);
typedef uint8_t *(*js_load_file_t)(JSContext *ctx, size_t *pbuf_len, const char *filename);
typedef int (*js_module_set_import_meta_t)(JSContext *ctx, JSValueConst func_val, JS_BOOL use_realpath, JS_BOOL is_main);
typedef JSModuleDef *(*js_module_loader_t)(JSContext *ctx, const char *module_name, void *opaque);
typedef void (*js_std_eval_binary_t)(JSContext *ctx, const uint8_t *buf, size_t buf_len, int flags);
typedef void (*js_std_promise_rejection_tracker_t)(JSContext *ctx, JSValueConst promise, JSValueConst reason, JS_BOOL is_handled, void *opaque);
typedef void (*js_std_set_worker_new_context_func_t)(JSContext *(*func)(JSRuntime *rt));

void win_jsc_fn_init(const char* const path);
int win_jsc_fn_free();
void *win_jsc_fn_call(const char* fn_name);

#ifdef __cplusplus
}
#endif

#endif

