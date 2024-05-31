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
    putChar('z');
    
    if (r9 < 0 || r9 > SCALLSDIM){     
        putChar('Q');
        return -1;      // syscall does not exist
    }
    switch (r9) {
        
        case 1:
            _sti();  
            sys_read(rdi, rsi, rdx);
            _cli();
            break;
        case 2:
            //putString("write");
            //putChar("w");
            sys_write(rdi, rsi);
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
        case 9:
            sys_write_color_asm();
        case 10:
            sys_write_color_at_asm();
        case 11:
            sys_sleep_asm();
        default:
            break;
    }
}

void sys_read(uint64_t fileDescriptor, char * location, uint64_t length) {
    putString("hola");
    if(fileDescriptor != STDIN) { 
        return -1;
    }
    for (int i = 0; i < length; i++) {
        putChar(itoa(length,10));
        putChar('k');
        char c = '\0'; 
        while (c == '\0'){
            c = getLastAscii();
        }
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

void sys_saveRegisters() {
    registers = registerSnapshot();
}

void sys_printRegisters() {
    newLine();
    for (int i = 0; i < 17 ; i++){
        putString(itoa(registers[i],10));
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
