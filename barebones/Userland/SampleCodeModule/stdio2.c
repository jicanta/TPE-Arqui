#include <stdio.h>
#include <stdint.h>

#define STDIN       0
#define STDOUT      1

#define DEFAULT_STR_LEN     20

void sys_read_front_asm(uint64_t fileDescriptor, char * location, uint64_t length);
void sys_write_color_front_asm(uint64_t fileDescriptor, const char * string, uint32_t color);
void sys_write_color_at_front_asm(uint64_t fileDescriptor, const char * string, uint32_t color, uint64_t x, uint64_t y);
void sys_zoomin();
void sys_zoomout();

char * itoa(int val, int base) {
    if (val < 10) {
	    static char s[3];
	    s[0] = '0';
	    s[1] = val + '0';
	    s[2] = '\0';
	    return s;
    }
    static char buf[32] = {0};
    int i = 30;
    for(; val && i ; --i, val /= base) {
        buf[i] = "0123456789abcdef"[val % base];
    }
    return &buf[i+1];
}

int atoi(char* str) {
    int ret = 0;
    int i = 0;
    while (str[i]) {
        ret = 10 * ret + (str[i++] - '0');
    }
}

char * numToStr(int num) {
    itoa(num, 10);
}

void putcharF(char c) {
    putcharcolorF(c, 0xFFFFFF);
}

void printF(char * string) {
    putstringcolorF(string, 0xFFFFFF);
}

void putcharatF(char c, uint64_t x, uint64_t y){
    putcharcoloratF(c, 0xFFFFFF, x, y);
}

void putstringatF(const char * str, uint64_t x, uint64_t y) {
    putstringcoloratF(str, 0xFFFFFF, x, y);
}

void putcharcolorF(char c, uint32_t color){
    sys_write_color_front_asm(STDOUT, &c, color);
}

void putstringcolorF(const char * str, uint32_t color){
    sys_write_color_front_asm(STDOUT, str, color);
}   

void putcharcoloratF(char c, uint32_t color, uint64_t x, uint64_t y){
    sys_write_color_at_front_asm(STDOUT, &c, color, x, y);
}

void putstringcoloratF(const char * str, uint32_t color, uint64_t x, uint64_t y){
     sys_write_color_at_front_asm(STDOUT, str, color, x, y);
}

char c[1];
char getcharF() {
    sys_read_front_asm(0, c, 1);
    return (*(c));
}
char * scanF() {
    char str[DEFAULT_STR_LEN];
    sys_read_front_asm(STDIN, str, DEFAULT_STR_LEN);
    return str;
}

void biggerText() {
    sys_zoomin();
}

void smallerText() {
    sys_zoomout();
}

void startShell() {
    putstringcolorF("$", 0x00FF00);
}