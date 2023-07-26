#include "log.h"

#include <cstdarg>
#include <cassert>

struct _log panda_log;
struct _log_c panda_log_c;
static bool init_ok = false;
static bool init_ok_c = false;

static void init(){
    for (int i = 0; i < 5; ++i) {
        panda_log.log_s[i] = false;
    }
    init_ok = true;
}

void set_log(log_grade g){
    if(!init_ok) init();
    if (g == debug) {
        panda_log.log_s[0] = true;
    } else if (g == info) {
        panda_log.log_s[1] = true;
    } else if (g == warn) {
        panda_log.log_s[2] = true;
    } else if (g == error) {
        panda_log.log_s[3] = true;
    } else if (g == fatal) {
        panda_log.log_s[4] = true;
    } else if (g == all) {
        set_log(debug);
        set_log(info);
        set_log(warn);
        set_log(error);
        set_log(fatal);
    } else {
        init();
    }
}

static constexpr inline void print_null(const char* const str) {
    return;
}

static void print_s(const char* const str) {
    printf_s(str);
}

static inline void init_c(){
    panda_log_c.debug = print_null;
    panda_log_c.info = print_null;
    panda_log_c.warn = print_null;
    panda_log_c.error = print_null;
    panda_log_c.fatal = print_null;
    init_ok_c = true;
}

void set_log_c(log_grade g){
    if(!init_ok_c) init_c();
    if (g == debug) {
        panda_log_c.debug = print_s;
    } else if (g == info) {
        panda_log_c.info = print_s;
    } else if (g == warn) {
        panda_log_c.warn = print_s;
    } else if (g == error) {
        panda_log_c.error = print_s;
    } else if (g == fatal) {
        panda_log_c.fatal = print_s;
    } else if (g == all) {
        set_log_c(debug);
        set_log_c(info);
        set_log_c(warn);
        set_log_c(error);
        set_log_c(fatal);
    } else {
        init_c();
    }
}