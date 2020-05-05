#include <kernel_sigaction.h>
#include <stdio.h>
#include <sys/dirent.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <syscall.h>

_syscall1_base(void, _exit, 0, int, status)
_syscall1_base(int, close, 1, int, file)
_syscall3_base(int, execve, 2, char *, name, char **, argv, char **, env)
_syscall0_base(int, fork, 3)
_syscall2_base(int, fstat, 4, int, file, struct stat *, st)
_syscall0_base(int, getpid, 5)
_syscall1_base(int, isatty, 6, int, file)
_syscall3_base(int, r_kill, 7, int64_t, pid, int64_t, tid, int, sig)
_syscall2_base(int, link, 8, char *, old, char *, new)
_syscall3_base(int, lseek, 9, int, file, int, ptr, int, dir)
_syscall3_base(int, r_open, 10, const char *, name, int, flags, int, mode)
_syscall3_base(int, read, 11, int, file, char *, ptr, int, len)
_syscall1_base(caddr_t, sbrk, 12, int, incr)
_syscall2_base(int, stat, 13, const char *,file, struct stat *, st)
_syscall1_base(clock_t, times, 14, struct tms *, buf)
_syscall1_base(int, unlink, 15, char *, name)
_syscall3_base(int, waitpid, 16, pid_t, pid, int *, wstatus, int, flags)
_syscall3_base(int, write, 17, int, file, char *, ptr, int, len)
_syscall3_base(int, r_sigaction, 18, int, signum, const struct __kernel_signal_action *, act, struct __kernel_signal_action *, oldact)
_syscall2_base(int, gettimeofday, 19, struct timeval *, p, void *, z)
_syscall2_base(int, gethostname, 20, char *, name, size_t, len)
_syscall0_base(int, sigreturn, 21)
_syscall1_base(unsigned int, sleep, 22, unsigned int, seconds)
_syscall3_base(int, getdents, 23, int, fd, struct dirent *, dirp, unsigned int, count)