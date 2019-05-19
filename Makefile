# # compile level deployement - this removes all debugging symobls

# ASM = nasm

# GCC = g++
# CC = gcc

# AFLAGS = -felf64  

# CFLAGS = -c  -Wall 

# LFLAGS = -no-pie 
# KFLAGS = -no-pie -nostartfiles -m64 -falign-functions=16 
# all: virus polymake

# polymake: polyengine.o polymorphicengine.o
# 	$(GCC) $(LFLAGS) $^ -o $@
	
# virus:  infect.c virus.o 
# 	$(CC) $(KFLAGS) $^ -o $@

# virus.o: virus.asm template.asm.inc
# 	$(ASM) $(AFLAGS) $< -o $@

# polyengine.o: polymake.cpp
# 	$(GCC) $(CFLAGS) $< -o $@

# polymorphicengine.o: polymorphicengine.asm
# 	$(ASM) $(AFLAGS) $< -o $@


# compile level development - with debuging symbols intact

ASM = nasm
GCC = g++
CC = gcc
LCC = ld
AFLAGS = -felf64 -g -F dwarf 

CFLAGS = -c -nostartfiles -Wall -O2 -g -nostdlib  -nodefaultlibs

LFLAGS = -no-pie 
KFLAGS = -no-pie -nostartfiles -m64 -g -falign-functions=16 
CKFLAGS = -no-pie -nostartfiles  -m64 -g -falign-functions=16 
MFLAGS = -no-pie -r -nostartfiles 
MCFLAGS = -no-pie -r -nostdlib
all: virus hello  polymorphic.o superpolymorphic.o


virus: infect.cpp superpolymorphic.o
	$(GCC) $(CKFLAGS) $^ -o $@

superpolymorphic.o: polymorphicengine.o virus.o polymorphicendgame_cpp.o
	$(GCC) $(MFLAGS) $^ -o $@


# virus: infect.c superpolymorphic.o
# 	$(CC) $(KFLAGS) $^ -o $@	


# superpolymorphic.o: polymorphicengine.o virus.o polymorphicendgame.o
# 	$(LCC) $(MFLAGS) $^ -o $@

polymorphicendgame_cpp.o: polymorphic.cpp
	$(GCC) $(CFLAGS) $^ -o $@

polymorphicendgame.o: polymorphic.c
	$(CC) $(CFLAGS) $^ -o $@

polymorphic.o: polymorphicengine.o virus.o
	$(LCC) $(MFLAGS) $^ -o $@

virus.o: virus.asm template.asm.inc
	$(ASM) $(AFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@


# hello: hello.c
# 	$(CC) $(LFLAGS) $^ -o $@
# test: test.c test.o
# 	$(CC) $(KFLAGS) $^ -o $@
# test.o: test.asm
# 	$(ASM) $(AFLAGS) $< -o $@


# # deploy level extreme deployment - this strips out all kind of information using the switch `-s` for gcc
# # In this mode objdump will not work with labels supplied as the labels now chnaged to placeholder
# ASM = nasm

# GCC = g++
# CC = gcc

# AFLAGS = -felf64  

# CFLAGS = -c  -Wall 

# LFLAGS = -no-pie -s
# KFLAGS = -no-pie -nostartfiles -m64 -falign-functions=16 -s
# all: virus polymake

# polymake: polyengine.o polymorphicengine.o
# 	$(GCC) $(LFLAGS) $^ -o $@
	
# virus:  infect.c virus.o 
# 	$(CC) $(KFLAGS) $^ -o $@

# virus.o: virus.asm template.asm.inc
# 	$(ASM) $(AFLAGS) $< -o $@

# polyengine.o: polymake.cpp
# 	$(GCC) $(CFLAGS) $< -o $@

# polymorphicengine.o: polymorphicengine.asm
# 	$(ASM) $(AFLAGS) $< -o $@