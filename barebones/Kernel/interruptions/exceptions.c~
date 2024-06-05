#include <exceptions.h>
#include <syscalls.h>
#include <videoDriver.h>

#define ZERODIVISION 0
#define INVALIDOPCODE 6

// defining a new data type: pointer to a exception function that returns void
typedef void(* excep)();

void zero_division() {
	putString("Cannot divide by zero");
	// TODO: imprimir registros
	// TODO: falta recuperar el stack y que todo vuelva a estar como estaba antes
}

void invalid_op_code() {
	putString("Invalid Op Code");
	// TODO: imprimir registros
	// TODO: falta recuperar el stack y que todo vuelva a estar como estaba antes
}

void reserved(){  //TODO: SIRVE DE ALGO??
	return ;
	// TODO: falta recuperar el stack y que todo vuelva a estar como estaba antes
}

excep exceptions[] = {zero_division, reserved, reserved, reserved, reserved, reserved, invalid_op_code};

void handler(excep e){
	e();
}

void exceptionHandler(int excepNum) {		// TODO: esta mal
	switch(excepNum){
		case ZERODIVISION:
			zero_division();
			break;
		case  INVALIDOPCODE:
			invalid_op_code();
			break;
	}
}
