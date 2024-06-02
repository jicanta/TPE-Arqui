#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>

void timer();
uint64_t getTicks();
uint64_t getSeconds();
uint64_t getMilliSeconds();
void sleep(uint64_t secs);
void nanosleep(uint64_t millis);

#endif