# # compile level deployement - this removes all debugging symobls

ASM = nasm

GCC = g++
CC = gcc

AFLAGS = -felf64  

CFLAGS = -c  -Wall 

LFLAGS = -no-pie 
KFLAGS = -no-pie -nostartfiles -m64 -falign-functions=16 
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


# compile level development - with debuging symbols intact

# ASM = nasm

# GCC = g++
# CC = gcc

# AFLAGS = -felf64 -g -F dwarf 

# CFLAGS = -c  -Wall -O2 -g

# LFLAGS = -no-pie 
# KFLAGS = -no-pie -nostartfiles -m64 -g -falign-functions=16
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