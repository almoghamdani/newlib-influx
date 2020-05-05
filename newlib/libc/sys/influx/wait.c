#include <sys/types.h>
#include <sys/wait.h>

int wait(int *wstatus) { return waitpid(-1, wstatus, 0); }