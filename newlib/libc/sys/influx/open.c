#include <stdarg.h>

extern int r_open(const char *, int, int);

int open(const char *name, int flags, ...) {
    va_list list;

    va_start(list, flags);

    int ret = r_open(name, flags, va_arg(list, int));

    va_end(list);

    return ret;
}