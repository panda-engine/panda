#include "log.h"

int main(){
    int a = 0;
    char s[] = "hello %s %d\n";
    set_log(all);
    panda_log.debug(s, "world", a);
    set_log_c(all);
    panda_log_c.debug("123");
}