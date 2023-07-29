#include "log.h"

int main() {
    int a = 0;
    char s[] = "hello %s %d\n";
    set_log(all);
    log_debug(s, "world", a);
}