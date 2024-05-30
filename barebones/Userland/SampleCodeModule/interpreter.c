#include <stdio2.h>
#include <strings2.h>
#include <stdint.h>

#define COMMDIM  8      // TODO: no me gusta el magic number me gustaria mas un size of
#define REGS     18

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

void help(){        // TODO: ver si la cambiamos o dejamos esto
    printF("\n");
    printF("The following are valid commands:");
    printF("\n");
    printF("    help            -- displays information on current shell.");
    printF("\n");
    printF("    divzero        -- simulates a division by zero exception.");
    printF("\n");
    printF("    invopcode      -- simulates an invalid op code exception.");
    printF("\n");
    printF("    time            -- displays current time.");
    printF("\n");
    printF("    registers       -- last saved register info (press shift to save at any given time).");
    printF("\n");
    printF("    zoomin         -- augments letter size. WARNING: this command clears the whole screen.");
    printF("\n");
    printF("    zoomout        -- diminishes letter size. WARNING: this command clears the whole screen");
    printF("\n");
    printF("    clear        -- clears the whole screen.");
}

void divzero() {
    printF("\n");
    exception00_asm();
}

void invopcode() {
    printF("\n");
    exception06_asm();
}

void time() {
    printF("\n");
    sys_time_front_asm();
}

void getregisters() {
    printF('\n');
    sys_registers_front_asm();
}

void zoomin() {
    printF("zoom");
    return ;
}

void zoomout() {
    printF("chau zoom");
    return ;
}

void clear(){
    sys_clean_front_asm();
    return;
}

comms commands[] = {{help, "help"}, {divzero, "divzero"}, {invopcode, "invopcode"}, {time, "time"}, {getregisters, "registers"}, {zoomin, "zoomin"}, {zoomout, "zoomout"}, {clear, "clear"}};

void interpretCommand(char * buffer){
    int i = 0;
    while (i < COMMDIM){
        if (strcmp(buffer, commands[i].name) == 0){
            commands[i].fn();
            printF("\n");
            return;
        }
        i++;
    }
    printF("\n");
    printF("buffer : command not found");
    printF("\n");
}
