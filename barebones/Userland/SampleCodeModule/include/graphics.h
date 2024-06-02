#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdint.h>

static const uint32_t WHITE = 0xFFFFFF;
static const uint32_t BLACK = 0x000000;
static const uint32_t RED = 0xFF0000;
static const uint32_t GREEN = 0x00FF00;
static const uint32_t BLUE = 0x0000FF;
static const uint32_t YELLOW = 0xFFFF00;
static const uint32_t PINK = 0xFF00FF;
static const uint32_t CYAN = 0x00FFFF;

void putPixel(uint32_t hexColor, uint32_t x, uint32_t y);

void drawRectangle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

void drawCircle(uint32_t hexColor, uint32_t x, uint32_t y, uint32_t radius);

#endif