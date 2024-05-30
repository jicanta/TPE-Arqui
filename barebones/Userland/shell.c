#include <stdio2.h>
#include <strings2.h>
#include <interpreter.h>

char buffer[50];
int buffersize = 0;

void addCharToBuffer(char c){
	buffer[buffersize++] = c;
}

int main() {
	while (1) {
		char c = getchar();
		if (c != '\0') {
			putchar(c);
			addCharToBuffer(c);
		}
		if (c == '\n') {
			buffer[buffersize] = '\0';
			interpretCommand(buffer);
			buffersize = 0;
		}
	}
}