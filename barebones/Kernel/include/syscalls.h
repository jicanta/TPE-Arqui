#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdint.h>

uint64_t syscall_handler(uint64_t rdi, uint64_t rsi, uint64_t rdx);

#endif
