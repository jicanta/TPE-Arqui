#include <stdio2.h>
#include <strings2.h>
#include <interpreter.h>
#include <stdint.h>

#define MAX_BUFFER_SIZE		6000

int totalbuffersize = 0;
char totalbuffer[MAX_BUFFER_SIZE];

void sys_read_front_asm(uint64_t fileDescriptor, char * location, uint64_t length);

char lastRead[1];

int main() {
	putstringcolorF("$", (uint32_t) 0x00FF00);
	while (totalbuffersize < MAX_BUFFER_SIZE){
		lastRead[0] = getcharF();
		putcharF(lastRead[0]);
		if (lastRead[0] != '\b'){
			if (lastRead[0] == '\n'){
				totalbuffer[totalbuffersize] = '\0';
				interpretCommand(totalbuffer);
				totalbuffersize = 0;
			}
			else {
				totalbuffer[totalbuffersize++] = lastRead[0];
			}
		}
	}
	printF("se llego al final del buffer");
}
