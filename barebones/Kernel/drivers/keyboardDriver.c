#include <stdio.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <syscalls.h>
#include <interpreter.h>

#define BLOCKMAYUSC     0x3A
#define LEFTSHIFT       0x2A
#define RIGHTSHIFT      0x36
#define LEFTCTRL        0x1D
#define RIGHTCTRL       0xE01D
#define ENTER           0x1C
#define BACKSPACE       0xE
#define R               0x13
#define SPACEBAR        0x39
#define TABBAR          0x0F

#define FIRSTLINE       0x0D     // last scanCode from first line so as not to type special chars instead of numbers with blockMayusc

#define BUFFER_MAX_SIZE 6000     // can write up to 6000 chars which takes up almpst the entire screen
#define MASK            0x7F
#define UNPRESSEDCODE   0x80
#define LOWERCASE       0
#define UPPERCASE       1

#define ISUPPERCASE(scanCode)       ((scanCode > FIRSTLINE && (mayuscOn || shftPressed)) || shftPressed)
#define ISPRESSED(key)      (((key) & UNPRESSEDCODE) == 0)
#define KEY_ASCII(scanCode) ((scanCode) & MASK)    

extern void sys_registers_front_asm();

char totalBuffer[250];
int bufferSize = 0;         // TODO: ver si sirve de algo buffer size o no
int mayuscOn = 0;           // turned on if block mayusc is on
int ctrlPressed = 0;        // "boolean" to know if ctrl is pressed or not
int shftPressed = 0;        // "boolean" to know if ctrl is pressed or not

uint8_t lowerCaseMap[] = {
      '`', 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 
      0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\',
      0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', 0, 0,
      0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
      0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

uint8_t upperCaseMap[] = {
      '~', 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0, 
      0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '|',
      0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':','\"', 0, 0,
      0, 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
      0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

uint8_t * keysMap[] = {lowerCaseMap, upperCaseMap};

void saveBuffer(){
    totalBuffer[bufferSize] = 0;      // string should be null terminated
    interpretCommand(totalBuffer);      // TODO: write command interpreter to receive string
    bufferSize = 0;
    totalBuffer[bufferSize] = 0;
}

char processKey(uint32_t scanCode){
    if ((scanCode == ENTER) && ISPRESSED(scanCode)) {
        saveBuffer();
        return 0;
    } 
    // AGREGAR ISPRESSED
    if ((scanCode == BACKSPACE) && ISPRESSED(scanCode)) {   // we do not want it to act when releases
        bufferSize -= backSpace();
        return 0;
    }
    if ((scanCode == SPACEBAR) && ISPRESSED(scanCode)) {     // we do not want it to act when released
        spaceBar();
        return 0;
    }
    if ((scanCode == TABBAR) && ISPRESSED(scanCode)) {      // we do not want it to act when released
        tabBar();
        return 0;
    }
    if ((scanCode == BLOCKMAYUSC) && ISPRESSED(scanCode)){  // we do not want it to act when released
        mayuscOn = !mayuscOn;
        return 0;
    }
    // TODO: arreglar tema de que el shift queda prendido forever y no vuelve a minuscula, no veo porque estaria mal
    if (scanCode == (LEFTSHIFT || RIGHTSHIFT)){   // in this case, we do want to change shftPressed status when released
        shftPressed = !shftPressed;
        return 0;
    }
    if ((scanCode == LEFTCTRL) || (scanCode == RIGHTCTRL)){     // same as last shft
        ctrlPressed = !ctrlPressed;
        return 0;
    }
    if (ctrlPressed && (scanCode == R)){                       // CTRL + R saves registers at any given moment
        //putChar('2');
        //TODO: crear matriz, y mandarla a la syscall.
        ctrlPressed = 0;  //TODO: ver si no se puede arreglar de una forma menos villera
        sys_registers_front_asm();
        return 0;
    }
    if (!ISPRESSED(scanCode) || keysMap[ISUPPERCASE(scanCode) ? UPPERCASE:LOWERCASE][KEY_ASCII(scanCode)] == 0){     // we should ignore scanCodes received from released key
        return 0;
    }
    char out = keysMap[ISUPPERCASE(scanCode) ? UPPERCASE:LOWERCASE][KEY_ASCII(scanCode)];
    return out;
}

int isPrintable(char out){
    return out != 0;
}

void addKeyToBuffer(char out){
    totalBuffer[bufferSize] = out;
    bufferSize++;
}

extern uint32_t inb0x60();

void readBufferChar(){
    uint32_t scanCode = inb0x60();       // get scan code of key from asm function
    char out = processKey(scanCode);
    if (isPrintable(out)){
        addKeyToBuffer(out);
        putChar(out);    // TODO: ver si funca putChar
    }
}


void processBuffer(){
    readBufferChar();       // start reading
    //bufferSize++;           // so as not to write more then buffer max size
    return ;
}

// TODO: BORRAR
// scanf --> llama a syscall read --> por cada key que recibe llama a processBuffer
// processBuffer lee el scancode de la key, la interpreta (processKey), 
// y la imprime en pantalla (drawChar)
// ademas processBuffer va creando otro buffer con el string completo
// para despues interpretarlo como un posible comando
//
// teclado --> genera una interrupcion --> en 0x60 tiene guardada la letra que se 
// escribio --> se llama a processBuffer --> procesa la letra segun el scancode de
// 0x60 y la imprime --> a su vez va guardando todo en un buffer para despues
// hacer comparaciones con el texto completo que typeo el usuario
