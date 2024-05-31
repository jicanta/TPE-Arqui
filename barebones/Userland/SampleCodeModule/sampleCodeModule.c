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
	//printF("FELIZ CUMPLEAÑOS CHICOS");
	//printF("FELIZ CUMPLEAÑOS CHICOS");
	//putstringatF("FELIZ CUMPLEAÑOS CHICOS", 400, 400);
	putstringcolorF("FELIZ CUMPLEAÑOS CHICOS", 0x00FF00);
	putstringcolorF("FELIZ CUMPLEAÑOS CHICOS", 0x123456);
	putstringcoloratF("FELIZ CUMPLEAÑOS CHICOS", 0x123456, 250, 250);
	/*while (1) {
		char c = getcharF();
		putcharF(c);
	}*/
}
