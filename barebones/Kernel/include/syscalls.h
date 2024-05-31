#ifndef SYSCALLS_H_
#define SYSCALLS_H_
#include <stdint.h>

typedef struct {
    int year; 
    int month; 
    int day; 
    int hour; 
    int minutes; 
    int seconds;
} Ttime;


uint64_t syscallHandler(uint64_t rax/*, uint64_t rdi, uint64_t rsi, uint64_t rdx*/);
void sys_peekRegisters();
uint64_t * getLastSavedRegisters();
void sys_read(uint64_t fileDescriptor, char * location, uint64_t length);


#endif
