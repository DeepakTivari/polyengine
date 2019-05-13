ASM = nasm

GCC = g++
CC = gcc

AFLAGS = -felf64 -g -F dwarf 

CFLAGS = -c  -Wall -O2 -g

LFLAGS = -no-pie 
KFLAGS = -no-pie -nostartfiles -m64 -g
all: virus polymake

polymake: polyengine.o polymorphicengine.o
	$(GCC) $(LFLAGS) $^ -o $@
	
virus:  infect.c virus.o 
	$(CC) $(KFLAGS) $^ -o $@

virus.o: virus.asm template.asm.inc
	$(ASM) $(AFLAGS) $< -o $@

polyengine.o: polymake.cpp
	$(GCC) $(CFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@