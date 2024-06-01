#include <syscalls.h>
#include <videoDriver.h>
#include <lib.h>   //TODO: es para testear, despues hay q sacarlo!!!
#include <keyboardDriver.h>

#define STDIN       0
#define STDOUT      1
#define STDERROR    2
#define SCALLSDIM   11

static uint64_t *registers;

// function to process which syscall is being asked for and call the function
uint64_t syscallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    if (r9 < 0 || r9 > SCALLSDIM){     
        return -1;      // syscall does not exist
    }
    switch (r9) {
        case 1:
            _sti();  
            sys_read(rdi, rsi, rdx);
            break;
        case 2:
            sys_time();
            break;
        case 3:
            sys_printRegisters();
            break;
        case 4:
            cleanScreen();
            break;
        case 5:
            sys_fillrect(rdi, rsi);
            break;
        case 6:
            sys_write_color(rdi, rsi, rdx);
        case 7:
            sys_write_color_at(rdi, rsi, rdx, rcx, r8);
        case 8:
            sys_sleep_asm();
        case 9:
            inzoom();
        case 10:
            outzoom();
        default:
            break;
    }
}

void sys_read(uint64_t fileDescriptor, char * location, uint64_t length) {
    if(fileDescriptor != STDIN) { 
        return;
    }
    char c;
    for (int i = 0; i < length; i++) {
        c = getLastAscii();
        location[i] = c;
    }
}

void sys_write(uint64_t fileDescriptor, const char * string) {
    if(fileDescriptor != STDOUT) {
        return -1;
    }
    putString(string);
}

void sys_time() {
    putString(itoa((get_hours()-3)%24, 10));putString("h:");putString(itoa(get_minutes(),10));putString("min:");putString(itoa(get_seconds(),10));putString("s\n");
    putString(itoa(get_day(), 10));putChar('/');putString(itoa(get_month(),10));putChar('/');putString(itoa(get_year(),10));
}

void sys_saveRegisters() {
    registers = registerSnapshot();
}

void sys_printRegisters() {
    char * aux[] = {"rax", "rbx", "rcx", "rdx", "rbp", "rdi", "rsi", "rsp", "rip", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
    for (int i = 0; i < 17 ; i++){
        putString(*(aux+i)); 
        putString(" = ");
        putString("0x");
        char * value = itoa(registers[i], 16);
        int len = strlength(value);
        if (len < 16){
            for (int i = 0; i < 16-len; i++){
                putChar('0');
            }
        }
        toUpperCase(value);
        putString(value);
        newLine();
    }
}

void sys_getkeypressed(uint64_t fileDescriptor, char * location) {
    if(fileDescriptor != STDIN) { 
        return -1;
    }
    *(location) = getLastPressedSC();
}

void sys_fillrect(uint64_t x, uint64_t y) {
    // drawColoredRectangle();
}

void sys_write_at(uint64_t fileDescriptor, const char * string, uint64_t x, uint64_t y) {
    if(fileDescriptor != STDOUT) {
        return -1;
    }
    putStringAt(string, x, y);
}

void sys_write_color(uint64_t fileDescriptor, const char * string, uint32_t color) {
    if(fileDescriptor != STDOUT) {
        return -1;
    }
    putStringColor(string, color);
}

void sys_write_color_at(uint64_t fileDescriptor, const char * string, uint32_t color, uint64_t x, uint64_t y) {
    if(fileDescriptor != STDOUT) {
        return -1;
    }
    putStringColorAt(string, color, x, y);
}

void sys_sleep(uint32_t ms) {

}

void inzoom() {
    incSize();
}

void outzoom() {
    decSize();
}
