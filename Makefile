ASM = nasm

CC = gcc

AFLAGS = -felf64 -g -F dwarf

CFLAGS = -c -Wall -02 -g

LFLAGS = -no-pie

all: virus

virus: virus.o
	$(CC) $(LFLAGS) $< -o $@

virus.o: virus.asm turnpoly.inc
	$(ASM) $(AFLAGS) $< -o $@
