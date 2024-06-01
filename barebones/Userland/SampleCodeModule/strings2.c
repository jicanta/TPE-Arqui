#include <strings.h>

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

int strcmp(const char * str1, const char * str2){		// 0 if strings are equal, 1 if not
	while (*str1) {
        if (*str2 == '\0'){
            return 1;
        }
        if (toLower((unsigned char)*str1) != toLower((unsigned char)*str2)) {
            return 1;  // strings are not equal
        }
        str1++;
        str2++;
    }
    return 0;
}

int strlength(const char* s) {
    int i = 0;
    while (*(s+(i++)) != '\0') {}
    return i - 1;	
}
