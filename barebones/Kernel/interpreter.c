#include <videoDriver.h>
#include <syscalls.h>
#include <lib.h>

#define COMMDIM  8      // TODO: no me gusta el magic number me gustaria mas un size of
#define REGS     18

extern void exception00();
extern void exception06();
//extern void sys_call(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx);
extern void sys_call(uint64_t id);
extern void sys_time_front_asm();

extern void exception06_asm();
extern void exception00_asm();

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
}

void divzero() {
    newLine();
    exception00_asm();
}

void invopcode() {
    newLine();
    exception06_asm();
}

void time() {
    newLine();
    sys_time_front_asm();
}

void getregisters() {
    newLine();
    uint64_t * registers = getLastSavedRegisters();
    newLine();
     for (int i = 0; i < 17 ; i++){
        putString(itoa(registers[i],10));
        newLine();
    }
}

void zoomin() {
    putString("zoom");
    return ;
}

void zoomout() {
    putString("chau zoom");
    return ;
}

void clear(){
    cleanScreen();
}

comms commands[] = {{help, "help"}, {divzero, "divzero"}, {invopcode, "invopcode"}, {time, "time"}, {getregisters, "registers"}, {zoomin, "zoomin"}, {zoomout, "zoomout"}, {clear, "clear"}};

void interpretCommand(char * buffer){
    int i = 0;
    while (i < COMMDIM){
        if (strcmp(buffer, commands[i].name) == 0){
            commands[i].fn();
            newLineC();
            return;
        }
        i++;
    }
    newLine();
    putString("buffer : command not found");
    newLineC();
}
