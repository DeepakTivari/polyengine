ASM = nasm

CC = g++

AFLAGS = -felf64 -g -F dwarf

CFLAGS = -c -Wall -O2 -g

LFLAGS = -no-pie

all: virus polymake

polymake: polyengine.o polymorphicengine.o
	$(CC) $(LFLAGS) $^ -o $@
	
virus: virus.o
	$(CC) $(LFLAGS) $< -o $@

virus.o: virus.asm template.asm.inc
	$(ASM) $(AFLAGS) $< -o $@

polyengine.o: polymake.cpp
	$(CC) $(CFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@