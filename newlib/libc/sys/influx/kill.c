#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

extern r_kill(int64_t pid, int64_t tid, int sig);

int kill(pid_t pid, int sig) { return r_kill(pid, -1, sig); }