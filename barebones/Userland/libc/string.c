#include <string.h>

int strcmp(const char* p1, const char* p2) {
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
	    return c1 - c2;
    } while (c1 == c2);

    return c1 - c2;
}

int strlen(const char* s) {
    int i = 0;
    while (*(s+(i++)) != '\0') {}
    return i - 1;	
}
