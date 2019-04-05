ASM = nasm

GCC = g++

AFLAGS = -felf64 -g -F dwarf

CFLAGS = -c -Wall -O2 -g

LFLAGS = -no-pie

all: virus polymake

polymake: polyengine.o polymorphicengine.o
	$(GCC) $(LFLAGS) $^ -o $@
	
virus: virus.o
	$(GCC) $(LFLAGS) $< -o $@

virus.o: virus.asm template.asm.inc
	$(ASM) $(AFLAGS) $< -o $@

polyengine.o: polymake.cpp
	$(GCC) $(CFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@