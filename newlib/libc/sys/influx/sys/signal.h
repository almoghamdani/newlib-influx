#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/_sigset.h>
#include <sys/_timespec.h>
#include <sys/cdefs.h>
#include <sys/features.h>
#include <sys/types.h>
#include "_ansi.h"

#if !defined(_SIGSET_T_DECLARED)
#define _SIGSET_T_DECLARED
typedef __sigset_t sigset_t;
#endif

#define SA_ONSTACK 0x0001   /* take signal on alternate signal stack */
#define SA_RESTART 0x0002   /* restart system calls on signal return */
#define SA_RESETHAND 0x0004 /* reset to SIG_DFL when taking signal */
#define SA_NOCLDSTOP 0x0008 /* do not generate SIGCHLD on child stop */
#define SA_NODEFER 0x0010   /* don't mask the signal we're delivering */
#define SA_NOCLDWAIT 0x0020 /* don't keep zombies around */
#define SA_SIGINFO 0x0040   /* signal handler with SA_SIGINFO args */

#define SIG_DFL ((_sig_func_ptr)0)  /* Default action */
#define SIG_IGN ((_sig_func_ptr)1)  /* Ignore action */
#define SIG_ERR ((_sig_func_ptr)-1) /* Error return */

/* Values for si_code */

/* Codes for SIGILL */
#define ILL_ILLOPC 1 /* illegal opcode */
#define ILL_ILLTRP 2 /* illegal trap */
#define ILL_PRVOPC 3 /* privileged opcode */
#define ILL_ILLOPN 4 /* illegal operand -NOTIMP */
#define ILL_ILLADR 5 /* illegal addressing mode -NOTIMP */
#define ILL_PRVREG 6 /* privileged register -NOTIMP */
#define ILL_COPROC 7 /* coprocessor error -NOTIMP */
#define ILL_BADSTK 8 /* internal stack error -NOTIMP */

/* Codes for SIGFPE */
#define FPE_FLTDIV 1 /* floating point divide by zero */
#define FPE_FLTOVF 2 /* floating point overflow */
#define FPE_FLTUND 3 /* floating point underflow */
#define FPE_FLTRES 4 /* floating point inexact result */
#define FPE_FLTINV 5 /* invalid floating point operation */
#define FPE_FLTSUB 6 /* subscript out of range -NOTIMP */
#define FPE_INTDIV 7 /* integer divide by zero */
#define FPE_INTOVF 8 /* integer overflow */

/* Codes for SIGSEGV */
#define SEGV_MAPERR 1 /* address not mapped to object */
#define SEGV_ACCERR 2 /* invalid permission for mapped object */

/* Codes for SIGBUS */
#define BUS_ADRALN 1 /* Invalid address alignment */
#define BUS_ADRERR 2 /* Nonexistent physical address -NOTIMP */
#define BUS_OBJERR 3 /* Object-specific HW error - NOTIMP */

/* Codes for SIGTRAP */
#define TRAP_BRKPT 1 /* Process breakpoint -NOTIMP */
#define TRAP_TRACE 2 /* Process trace trap -NOTIMP */

/* Codes for SIGCHLD */
#define CLD_EXITED 1    /* child has exited */
#define CLD_KILLED 2    /* terminated abnormally, no core file */
#define CLD_DUMPED 3    /* terminated abnormally, core file */
#define CLD_TRAPPED 4   /* traced child has trapped */
#define CLD_STOPPED 5   /* child has stopped */
#define CLD_CONTINUED 6 /* stopped child has continued */

/* Codes for SIGPOLL */
#define POLL_IN 1  /* Data input available */
#define POLL_OUT 2 /* Output buffers available */
#define POLL_MSG 3 /* Input message available */
#define POLL_ERR 4 /* I/O error */
#define POLL_PRI 5 /* High priority input available */
#define POLL_HUP 6 /* Device disconnected */

union sigval {
    int sival_int;
    void *sival_ptr;
};

typedef struct siginfo {
    uint64_t si_signo;  /* signal number */
    uint64_t si_errno;  /* errno association */
    uint64_t si_code;   /* signal code */
    pid_t si_pid;       /* sending process */
    uid_t si_uid;       /* sender's ruid */
    uint64_t si_status; /* exit value */
    void *si_addr;      /* faulting instruction */

    /* signal value */
    int si_int;
    void *si_ptr;
} siginfo_t;

/* struct sigaction notes from POSIX:
 *
 *  (1) Routines stored in sa_handler should take a single int as
 *      their argument although the POSIX standard does not require this.
 *      This is not longer true since at least POSIX.1-2008
 *  (2) The fields sa_handler and sa_sigaction may overlap, and a conforming
 *      application should not use both simultaneously.
 */

typedef void (*_sig_func_ptr)(int);

struct sigaction {
    union {
        _sig_func_ptr _handler; /* SIG_DFL, SIG_IGN, or pointer to a function */
        void (*_sigaction)(int, siginfo_t *, void *);
    } _signal_handlers;
    int sa_flags;     /* Special flags to affect behavior of signal */
    sigset_t sa_mask; /* Additional set of signals to be blocked */
                      /*   during execution of signal-catching */
                      /*   function. */
};

#define sa_handler _signal_handlers._handler
#define sa_sigaction _signal_handlers._sigaction

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
/*
 * Minimum and default signal stack constants. Allow for target overrides
 * from <sys/features.h>.
 */
