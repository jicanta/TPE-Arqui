#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

char processKey(uint32_t key);
void processBuffer();
int fullBuffer();
int emptyBuffer();
uint32_t getLastPressedSC();
char getLastAscii();

#endif
