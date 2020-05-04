#include <kernel_sigaction.h>
#include <stdint.h>
#include <sys/signal.h>

extern int r_sigaction(int, const __kernel_signal_action *, __kernel_signal_action *);

int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact) {
    __kernel_signal_action kernel_act, kernel_oldact;

    int ret;

    if (act != NULL) {
        kernel_act.handler.handler_func = act->_signal_handlers._handler;
        kernel_act.flags = act->sa_flags;
        kernel_act.mask = act->sa_mask;
        kernel_act.restorer = (void (*)(void))sigreturn;
    }

    ret =
        r_sigaction(sig, act != NULL ? &kernel_act : NULL, oldact != NULL ? &kernel_oldact : NULL);

    if (ret != -1 && oldact != NULL) {
        oldact->_signal_handlers._handler = (_sig_func_ptr)kernel_oldact.handler.handler_func;
        oldact->sa_flags = kernel_oldact.flags;
        oldact->sa_mask = kernel_oldact.mask;
    }

    return ret;
}