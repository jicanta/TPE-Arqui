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
char c;

int main() {
	//putcharF('a');
	/*printF("LA RE COMCHA DE TU HERMANA TP DE MIERDAAAA ");
	putcharF('a');
	c = getcharF();
	putcharF(c);*/
	while(1){
		putcharF('a');
		c = getcharF();
		putcharF('b');
		putcharF(c);
	}
}
