#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

char processKey(uint32_t key);

void processBuffer(char buffer);

int fullBuffer();

int emptyBuffer();

#endif
