#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H
#include <_ansi.h>
#include <machine/_types.h>
#include <sys/_stdint.h>
#include <sys/_types.h>
#include <sys/cdefs.h>

/* BSD types permitted by POSIX and always exposed as in Glibc.  Only provided
   for backward compatibility with BSD code.  The uintN_t standard types should
   be preferred in new code. */
typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;
typedef __intptr_t register_t;

typedef __uint32_t in_addr_t; /* base type for internet address */
typedef __uint16_t in_port_t;
typedef __uintptr_t u_register_t;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

typedef uint32_t dev_t;
typedef uint64_t ino_t; /* inode number */
typedef uint32_t mode_t;
typedef uint64_t nlink_t;
typedef uint64_t uid_t;
typedef uint64_t gid_t;
typedef int pid_t;
typedef uint32_t rdev_t;
typedef uint64_t blksize_t;
typedef uint64_t blkcnt_t;
typedef uint64_t id_t; /* can hold a uid_t or pid_t */
typedef uint64_t key_t;
typedef uint64_t ssize_t;
typedef uint64_t sbintime_t;
typedef uint64_t daddr_t;
typedef char* caddr_t;

/* for statvfs() */
typedef uint64_t fsblkcnt_t;
typedef uint64_t fsfilcnt_t;

/* redefine newlib types to prevent conflicts */
typedef _CLOCK_T_ clock_t;
typedef _TIME_T_ time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t; /* microseconds (unsigned) */
typedef __suseconds_t suseconds_t;
typedef __off_t off_t;

#include <sys/features.h>
#include <sys/_pthreadtypes.h>
#include <machine/types.h>

#endif