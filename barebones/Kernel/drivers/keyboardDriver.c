#include <stdio.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <syscalls.h>


#define LEFTSHIFT             0x2A
#define RIGHTSHIFT            0x36
#define MASK                  0x7F
#define ISSHIFT(scanCode)     ((scanCode == LEFTSHIFT) && (scanCode == RIGHTSHIFT))
#define KEY_ASCII(scanCode) ((scanCode) & MASK)

uint8_t lowerCaseMap[] = {
      '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
      '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
      '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', '`', '\b',
      '\0', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0',
      '\0', ' ', '\0', '\0', '\0', '\0', '\0',  '\0', '\0', '\0', '\0'
};

extern void sys_peekRegisters();
extern uint32_t inb0x60();

uint32_t lastPressedSC = 55;

void saveLastPressed() {
    uint32_t scanCode = inb0x60();
    if (ISSHIFT(scanCode)) {
        sys_saveRegisters();
    }
    lastPressedSC = scanCode;
}

char getLastAscii(){
    uint32_t sc = getLastPressedSC();
    return lowerCaseMap[sc];
}

// TODO: esta es la funcion a la que llama la sys call read
uint32_t getLastPressedSC() {
    uint32_t aux = lastPressedSC;
    lastPressedSC = 55;
    return aux;
}

// TODO: esta es la funcion a la que llama la interrupcion del teclado
void processBuffer(){
    saveLastPressed();       // start reading
    return ;
}