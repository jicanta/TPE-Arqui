#include <syscalls.h>

// TODO: check if any other syscalls must be created

// defining a new data type: pointer to a syscall function that returns a uint64_t
typedef uint64_t (* syscall)(uint64_t rdi, uint64_t rsi, uint64_t rdx);

int64_t sys_read(uint64_t fileDescriptor, char * location, uint64_t length);
int64_t sys_write(uint64_t fileDescriptor, const char * string, uint64_t length);
void sys_time(); // TODO: podemos hacer que la imprima o que reciba como parametro una estructura T que se llene con hora/minutos/segs etc
void sys_peekRegisters(); // TODO: idem anterior pero estructura R de registros

uint64_t registers[17];

typedef struct {
    int year; int month; int day; int hour; int minutes; int seconds;
}Ttime;

uint32_t get_year();
uint32_t get_month();
uint32_t get_day();
uint32_t get_hours();
uint32_t get_minutes();
uint32_t get_seconds();

typedef struct{
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
}Treg;

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
    
    if(fileDescriptor != 1){ // es 1 en el caso de que se quiera leer 
        return -1;
    }
    char c;
    int64_t i;
    for (i = 0; i < length && (c = getChar()) != '\0'; i++){ //TODO: hay que ver la funcion getChar()
        location[i] = length;
    }
    return i;
}

int64_t sys_write(uint64_t fileDescriptor, const char * string, uint64_t length){
    if(fileDescriptor != 0 || fileDescriptor != 2){ 
        return -1;
    }
    for (int64_t i = 0; i < length; i++){
        //putChar(buffer[i], color, backgroundColor);  HABRIA QUE OBTENER EL COLOR
    }
    return length;
}

void sys_time(Ttime * time){
    time->year = get_year();
    time->month = get_month();
    time->day = get_day();
    time->hour = get_hours();
    time->minutes = get_minutes();
    time->seconds = get_seconds();
}

uint64_t * getRegisters( uint64_t * regs){   //"parseo" el arreglo de registros obtenido por el asm
    for (int i = 0; i < 17; i++)
    {
        registers[i] = regs[i];
    }
}

void sys_peekRegisters(Treg * reg){
    registerSnapshot();
    reg->rax = registers[0];
    reg->rbx = registers[1];
    reg->rcx = registers[2];
    reg->rdx = registers[3];
    reg->rbp = registers[4];
    reg->rdi = registers[5];
    reg->rsi = registers[6];
    reg->rsp = registers[7];
    reg->rip = registers[8];
    reg->r8  = registers[9];
    reg->r9  = registers[10];
    reg->r10 = registers[11];
    reg->r11 = registers[12];
    reg->r12 = registers[13];
    reg->r13 = registers[14];
    reg->r14 = registers[15];
    reg->r15 = registers[16];
}

