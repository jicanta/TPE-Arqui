include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
ASM_SOURCES=caller.asm test00.asm test06.asm
ASM_OBJECTS=$(ASM_SOURCES:.asm=.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(ASM_OBJECTS)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(SOURCES) $(ASM_OBJECTS) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) $(ASM_OBJECTS) -o ../0000-sampleCodeModule.elf

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean
