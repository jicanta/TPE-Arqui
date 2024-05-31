#include <stdio2.h>
#include <strings2.h>
#include <interpreter.h>

char buffer[50];
int buffersize = 0;

void addCharToBuffer(char c){
	if (c == '\n' || c == '\b'){
		return;
	}
	buffer[buffersize++] = c;
}

int main() {
	printF("FELIZ CUMPLEAÑOS CHICOS");
	printF("FELIZ CUMPLEAÑOS CHICOS");
	/*while (1) {
		char c = getcharF();
		putcharF(c);
	}*/
}
