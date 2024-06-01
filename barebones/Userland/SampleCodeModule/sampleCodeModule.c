#include <stdio2.h>
#include <strings2.h>
#include <interpreter.h>
#include <stdint.h>

#define MAX_BUFFER_SIZE		6000

int main() {
	startShell();
	biggerText();
	int totalbuffersize = 0;
	char totalbuffer[MAX_BUFFER_SIZE];
	char lastRead[1];
	//putstringcolorF("$", (uint32_t) 0x00FF00);
	//putstringcolorF("hola", (uint32_t) 0xFF0000);
	while (totalbuffersize < MAX_BUFFER_SIZE){
		lastRead[0] = getcharF();
		if (lastRead[0] != '\b'){
			if (lastRead[0] == '\n'){
				totalbuffer[totalbuffersize] = '\0';
				putcharF(lastRead[0]);
				interpretCommand(totalbuffer);
				totalbuffersize = 0;
				totalbuffer[totalbuffersize] = '\0';
				putcharF(lastRead[0]);
				startShell();
			}
			else {
				putcharF(lastRead[0]);
				totalbuffer[totalbuffersize++] = lastRead[0];
			}
		}
		else {	// last read is a backspace
			if (totalbuffersize > 1){
				//putcharF(lastRead[0]);
				totalbuffersize--;
			}
		}
	}
	printF("se llego al final del buffer");
}
