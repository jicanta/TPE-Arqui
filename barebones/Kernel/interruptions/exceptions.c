#define ZERODIVISION 0
#define INVALIDOPCODE 6

// defining a new data type: pointer to a exception function that returns void
typedef void(* excep)();

// defining a new data struct: exception message and exception function
typedef struct {
    const char * msg;
    excep excepFunction;
} excepFull;

excepFull exceptions[] = { {"Cannot divide by zero", zero_division},
                            " ", reserved,
			    " ", reserved,
			    " ", reserved,
			    " ", reserved,
			    " ", reserved,
			    "Invalid op code", invalid_op_code}

void exceptionHandler(int excepNum) {
	if (excepNum != ZERODIVISION || excepNum != INVALIDOPCODE){
		return ;		// exception does not exist
	}
	return exceptions[excepNum];	
}

void zero_division() {
	// TODO: complete exception
}

void invalid_op_code() {
	// TODO: complete exception
}
