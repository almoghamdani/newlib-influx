#ifndef _SYS_DIRENT_H
#error "Never use <bits/dirent.h> directly; include <dirent.h> instead."
#endif
#include <stdint.h>

#define MAXNAMELEN 256
#define MAXPATHLEN 2048

typedef struct dirent {
    uint64_t d_ino;          /* 64-bit inode number */
    uint64_t d_off;          /* 64-bit offset to next structure */
    unsigned short d_reclen; /* Size of this dirent */
    unsigned char d_type;    /* File type */
    char d_name[MAXNAMELEN]; /* Filename (null-terminated) */
} dirent;

#define d_fileno d_ino /* Backwards compatibility.  */

/* File types */
#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12
#define DT_WHT 14

#undef _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_OFF
#define _DIRENT_HAVE_D_TYPE