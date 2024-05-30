#include <strings.h>

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

int strcmp(const char * str1, const char * str2){		// 0 if strings are equal, 1 if not
	while (*str1 && *str2) {
        if (toLower((unsigned char)*str1) != toLower((unsigned char)*str2)) {
            return 1;  // strings are not equal
        }
        str1++;
        str2++;
    }
    // if both strings end simultaneously, they are equal
    return (*str1 == '\0' && *str2 == '\0') ? 0 : 1;
}

int strlength(const char* s) {
    int i = 0;
    while (*(s+(i++)) != '\0') {}
    return i - 1;	
}
