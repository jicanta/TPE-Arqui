#include <keyboardDriver.c>

// defining a new data type: pointer to a interruption function that returns void
typedef void (*ints)();

// timer tick interruption
void int_20(){
    // TODO: completar
}

// keyboard interruption
void int_21(){
    processBuffer();
}

ints interruptions[] = {int_20, int_21}; // in interruptions[0] timer tick, in interruptions[1] keyboard

int interruptionsDim = sizeof(interruptions) / sizeof(interruptions[0]);

void irqHandler(uint64_t irq){
    if (irq < 0 || irq > interruptionsDim){
        return ;                      // interruption does not exist
    }
    return interruptions[irq]();      // requested interruption is called
}
