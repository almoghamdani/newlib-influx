#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>
#include <sys/errno.h>
#include <sys/types.h>

extern char *r_getcwd(char *buf, size_t size);

char *getcwd(char *buf, size_t size) {
    char temp_buf[MAXPATHLEN];

    char *ret = NULL;
    size_t ret_size = 0;

    // Check valid parameterss
    if (size == 0 && buf != NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (size == 0) {
        size = MAXPATHLEN;
    }

    // Try to get the current working dir
    ret = r_getcwd(temp_buf, size);

    // If no error occurred
    if (ret == temp_buf) {
        ret_size = strlen(temp_buf);

        // Allocate the buffer
        if (buf == NULL) {
            buf = malloc(ret_size);
        }

        // Copy the current directory to the buffer
        memcpy(buf, temp_buf, ret_size);
    }

    return ret == temp_buf ? buf : NULL;
}