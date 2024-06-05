#include <sounds.h>
#include <stdint.h>

void sys_beep();

void beepF(uint32_t nFreq, uint64_t time) {
    sys_beep(nFreq, time);
}