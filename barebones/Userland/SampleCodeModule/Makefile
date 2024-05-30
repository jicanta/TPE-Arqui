include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(ASM) $(ASMFLAGS) caller.asm
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(SOURCES) caller.o -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) caller.o -o ../0000-sampleCodeModule.elf

clean:
	rm -rf *.o

.PHONY: all clean
