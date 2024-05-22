#include <stdio.h>
#include <keyboardDriver.h>
#include <videoDriver.h>

#define BLOCKMAYUSC     0x3A
#define LEFTSHIFT       0x2A
#define RIGHTSHIFT      0x36
#define LEFTCTRL        0x1D
#define RIGHTCTRL       0xE01D
#define ENTER           0x1C
#define BACKSPACE       0x53

#define BUFFER_MAX_SIZE 6000     // can write up to 6000 chars which takes up almpst the entire screen
#define MASK            0x7F
#define UNPRESSEDCODE   0x80
#define LOWERCASE       0
#define UPPERCASE       1

#define ISUPPERCASE()       (mayuscOn || ISPRESSED(LEFTSHIFT) || ISPRESSED(RIGHTSHIFT))
#define ISPRESSED(key)      (((key) & UNPRESSEDCODE) == 0)
#define KEY_ASCII(scanCode) ((scanCode) & MASK)    

char * totalBuffer;
int bufferSize = 0;     // TODO: ver si sirve de algo buffer size o no
int mayuscOn = 0;       // turned on if block mayusc is on
int ctrlPressed = 0;    // "boolean" to know if ctrl is pressed or not

uint8_t lowerCaseMap[] = {
    '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t',  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\n',
    0,  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '\\', 0,
    0, 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0 
};

uint8_t upperCaseMap[] = {
    '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t',  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '|',
    0,  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '\n',
    0,  'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    0, 0, 0, 0, ' ', 0, 0, 0, 0, 0, 0 
};

uint8_t * keysMap[] = {lowerCaseMap, upperCaseMap};

void saveBuffer(){
    // interpretCommand(totalBuffer);      // TODO: write command interpreter to receive string
    bufferSize = 0;
}

char processKey(uint32_t scanCode){
    if (scanCode == ENTER){
        // saveBuffer();           // typing is donde for now
        return 0;
    }
    if (scanCode == BACKSPACE){
        backSpace();
    }
    if (!ISPRESSED(scanCode) || keysMap[LOWERCASE][KEY_ASCII(scanCode)] == 0){
        return 0;
    }
    if ((scanCode == BLOCKMAYUSC) && ISPRESSED(scanCode)){
        mayuscOn = !mayuscOn;
        return 0;
    }
    if (scanCode == LEFTCTRL || scanCode == RIGHTCTRL){
        ctrlPressed = (ISPRESSED(scanCode));
        return 0;
    }
    char out = keysMap[ISUPPERCASE()? UPPERCASE:LOWERCASE][KEY_ASCII(scanCode)];
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
    putChar('a');
    if (isPrintable(out)){
        addKeyToBuffer(out);
        putChar(out);    // TODO: ver si funca putChar
    }
}


void processBuffer(){
    putChar('a');
    readBufferChar();       // start reading
    bufferSize++;           // so as not to write more then buffer max size
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
