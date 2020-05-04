#ifndef INFLUX_KERNEL_SIGACTION_H
#define INFLUX_KERNEL_SIGACTION_H
#include <sys/_sigset.h>
#include <sys/signal.h>

union __kernel_signal_handler {
    void (*handler_func)(int);
    void (*action_func)(int, siginfo_t *, void *);
};

typedef struct __kernel_signal_action {
    union __kernel_signal_handler handler;
    __sigset_t mask;
    int flags;
    void (*restorer)(void);
} __kernel_signal_action;

#endif