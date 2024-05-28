#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

#define DEFAULT_WIDTH   8
#define DEFAULT_HEIGHT  18

uint8_t * getFramebuffer();
int getWidth();
int getHeight();
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
int backSpace();
void putChar(char c);
void putString(char * c);
void newLine();
void spaceBar();
void newLineC();
void incCurrentPosX(int increase);
void resetCurrentPosX(int newPosX);
void incCurrentPosY(int decrease);
void resetCurrentPosY(int newPosY);
void cleanScreen();

#endif
