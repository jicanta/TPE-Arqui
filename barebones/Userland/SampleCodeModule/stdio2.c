#include <stdio.h>
#include <stdint.h>

#define STDIN       0
#define STDOUT      1

#define DEFAULT_STR_LEN     20

sys_read_front_asm(uint64_t fileDescriptor, char * location, uint64_t length);

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
    sys_write_front_asm(STDOUT, &c);
}

void printF(char * string) {
    sys_write_front_asm(STDOUT, string);
}

void putcharatF(char c, uint64_t x, uint64_t y){
    sys_write_at_front_asm(STDOUT, c, x, y);
}

void putstringatF(const char * str, uint64_t x, uint64_t y) {
    sys_write_at_front_asm(STDOUT, str, x, y);
}

void putcharcolorF(char c, uint32_t color){
    sys_write_color_front_asm(STDOUT, c, color);
}

void putstringcolorF(const char * str, uint32_t color){
    sys_write_color_front_asm(STDOUT, str, color);
}   

void putcharcoloratF(char c, uint32_t color, uint64_t x, uint64_t y){
    sys_write_color_at_front_asm(STDOUT, c, color, x, y);
}

void putstringcoloratF(const char * str, uint32_t color, uint64_t x, uint64_t y){
     sys_write_color_at_front_asm(STDOUT, str, color, x, y);
}

char c[1];
char getcharF() {
    sys_read_front_asm(0, c, 1);
    return (*(c));
}
char * scan2F() {
    char str[DEFAULT_STR_LEN];
    sys_read_front_asm(STDIN, str, DEFAULT_STR_LEN);
    return str;
}
