#include "log.h"

int main(){
    set_log(all);
    panda_log.debug("hello %s\n", "world");
    set_log_c(all);
    panda_log_c.debug("123");
}