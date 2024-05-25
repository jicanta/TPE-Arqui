#include <keyboardDriver.h>
#include <videoDriver.h>    // TODO: BORRAR
#include <naiveConsole.h>

// defining a new data type: pointer to a interruption function that returns void
typedef void (*ints)();

// timer tick interruption
static void int_20(){
    
}

// keyboard interruption
static void int_21(){
    processBuffer();
}

static ints interruptions[] = {int_20, int_21}; // in interruptions[0] timer tick, in interruptions[1] keyboard

int interruptionsDim = sizeof(interruptions) / sizeof(interruptions[0]);

void irqHandler(uint64_t irq){
    if (irq < 0 || irq > interruptionsDim){
        return ;                      // interruption does not exist
    }
    interruptions[irq]();      // requested interruption is called
}
