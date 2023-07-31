

#include "jscore/win_def.h"
#include <atomic>

std::atomic<HMODULE> _jsc_hl;
#define jl_load _jsc_hl.load(std::memory_order_acquire)

void win_jsc_fn_init(const char *const path) {
    if (jl_load)
        return;

    _jsc_hl.store(LoadLibrary(path), std::memory_order_release);
}

int win_jsc_fn_free() {
    if (!jl_load)
        return 0;

    return FreeLibrary(_jsc_hl);
}

void *win_jsc_fn_call(const char* fn_name){
    return (void *)GetProcAddress(jl_load, fn_name);
}