ASM = nasm

CC = g++

AFLAGS = -felf64 -g -F dwarf

CFLAGS = -c -Wall -O2 -g

LFLAGS = -no-pie

all: virus polyengine

polyengine: polyengine.o morphengine.o
	$(CC) $(LFLAGS) $^ -o $@
	
virus: virus.o
	$(CC) $(LFLAGS) $< -o $@

virus.o: virus.asm turnpoly.asm
	$(ASM) $(AFLAGS) $< -o $@

polyengine.o: polyengine.cpp
	$(CC) $(CFLAGS) $< -o $@

morphengine.o: morphengine.asm
	$(ASM) $(AFLAGS) $< -o $@