#ifndef MINSIGSTKSZ
#define MINSIGSTKSZ 2048
#endif
#ifndef SIGSTKSZ
#define SIGSTKSZ 8192
#endif

/*
 * Possible values for ss_flags in stack_t below.
 */
#define SS_ONSTACK 0x1
#define SS_DISABLE 0x2

#endif

/*
 * Structure used in sigaltstack call.
 */
typedef struct sigaltstack {
    void *ss_sp;    /* Stack base or pointer.  */
    int ss_flags;   /* Flags.  */
    size_t ss_size; /* Stack size.  */
} stack_t;

#if __POSIX_VISIBLE
#define SIG_SETMASK 0 /* set mask with sigprocmask() */
#define SIG_BLOCK 1   /* set of signals to block */
#define SIG_UNBLOCK 2 /* set of signals to, well, unblock */

int sigprocmask(int, const sigset_t *, sigset_t *);
#endif

#if __POSIX_VISIBLE >= 199506
int pthread_sigmask(int, const sigset_t *, sigset_t *);
#endif

#ifdef _COMPILING_NEWLIB
int _kill(pid_t, int);
#endif /* _COMPILING_NEWLIB */

#if __POSIX_VISIBLE
int kill(pid_t, int);
#endif

#if __POSIX_VISIBLE
int sigreturn();
int sigaction(int, const struct sigaction *, struct sigaction *);
int sigaddset(sigset_t *, const int);
int sigdelset(sigset_t *, const int);
int sigismember(const sigset_t *, int);
int sigfillset(sigset_t *);
int sigemptyset(sigset_t *);
int sigpending(sigset_t *);
int sigsuspend(const sigset_t *);
int sigwait(const sigset_t *, int *);

#if !defined(__CYGWIN__) && !defined(__rtems__)
/* These depend upon the type of sigset_t, which right now
   is always a long.. They're in the POSIX namespace, but
   are not ANSI. */
#define sigaddset(what, sig) (*(what) |= (1 << (sig)), 0)
#define sigdelset(what, sig) (*(what) &= ~(1 << (sig)), 0)
#define sigemptyset(what) (*(what) = 0, 0)
#define sigfillset(what) (*(what) = ~(0), 0)
#define sigismember(what, sig) (((*(what)) & (1 << (sig))) != 0)
#endif /* !__CYGWIN__ && !__rtems__ */
#endif /* __POSIX_VISIBLE */

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
int sigaltstack(const stack_t *__restrict, stack_t *__restrict);
#endif

#if __POSIX_VISIBLE >= 199506
int pthread_kill(pthread_t, int);
#endif

#if __POSIX_VISIBLE >= 199309

/*  3.3.8 Synchronously Accept a Signal, P1003.1b-1993, p. 76
    NOTE: P1003.1c/D10, p. 39 adds sigwait().  */

int sigwaitinfo(const sigset_t *, siginfo_t *);
int sigtimedwait(const sigset_t *, siginfo_t *, const struct timespec *);
/*  3.3.9 Queue a Signal to a Process, P1003.1b-1993, p. 78 */
int sigqueue(pid_t, int, const union sigval);

#endif /* __POSIX_VISIBLE >= 199309 */

#define SIGHUP 1       /* hangup */
#define SIGINT 2       /* interrupt */
#define SIGQUIT 3      /* quit */
#define SIGILL 4       /* illegal instruction (not reset when caught) */
#define SIGTRAP 5      /* trace trap (not reset when caught) */
#define SIGABRT 6      /* abort() */
#define SIGIOT SIGABRT /* compatibility */
#define SIGBUS 7       /* bus error */
#define SIGFPE 8       /* floating point exception */
#define SIGKILL 9      /* kill (cannot be caught or ignored) */
#define SIGUSR1 10     /* user defined signal 1 */
#define SIGSEGV 11     /* segmentation violation */
#define SIGUSR2 12     /* user defined signal 2 */
#define SIGPIPE 13     /* write on a pipe with no one to read it */
#define SIGALRM 14     /* alarm clock */
#define SIGTERM 15     /* software termination signal from kill */
#define SIGSTKFLT 16   /* stack fault on coprocessor (unused) */
#define SIGCHLD 17     /* child stopped or terminated */
#define SIGCLD SIGCHLD /* compatibility */
#define SIGCONT 18     /* continue a stopped process */
#define SIGSTOP 19     /* stop process */
#define SIGTSTP 20     /* stop typed at terminal */
#define SIGTTIN 21     /* to readers pgrp upon background tty read */
#define SIGTTOU 22     /* like TTIN for output if (tp->t_local&LTOSTOP) */
#define SIGURG 23      /* urgent condition on IO channel */
#define SIGXCPU 24     /* exceeded CPU time limit */
#define SIGXFSZ 25     /* exceeded file size limit */
#define SIGVTALRM 26   /* virtual time alarm */
#define SIGPROF 27     /* profiling time alarm */
#define SIGWINCH 28    /* window size changes */
#define SIGIO 29       /* I/O now possible */
#define SIGPOLL SIGIO  /* compatibility */
#define SIGPWR 30      /* power failure */
#define SIGSYS 31      /* bad argument to system call */

#ifdef __cplusplus
}
#endif

#ifndef _SIGNAL_H_
/* Some applications take advantage of the fact that <sys/signal.h>
 * and <signal.h> are equivalent in glibc.  Allow for that here.  */
#include <signal.h>
#endif
#endif /* _SYS_SIGNAL_H */
