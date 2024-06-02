#include <time.h>
#include <stdint.h>

static uint64_t ticks = 0;

void timer() {
    ticks++;
}

uint64_t getTicks() {
    return ticks;
}

uint64_t getSeconds() {
    return ticks/18;
}

uint64_t getMilliSeconds() {
    return (ticks * 1000)/18;
}
 
void sleep(uint64_t secs) {
    uint64_t startTime = getSeconds();
    uint64_t currTime = startTime;
    while (currTime < startTime + secs) {
        currTime = getSeconds();
    }
    return;
}

void nanosleep(uint64_t millis) {
    uint64_t startTime = getMilliSeconds();
    uint64_t currTime = startTime;
    while (currTime < startTime + millis) {
        currTime = getMilliSeconds();
    }
    return;
}

