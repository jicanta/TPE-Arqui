#ifndef LIB_H_
#define LIB_H_


void * memset(void * destination, int32_t c, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

int strcmp(const char * str1, const char * str2);
char toLower(char c);

char* itoa(int val, int base);

void printMinutes();
void printHours();
void printSeconds();
void printCurrTime();

#endif
