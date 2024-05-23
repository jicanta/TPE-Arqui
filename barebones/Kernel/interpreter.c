#include <videoDriver.h>
#include <syscalls.h>
#include <lib.h>

#define COMMDIM  7      // TODO: no me gusta el magic number me gustaria mas un size of
#define REGS     18

extern void exception00();
extern void exception06();
extern void sys_call(int id);

typedef struct {
    void (* fn)();
    char * name;
} comms;

void help(){        // TODO: ver si la cambiamos o dejamos esto
    newLine();
    putString("The following are valid commands:");
    newLine();
    tabBar();
    putString("    help            -- displays information on current shell.");
    newLine();
    tabBar();
    putString("    div zero        -- simulates a division by zero exception.");
    newLine();
    tabBar();
    putString("    inv opcode      -- simulates an invalid op code exception.");
    newLine();
    tabBar();
    putString("    time            -- displays current time.");
    newLine();
    tabBar();
    putString("    registers       -- last saved register info (CTRL+R to save at any given time)");
    newLine();
    tabBar();
    putString("    zoom in         -- augments letter size. WARNING: this command clears the whole screen.");
    newLine();
    tabBar();
    putString("    zoom out        -- diminishes letter size. WARNING: this command clears the whole screen");
    newLineC();
}

void divzero() {
    exception00();
}

void invopcode() {
    exception06();
}

void time() {
    sys_call(3);
}

void getregisters() {
    for (int i = 0; i < REGS ; i++){
        putString("hola");
        newLine();
    }
}

void zoomin() {
    return ;
}

void zoomout() {
    return ;
}

comms commands[] = {{help, "help"}, {divzero, "div zero"}, {invopcode, "inv opcode"}, {time, "time"}, {getregisters, "registers"}, {zoomin, "zoom in"}, {zoomout, "zoom out"}};

void interpretCommand(char * buffer){
    int i = 0;
    while (i < COMMDIM){
        if (strcmp(buffer, commands[i].name) == 0){
            commands[i].fn();
        }
        i++;
    }
    newLine();
    putString("buffer : command not found");
}