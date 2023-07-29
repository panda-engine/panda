#ifndef log_h_
#define log_h_

typedef enum log_grade {
    all,
    debug,
    info,
    warn,
    error,
    off,
} log_grade;

#include <stdio.h>
#ifdef __cplusplus
#include <atomic>
#include <utility>

extern std::atomic_bool log_s[4];
#ifdef NDEBUG
#define log_debug(msg...) ((void)0)
#define log_info(msg...) ((void)0)
#else

template <typename S, typename... Args>
constexpr inline void log_debug(const S &str, Args &&...args) {
    if (!log_s[0].load(std::memory_order_acquire))
        return;
    printf("* DEBUG: ");
    printf(str, std::forward<Args>(args)...);
    puts(" *");
}
template <typename S, typename... Args>
constexpr inline void log_info(const S &str, Args &&...args) {
    if (!log_s[1].load(std::memory_order_acquire))
        return;
    printf("* INFO: ");
    printf(str, std::forward<Args>(args)...);
    puts(" *");
}
#endif
template <typename S, typename... Args>
constexpr inline void log_warn(const S &str, Args &&...args) {
    if (!log_s[2].load(std::memory_order_acquire))
        return;
    printf("* WARN: ");
    printf(str, std::forward<Args>(args)...);
    puts(" *");
}
template <typename S, typename... Args>
constexpr inline void log_error(const S &str, Args &&...args) {
    if (!log_s[3].load(std::memory_order_acquire))
        return;
    printf("* ERROR: ");
    printf(str, std::forward<Args>(args)...);
    puts(" *");
}
template <typename S, typename... Args>
constexpr inline void log(bool is_error, const S &str, Args &&...args) {
    if (!log_s[3].load(std::memory_order_acquire) and !is_error)
        return;
    printf("* ERROR: ");
    printf(str, std::forward<Args>(args)...);
    puts(" *");
}

extern "C" {
#endif
void set_log(log_grade g);

#ifdef NDEBUG
#define clog_error(msg, args...) ((void)0)
#define assert(x) ((void)0)
#else
#include <assert.h>

#define clog_error(msg, ...)                                                   \
    printf("* ERROR: ");                                                       \
    printf(msg, __VA_ARGS__);                                                  \
    puts(" *");

#endif

#ifdef __cplusplus
}
#endif

#endif