#include <stdio2.h>
#include <strings2.h>
#include <interpreter.h>

char buffer[50];
int buffersize = 0;

void addCharToBuffer(char c){
	buffer[buffersize++] = c;
}

int main() {
	printF("hola chicos\n");
	/*while (1) {
		char c = getcharF();
		if (c != 0) {
			if (c == '\n') {
				buffer[buffersize] = '\0';
				interpretCommand(buffer);
				buffersize = 0;
			}
			else {
				putcharF(c);
				addCharToBuffer(c);
			}
		}
	}*/
}