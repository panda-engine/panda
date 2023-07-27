#include "log.h"

#include <cstdarg>
#include <cassert>

std::atomic_bool log_s[4] = {{false}};

static void init(){
    for (int i = 0; i < 4; ++i) {
        log_s[i].store(false, std::memory_order_release);
    }
}

void set_log(log_grade g){
    if (g == debug) {
        log_s[0].store(true, std::memory_order_release);
    } else if (g == info) {
        log_s[1].store(true, std::memory_order_release);
    } else if (g == warn) {
        log_s[2].store(true, std::memory_order_release);
    } else if (g == error) {
        log_s[3].store(true, std::memory_order_release);
    } else if (g == all) {
        set_log(debug);
        set_log(info);
        set_log(warn);
        set_log(error);
    } else {
        init();
    }
}