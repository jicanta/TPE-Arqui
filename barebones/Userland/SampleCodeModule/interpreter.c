#include <stdio2.h>
#include <strings2.h>
#include <stdint.h>

#define COMMDIM  8
#define REGS     18
#define CLEAR    8

extern void sys_time_front_asm();
extern void sys_registers_front_asm();
extern void sys_clean_front_asm();

extern void exception06_asm();
extern void exception00_asm();

extern void sys_registers_front_asm();

typedef struct {
    void (* fn)();
    char * name;
} comms;

void help() {
    printF("The following are valid commands:");
    printF("\n");
    printF("    help         -- displays information on current shell.");
    printF("\n");
    printF("    divzero      -- simulates a division by zero exception.");
    printF("\n");
    printF("    invopcode    -- simulates an invalid op code exception.");
    printF("\n");
    printF("    time         -- displays current time.");
    printF("\n");
    printF("    registers    -- last saved register info (press shift to save at any given time).");
    printF("\n");
    printF("    zoomin       -- augments letter size. WARNING: this command clears the screen.");
    printF("\n");
    printF("    zoomout      -- diminishes letter size. WARNING: this command clears the screen.");
    printF("\n");
    printF("    clear        -- clears the whole screen.");
}

void divzero() {
    exception00_asm();
}

void invopcode() {
    exception06_asm();
}

void time() {
    sys_time_front_asm();
}

void getregisters() {
    sys_registers_front_asm();
}

void clear() {
    sys_clean_front_asm();
}

void zoomin() {
    biggerText();
}

void zoomout() {
    smallerText();
}

comms commands[] = {{help, "help"}, {divzero, "divzero"}, {invopcode, "invopcode"}, {time, "time"}, {getregisters, "registers"}, {zoomin, "zoomin"}, {zoomout, "zoomout"}, {clear, "clear"}};

void interpretCommand(char * buffer){
    int i = 0;
    while (i < COMMDIM && *buffer) {
        if (strcmp(buffer, commands[i].name) == 0){
            commands[i].fn();
            if (i<=4) {
                putcharF('\n');
            }
            return;
        }
        i++;
    }
    printF("buffer : command not found\n");
}
