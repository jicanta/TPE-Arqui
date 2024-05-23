#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

#define DEFAULT_WIDTH   10
#define DEFAULT_HEIGHT  36

uint8_t * getFramebuffer();
int getWidth();
int getHeight();
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void backSpace();
void putChar(char c);
void putString(char * c);
void newLine();
void newLineC();
void incCurrentPosX(int increase);
void resetCurrentPosX(int newPosX);
void incCurrentPosY(int decrease);
void resetCurrentPosY(int newPosY);

#endif
