// defining a new data type: pointer to a exception function that returns void
typedef void(* excep)();

// defining a new data struct: exception message and exception function
typedef struct {
    const char * msg;
    excep excepFunction;
} excepFull;

excepFull exceptions[] = { {"Cannot divide by zero", zero_division},
                            " ", reserved }


#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	// Handler para manejar excepcíon
}
