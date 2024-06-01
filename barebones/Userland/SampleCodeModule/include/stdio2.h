#ifndef STDIO_H_
#define STDIO_H_

#include <stdint.h>

char * itoa(int val, int base);
char * atoi(int val);
char * numToStr(int num);
void putcharF(char c);
void printF(char * string);
char getcharF();
char * scanF();
void putcharatF(char c, uint64_t x, uint64_t y);
void putstringatF(const char * str, uint64_t x, uint64_t y);
void putcharcolorF(char c, uint32_t color);
void putstringcolorF(const char * str, uint32_t color);
void putcharcoloratF(char c, uint32_t color, uint64_t x, uint64_t y);
void putstringcoloratF(const char * str, uint32_t color, uint64_t x, uint64_t y);

#endif