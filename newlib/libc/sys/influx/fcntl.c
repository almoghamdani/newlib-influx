#include <errno.h>

int fcntl(int fd, int cmd, ...) {
	// TODO: Remove stub and implement
    errno = EAGAIN;
    return -1;
}