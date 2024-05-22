#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdint.h>

uint64_t syscallHandler(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx);

#endif
