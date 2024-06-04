#include <stdio.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <syscalls.h>


#define LEFTSHIFT             0x2A 
#define RIGHTSHIFT            0x36
#define ISSHIFT(scanCode)     ((scanCode == LEFTSHIFT) || (scanCode == RIGHTSHIFT))

uint8_t lowerCaseMap[] = {
      '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\0' /*'\t*/,
       'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0',
       'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', '`', '\0', '\\',
       'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', '*', '\0', ' ', '\0'
};

extern void sys_peekRegisters();
extern uint32_t inb0x60();

uint32_t lastPressedSC = 0;

void saveLastPressed() {
    uint32_t scanCode = inb0x60();
    if (scanCode > 0x80){
        return;
    }
    if (ISSHIFT(scanCode)) {
        sys_saveRegisters();
    }
    lastPressedSC = scanCode;
}

char getLastAscii(){
    while (lowerCaseMap[getLastPressedSC()] == '\0'){
        // it does not return an ascii until some significant key is pressed
    }
    char ascii = lowerCaseMap[lastPressedSC];
    lastPressedSC = 0;
    return ascii;
}

uint32_t getLastPressedSC() {
    return lastPressedSC;
}

void processBuffer(){
    saveLastPressed();       // start reading
    return ;
}