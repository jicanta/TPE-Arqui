#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

char* itoa(int val, int base);

uint32_t get_minutes();
uint32_t get_seconds();
uint32_t get_hours();

void printMinutes(int x, int y);

void printHours(int x, int y);

void printSeconds(int x, int y);

void printCurTime(int x, int y);

#endif
