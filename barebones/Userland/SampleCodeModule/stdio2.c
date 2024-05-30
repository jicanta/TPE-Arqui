#include <stdio.h>
#include <stdint.h>

#define STDIN       0
#define STDOUT      1

#define DEFAULT_STR_LEN     20

void sys_read_front_asm(uint64_t fd, char * loc, uint64_t length);
void sys_write_front_asm(uint64_t fd, char * str);

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
    char * aux;
    *aux = c;
    sys_write_front_asm(STDOUT, aux);
}

void printF(char * string) {
    sys_write_front_asm(STDOUT, string);
}

char getcharF() {
    char * c;
    sys_read_front_asm(STDIN, c, 1);
    return c;
}
char * scanF() {
    char str[DEFAULT_STR_LEN];
    sys_read_front_asm(STDIN, str, DEFAULT_STR_LEN);
    return str;
}
