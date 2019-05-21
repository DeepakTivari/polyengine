# compile level production - NO debuging symbols

ASM = nasm
CC = gcc

AFLAGS = -felf64
CFLAGS = -c -Wall -falign-functions=16 -m64 

KFLAGS = -no-pie -nostartfiles
MFLAGS = -no-pie -r -nostdlib

all: turbopolymorphic.o


turbopolymorphic.o: polymorphicengine.o polymorphichandler.o bootloader.o
	$(CC) $(MFLAGS) $^ -o $@

polymorphichandler.o: polymorphichandler.c
	$(CC) $(CFLAGS) $^ -o $@

bootloader.o: bootloader.asm template.asm.inc
	$(ASM) $(AFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@



# # compile level development - with debuging symbols intact

# ASM = nasm
# CC = gcc

# AFLAGS = -felf64 -g -F dwarf 
# CFLAGS = -c -Wall -O2 -g -m64  -falign-functions=16 

# KFLAGS = -no-pie -nostartfiles
# MFLAGS = -no-pie -r -nostdlib

# all: turbopolymorphic.o


# turbopolymorphic.o: polymorphicengine.o polymorphichandler.o bootloader.o
# 	$(CC) $(MFLAGS) $^ -o $@

# polymorphichandler.o: polymorphichandler.c
# 	$(CC) $(CFLAGS) $^ -o $@

# bootloader.o: bootloader.asm template.asm.inc
# 	$(ASM) $(AFLAGS) $< -o $@

# polymorphicengine.o: polymorphicengine.asm
# 	$(ASM) $(AFLAGS) $< -o $@
