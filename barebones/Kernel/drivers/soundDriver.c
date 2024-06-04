#include <soundDriver.h>
#include <time.h>

extern void outPIT(int register, uint8_t val);
extern uint8_t inPIT(int register);

void beep(uint32_t nFrequence, uint64_t time) {
    uint32_t Div;
    uint8_t tmp;

    Div = 1193180 / nFrequence;
    outPIT(0x43, 0xb6);
    outPIT(0x42, (uint8_t) (Div));
    outPIT(0x42, (uint8_t) (Div >> 8));

    tmp = inPIT(0x61);
    if (tmp != (tmp | 3)) {
	    outPIT(0x61, tmp | 3);
    }

    millisleep(1000 / time);

    tmp = inPIT(0x61) & 0xFC;
    outPIT(0x61, tmp);
}
