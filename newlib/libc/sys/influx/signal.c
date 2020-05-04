#include <sys/signal.h>

_sig_func_ptr signal(int signum, _sig_func_ptr handler) {
    struct sigaction act = {0}, old_act = {0};

    act.sa_flags = SA_RESETHAND | SA_NODEFER;
    act.sa_handler = handler;

    // Call sigaction
    if (sigaction(signum, &act, &old_act) != 0) {
        return SIG_ERR;
    }

    return old_act.sa_handler;
}