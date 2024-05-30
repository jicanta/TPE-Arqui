#include <soundDriver.h>

extern void outPIT(int register, uint8_t val);
extern uint8_t inPIT(int register);

void playSound(uint32_t nFrequence) {
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
}

void stopSound() {
    uint8_t tmp = inPIT(0x61) & 0xFC;
    outPIT(0x61, tmp);
}

void beep() {
   for(int i = 0; i < 100000; i++) playSound(1000);
    // aca deberia ir un timerWait
    stopSound();
}
