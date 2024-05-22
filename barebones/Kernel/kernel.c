#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
// TODO: borrar
#include <videoDriver.h>

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


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

char* itoa(int val, int base) {

    if (val < 10) {
	static char s[3];
	s[0] = '0';
	s[1] = val + '0';
	s[2] = '\0';
	return s;
    }

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];

}

uint32_t get_minutes();
uint32_t get_seconds();
uint32_t get_hours();

void printMinutes(int x, int y) {
	draw_string(itoa(get_minutes(), 10), 0xFF0000, x, y);
}

void printHours(int x, int y) {
        draw_string(itoa(get_hours() - 0x3, 10), 0xFF0000, x, y);
}

void printSeconds(int x, int y) {
        draw_string(itoa(get_seconds(), 10), 0xFF0000, x, y);
}

void printCurTime(int x, int y) {
	printHours(x, y);
	draw_string(":", 0xFF0000, x + 8 * 2, y);
	x += 8 * 3 + 1;
	printMinutes(x, y);
	draw_string(":", 0xFF0000, x + 8 * 2, y);
	x += 8 * 3;
	printSeconds(x, y);
}


int main()
{      
 //       ncPrint("HOla");
//	printHours();	
//        printMinutes();
//	printSeconds();
//
//
	printCurTime(120, 120);
	draw_string("Bienvenidos a DRACULAOS. Escribir \"help\" para ver mas comandos.", 0xFF0000, 0, 0);
		draw_string("$", 0xFF0000, 0, 0 + 16);	
	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();

	ncPrint("[Finished]");
	return 0;
}

