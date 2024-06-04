#include <shell.h>
#include <stdio2.h>
#include <interpreter.h>

#define MAX_BUFFER_SIZE		6000

char lastRead[1];
int totalbuffersize = 0;
char totalbuffer[MAX_BUFFER_SIZE];

void runShell(){
    startShell();
    while (totalbuffersize < MAX_BUFFER_SIZE){
		lastRead[0] = getcharF();
		if (lastRead[0] != '\b'){
			if (lastRead[0] == '\n'){
				totalbuffer[totalbuffersize] = '\0';
				printF("\n");
				interpretCommand(totalbuffer);
				totalbuffersize = 0;
				startShell();
			}
			else {
				putcharF(lastRead[0]);
				totalbuffer[totalbuffersize] = lastRead[0];
				totalbuffersize++;
			}
		}
		else {	// last read is a backspace
			if (totalbuffersize > 0){
				putcharF(lastRead[0]);
				totalbuffersize--;
			}
			else {
				beepF();
			}
		}
	}
}

