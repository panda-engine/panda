#ifndef log_h_
#define log_h_

typedef enum log_grade{
    all,
    debug,
    info,
    warn,
    error,
    off,
}log_grade;

#ifdef __cplusplus
#include <cstdio>
#include <utility>
#include <atomic>

extern std::atomic_bool log_s[4];

template<typename S, typename ...Args>
constexpr inline void log_debug(const S &str, Args&& ...args){
    if(!log_s[0].load(std::memory_order_acquire)) return;
    std::printf("* DEBUG: ");
    std::printf(str, std::forward<Args>(args)...);
    std::puts(" *");
}
template<typename S, typename ...Args>
constexpr inline void log_info(const S &str, Args&& ...args){
    if(!log_s[1].load(std::memory_order_acquire)) return;
    std::printf("* INFO: ");
    std::printf(str, std::forward<Args>(args)...);
    std::puts(" *");
}
template<typename S, typename ...Args>
constexpr inline void log_warn(const S &str, Args&& ...args){
    if(!log_s[2].load(std::memory_order_acquire)) return;
    std::printf("* WARN: ");
    std::printf(str, std::forward<Args>(args)...);
    std::puts(" *");
}
template<typename S, typename ...Args>
constexpr inline void log_error(const S &str, Args&& ...args){
    if(!log_s[3].load(std::memory_order_acquire)) return;
    std::printf("* ERROR: ");
    std::printf(str, std::forward<Args>(args)...);
    std::puts(" *");
}
template<typename S, typename ...Args>
constexpr inline void log(bool is_error, const S &str, Args&& ...args){
    if(!log_s[3].load(std::memory_order_acquire) && !is_error) return;
    std::printf("* ERROR: ");
    std::printf(str, std::forward<Args>(args)...);
    std::puts(" *");
}

extern "C" {
#endif
void set_log(log_grade g);

#ifdef NDEBUG
#define assert(x) ((void)0)
#else
#include <assert.h>
#endif

#ifdef __cplusplus
}
#endif

#endif