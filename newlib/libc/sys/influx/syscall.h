#ifndef INFLUX_SYSCALL_H
#define INFLUX_SYSCALL_H
#include <stdint.h>

#define __syscall_return(type, res)              \
	do                                           \
	{                                            \
		if ((uint64_t)(res) >= (uint64_t)(-125)) \
		{                                        \
			errno = -(res);                      \
			res = -1;                            \
		}                                        \
		return (type)(res);                      \
	} while (0)

#define __inline_syscall0(num, ret) \
	__asm__ volatile("int $0x80"    \
					 : "=a"(ret)    \
					 : "a"(num));

#define __inline_syscall1(num, ret, arg1)       \
	__asm__ volatile("mov %2, %%rdx; int $0x80" \
					 : "=a"(ret)                \
					 : "a"(num), "r"((uint64_t)(arg1)));

#define __inline_syscall2(num, ret, arg1, arg2)                \
	__asm__ volatile("mov %2, %%rdx; mov %3, %%rdi; int $0x80" \
					 : "=a"(ret)                               \
					 : "a"(num), "r"((uint64_t)(arg1)), "r"((uint64_t)(arg2)));

#define __inline_syscall3(num, ret, arg1, arg2, arg3)                          \
	__asm__ volatile("mov %2, %%rdx; mov %3, %%rdi; mov %4, %%rsi; int $0x80"  \
					 : "=a"(ret)                                               \
					 : "a"(num), "r"((uint64_t)(arg1)), "r"((uint64_t)(arg2)), \
					   "r"((uint64_t)(arg3)));

#define __inline_syscall4(num, ret, arg1, arg2, arg3, arg4)                                  \
	__asm__ volatile("mov %2, %%rdx; mov %3, %%rdi; mov %4, %%rsi; mov %5, %%r10; int $0x80" \
					 : "=a"(ret)                                                             \
					 : "a"(num), "r"((uint64_t)(arg1)), "r"((uint64_t)(arg2)),               \
					   "r"((uint64_t)(arg3)), "r"((uint64_t)(arg4)));

#define _syscall0_base(type, name, num)    \
	type name(void)                        \
	{                                      \
		uint64_t __res;                    \
		__inline_syscall0(num, __res)      \
		__syscall_return(type, __res); \
	}

#define _syscall1_base(type, name, num, type1, arg1) \
	type name(type1 arg1)                            \
	{                                                \
		uint64_t __res;                              \
		__inline_syscall1(num, __res, arg1)          \
		__syscall_return(type, __res);           \
	}

#define _syscall2_base(type, name, num, type1, arg1, type2, arg2) \
	type name(type1 arg1, type2 arg2)                             \
	{                                                             \
		uint64_t __res;                                           \
		__inline_syscall2(num, __res, arg1, arg2)                 \
		__syscall_return(type, __res);                        \
	}

#define _syscall3_base(type, name, num, type1, arg1, type2, arg2, type3, arg3) \
	type name(type1 arg1, type2 arg2, type3 arg3)                              \
	{                                                                          \
		uint64_t __res;                                                        \
		__inline_syscall3(num, __res, arg1, arg2, arg3)                        \
		__syscall_return(type, __res);                                     \
	}

#define _syscall4_base(type, name, num, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4)                               \
	{                                                                                       \
		uint64_t __res;                                                                     \
		__inline_syscall4(num, __res, arg1, arg2, arg3, arg4)                               \
		__syscall_return(type, __res);                                                  \
	}

#endif