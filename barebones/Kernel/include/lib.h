#ifndef LIB_H_
#define LIB_H_


void * memset(void * destination, int32_t c, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

char* itoa(int val, int base);
#endif
