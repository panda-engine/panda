#ifndef log_h_
#define log_h_

typedef enum log_grade{
    all,
    debug,
    info,
    warn,
    error,
    fatal,
    off,
}log_grade;

#ifdef __cplusplus
#include <cstdio>
#include <utility>
struct _log{
    bool log_s[5];
    template<typename S, typename ...Args>
    void debug(S &str, Args&& ...args){
        if(!log_s[0]) return;
        std::printf("*DEBUG*: ");
        std::printf(str, std::forward<Args>(args)...);
    }
    template<typename S, typename ...Args>
    void info(S &str, Args&& ...args){
        if(!log_s[1]) return;
        std::printf("*INFO*: ");
        std::printf(str, std::forward<Args>(args)...);
    }
    template<typename S, typename ...Args>
    void warn(S &str, Args&& ...args){
        if(!log_s[2]) return;
        std::printf("*WARN*: ");
        std::printf(str, std::forward<Args>(args)...);
    }
    template<typename S, typename ...Args>
    void error(S &str, Args&& ...args){
        if(!log_s[3]) return;
        std::printf("*ERROR: ");
        std::printf(str, std::forward<Args>(args)...);
    }
    template<typename S, typename ...Args>
    void fatal(S &str, Args&& ...args){
        if(!log_s[4]) return;
        std::printf("*FATAL: ");
        std::printf(str, std::forward<Args>(args)...);
    }
};
extern struct _log panda_log;
void set_log(log_grade g);
extern "C" {
#endif

struct _log_c{
    void (*debug)(const char* const str);
    void (*info)(const char* const str);
    void (*warn)(const char* const str);
    void (*error)(const char* const str);
    void (*fatal)(const char* const str);
};
extern struct _log_c panda_log_c;
void set_log_c(log_grade g);

#ifdef __cplusplus
}
#endif

#endif