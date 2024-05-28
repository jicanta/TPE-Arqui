#include <stdint.h>
#include <lib.h>
#include <videoDriver.h>

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

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

char* itoa(int val, int base) {
    if (val < 10) {
	static char s[3];
	s[0] = '0';
	s[1] = val + '0';
	s[2] = '\0';
	return s;
    }

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];
	
}

extern uint32_t get_minutes();
extern uint32_t get_seconds();
extern uint32_t get_hours();

void printMinutes() {
	putString(itoa(get_minutes(), 10)); putChar('m');
}

void printHours() {
	putString(itoa(get_hours() - 0x3, 10)); putChar('h');
}

void printSeconds() {
    putString(itoa(get_seconds(), 10)); putChar('s');
}

void printCurTime() {
	newLine();
	putString("Time:");
	putChar('\t');
	printHours();
	putChar(': ');
	printMinutes();
	putChar(": ");
	printSeconds();
	newLineC();
}