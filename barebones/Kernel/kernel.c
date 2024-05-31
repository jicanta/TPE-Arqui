#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <videoDriver.h> // sacarlo

extern void _hlt();
extern void load_idt();

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase() {
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}


int main() {
	load_idt();
	/*beep(261);
	beep(261);
	beep(293);
	beep(261);
	beep(349);
	beep(329);
	beep(261);
	beep(261);
	beep(293);
	beep(261);
	beep(392);
	beep(349);
	beep(261);
	beep(261);
	beep(523);
	beep(440);
	beep(349);
	beep(329);
	beep(293);
	beep(466);
	beep(466);
	beep(440);
	beep(349);
	beep(392);
	beep(349);*/
	//newLineC();
	//putString("hola");
	newLineC();
	//putStringColor("chau", 0xFF0000);
	//putStringColorAt("hellooo", 0x00FF00, 500, 500);
	((EntryPoint)sampleCodeModuleAddress)();
	while(1) {
		
	}
	return 0;
}
