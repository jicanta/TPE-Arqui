#include <syscalls.h>

// TODO: check if any other syscalls must be created

// defining a new data type: pointer to a syscall function that returns a uint64_t
typedef uint64_t (* syscall)(uint64_t rdi, uint64_t rsi, uint64_t rdx);

int64_t sys_read(uint64_t fileDescriptor, char * location, uint64_t length);
int64_t sys_write(uint64_t fileDescriptor, const char * string, uint64_t length);
void sys_time(); // TODO: podemos hacer que la imprima o que reciba como parametro una estructura T que se llene con hora/minutos/segs etc
void sys_peekRegisters(); // TODO: idem anterior pero estructura R de registros

// array with syscalls. each syscall is in it's ID position
syscall syscalls[] = {(syscall) sys_read, (syscall) sys_write, (syscall) sys_time, (syscall) sys_peekRegisters};

int syscallsDim = sizeof(syscalls) / sizeof(syscalls[0]);


// function to process which syscall is being asked for and call the function
uint64_t syscallHandler(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx){
    if (rax < 0 || rax > syscallsDim){      
        return -1;      // syscall does not exist
    }
    return syscalls[rax](rdi, rsi, rdx);  // requested syscall is called
}

int64_t sys_read(uint64_t fileDescriptor, char * location, uint64_t length){
    // TODO: define syscall read
    return 0;
}

int64_t sys_write(uint64_t fileDescriptor, const char * string, uint64_t length){
    // TODO: define syscall write
    return 0;
}

void sys_time(){
    // TODO: define syscall time
    return ;
}

void sys_peekRegisters(){
    // TODO: define syscall peekRegisters
    return ;
}
