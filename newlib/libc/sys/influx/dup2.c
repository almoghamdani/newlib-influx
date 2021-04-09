#include <errno.h>

extern int r_dup(int oldfd, int newfd);

int dup2(int oldfd, int newfd) {
    if (newfd < 0) {
        errno = EBADF;
        return -1;
    }

    return r_dup(oldfd, newfd);
}