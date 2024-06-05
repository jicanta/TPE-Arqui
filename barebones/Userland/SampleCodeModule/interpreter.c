#include <stdio2.h>
#include <strings2.h>
#include <stdint.h>
#include <eliminator.h>
#include <music.h>

#define COMMDIM  13
#define REGS     18
#define CLEAR    8

extern void sys_time_front_asm();
extern void sys_registers_front_asm();
extern void sys_clean_front_asm();

extern void exception06_asm();
extern void exception00_asm();

extern void sys_registers_front_asm();

extern void test00();
extern void test06();

typedef struct {
    void (* fn)();
    char * name;
} comms;

void help() {
    printF("The following are valid commands:\n");
    printF("    help          -- displays information on current shell.\n");
    printF("    divzero       -- simulates a division by zero exception.\n");
    printF("    invopcode     -- simulates an invalid op code exception.\n");
    printF("    time          -- displays current time.\n");
    printF("    registers     -- last saved register info (press shift to save at any given time).\n");
    printF("    zoomin        -- augments letter size. WARNING: this command clears the screen.\n");
    printF("    zoomout       -- diminishes letter size. WARNING: this command clears the screen.\n");
    printF("    clear         -- clears the whole screen.\n");
    printF("    eliminator    -- initiates \"eliminator\" test game.\n");
    printF("    furelise      -- plays the famous song!\n");
    printF("    happybirthday -- plays the happy birthday song\n");
    printF("    cantinaband   -- plays the iconic star wars song\n");
    printF("    tetris        -- plays the tetris theme song\n");
}

void divzero() {
    test00();
}

void invopcode() {
    test06();
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

void eliminatorCommand() {
    eliminator();
}

comms commands[] = {{help, "help"}, {divzero, "divzero"}, {invopcode, "invopcode"}, {time, "time"}, {getregisters, "registers"}, {zoomin, "zoomin"}, {zoomout, "zoomout"}, {clear, "clear"}, {eliminatorCommand, "eliminator"}, {happyBirthday, "happybirthday"}, {furElise, "furelise"}, {cantinaBand, "cantinaband"}, {tetris, "tetris"}};

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
