#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

#define DEFAULT_WIDTH   8
#define DEFAULT_HEIGHT  18

uint8_t * getFramebuffer();
int getWidth();
int getHeight();

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void putChar(char c);
void putCharAt(char c, uint64_t x, uint64_t y);
void putCharColor(char c, uint32_t color);
void putCharColorAt(char c, uint32_t color, uint64_t x, uint64_t y);

void putString(char * str);
void putStringAt(const char * str, uint64_t x, uint64_t y);
void putStringColor(const char * str, uint32_t color);
void putStringColorAt(const char * str, uint32_t color, uint64_t x, uint64_t y);

int backSpace();
void newLine();
void spaceBar();
void newLineC();
void cleanScreen();
void incSize();
void decSize();

void incCurrentPosX(int increase);
void resetCurrentPosX(int newPosX);
void incCurrentPosY(int decrease);
void resetCurrentPosY(int newPosY);
int getCurrPosX();
int getCurrPosY();

void drawColoredRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void drawColoredCircle(uint32_t hexColor, uint32_t x1, uint32_t y1, uint32_t radius);

#endif