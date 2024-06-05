#include <exceptions.h>
#include <syscalls.h>
#include <videoDriver.h>

#define ZERODIVISION 0
#define INVALIDOPCODE 6

// defining a new data type: pointer to a exception function that returns void
typedef void(* excep)();

void zero_division() {
	putString("Cannot divide by zero\n");
	sys_saveRegisters();
	sys_printRegisters();
	return;
}


void invalid_op_code() {
	putString("Invalid Op Code\n");
	sys_saveRegisters();
	sys_printRegisters();
	return;
}

void exceptionHandler(int excepNum) {
	switch(excepNum){
		case ZERODIVISION:
			zero_division();
			break;
		case  INVALIDOPCODE:
			invalid_op_code();
			break;
	}
	return;
}
