#include <sys/dirent.h>
#include <unistd.h>

char *ttyname(int fd) {
    static char name[MAXPATHLEN];

    if (ttyname_r(fd, name, MAXPATHLEN) == 0) {
        return name;
    } else {
        return NULL;
    }
}