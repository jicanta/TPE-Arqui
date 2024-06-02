#ifndef SOUND_DRIVER_H
#define SOUND_DRIVER_H

#include <stdint.h>

void playSound(uint32_t nFrequence);
void stopSound();
void beep(uint32_t nFrequence);

#endif
