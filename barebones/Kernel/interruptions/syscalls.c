#include <syscalls.h>
#include <videoDriver.h>
#include <lib.h>   //TODO: es para testear, despues hay q sacarlo!!!

#define STDIN       0
#define STDOUT      1
#define STDERROR    2

static uint64_t *registers;

extern uint32_t inb0x60();
extern uint32_t get_year();
extern uint32_t get_month();
extern uint32_t get_day();
extern uint32_t get_hours();
extern uint32_t get_minutes();
extern uint32_t get_seconds();
extern void _sti();
extern void _cli();

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
uint64_t syscallHandler(uint64_t rax/*, uint64_t rdi, uint64_t rsi, uint64_t rdx*/){
    if (rax < 0 || rax > syscallsDim){     
        return -1;      // syscall does not exist
    }
    switch (rax)
    {
        case 1:  
            //_sti();
            //sys_read();
            //_cli();
            break;
        case 2:
            //sys_write();
            break;
        case 3:
            sys_time();
            break;
        case 4:
            sys_peekRegisters();
            break;
        
        default:
            break;
    }
}

int64_t sys_read(uint64_t fileDescriptor, char * location, uint64_t length){
    if(fileDescriptor != STDIN){ 
        return -1;
    }
    char c;
    int64_t i;
    for (i = 0; i < length && (c = inb0x60()) != '\0'; i++){ //TODO: hay que ver la funcion getChar()
        location[i] = length;
    }
    return i;
}

int64_t sys_write(uint64_t fileDescriptor, const char * string, uint64_t length){
    if(fileDescriptor != STDOUT /* || fileDescriptor != STDERROR */){   // TODO: ver si agregamos eso como escribir bien
        return -1;
    }
    for (int64_t i = 0; i < length; i++){
        putChar(getFramebuffer()[i]);
    }
    return length;
}

void sys_time(){
    putString("year:");
    putString(itoa(get_year(),10));
    putString("month:");
    putString(itoa(get_month(),10));
    putString("day:");
    putString(itoa(get_day(),10));
    putString("hour:");
    putString(itoa(get_hours() - 3,10));
    putString("minutes:");
    putString(itoa(get_minutes(),10));
    putString("seconds:");
    putString(itoa(get_seconds(),10));
}

void sys_peekRegisters(){
    registers = registerSnapshot();
}

uint64_t * getLastSavedRegisters(){
    return registers;
}