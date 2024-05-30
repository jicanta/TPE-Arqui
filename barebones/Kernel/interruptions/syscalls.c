#include <syscalls.h>
#include <videoDriver.h>
#include <lib.h>   //TODO: es para testear, despues hay q sacarlo!!!
#include <keyboardDriver.h>

#define STDIN       0
#define STDOUT      1
#define STDERROR    2
#define SCALLSDIM   5

static uint64_t *registers;

extern uint32_t inb0x60();
extern uint32_t get_year();
extern uint32_t get_month();
extern uint32_t get_day();
extern uint32_t get_hours();
extern uint32_t get_minutes();
extern uint32_t get_seconds();
extern uint64_t *registerSnapshot();
extern void sys_time_asm();
extern void sys_registers_asm();
extern void _sti();
extern void _cli();
extern void sys_getkeypressed_asm();
extern void sys_fillrect_asm();
extern void sys_write_at_asm();


// TODO: check if any other syscalls must be created

void sys_read(uint64_t fileDescriptor, char * location, uint64_t length);
void sys_write(uint64_t fileDescriptor, const char * string);

;
// function to process which syscall is being asked for and call the function
uint64_t syscallHandler(uint64_t id){
    if (id < 0 || id > SCALLSDIM){     
        return -1;      // syscall does not exist
    }
    switch (id) {
        case 1:  
            _sti();
            sys_read_asm();
            _cli();
            break;
        case 2:
            sys_write_asm();
            break;
        case 3:
            sys_time();
            break;
        case 4:
            sys_printRegisters();
            break;
        case 5:
            cleanScreen();
            break;
        case 6:
            sys_getkeypressed_asm();
            break;
        case 7:
            sys_fillrect_asm();
            break;
        case 8:
            sys_write_at_asm();
            break;
        default:
            break;
    }
}

void sys_getkeypressed(uint64_t fileDescriptor, char * location){
        if(fileDescriptor != STDIN) { 
        return -1;
    }
    *(location) = getLastPressedSC();
}

void sys_read(uint64_t fileDescriptor, char * location, uint64_t length){
    if(fileDescriptor != STDIN) { 
        return -1;
    }
    char c;
    int64_t i;
    for (i = 0; i < length && (c = getLastAscii()) != '\0'; i++) {
        location[i] = c;
    }
}

void sys_write(uint64_t fileDescriptor, const char * string){
    if(fileDescriptor != STDOUT) {
        return -1;
    }
    putString(string);
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

void saveRegisters(){
    registers = registerSnapshot();
}

void sys_printRegisters(){
    newLine();
    for (int i = 0; i < 17 ; i++){
        putString(itoa(registers[i],10));
        newLine();
    }
}

void sys_getkeypressed(uint64_t fileDescriptor, char * location){
    if(fileDescriptor != STDIN) { 
        return -1;
    }
    *(location) = getLastPressedSC();
}

void sys_fillrect(uint64_t x, uint64_t y){
    // drawColoredRectangle();
}

void sys_write_at(uint64_t fileDescriptor, const char * string, uint64_t x, uint64_t y){
    if(fileDescriptor != STDOUT) {
        return -1;
    }
    //putStringAt(string,x,y);    TODO: nose como hacerlo bien
}
