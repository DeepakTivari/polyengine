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

AFLAGS = -felf64 -g -F dwarf 

CFLAGS = -c  -Wall -O2 -g

LFLAGS = -no-pie 
KFLAGS = -no-pie -nostartfiles -m64 -g -falign-functions=16 
all: virus polymake solopoly test
polymake: polyengine.o polymorphicengine.o
	$(GCC) $(LFLAGS) $^ -o $@
	
virus: infect.c polymorphic.c  polymorphicengine.o  virus.o  decryptionegnine.o
	$(CC) $(KFLAGS) $^ -o $@

virus.o: virus.asm
	$(ASM) $(AFLAGS) $< -o $@

polyengine.o: polymake.cpp
	$(GCC) $(CFLAGS) $< -o $@

decryptionegnine.o: decryptionengine.asm
	$(ASM) $(AFLAGS) $< -o $@

polymorphicengine.o: polymorphicengine.asm
	$(ASM) $(AFLAGS) $< -o $@




libobjdata.a: objsect.o objsym.o objcopy.o
	ar rs libobjdata.a objsect.o objsym.o objcopy.o
	mkdir -p lib
	cp -f libobjdata.a lib


XFLAGS = -no-pie  -L./lib
solopoly: polymorphic2.c polymorphicengine.o libobjdata.a -lobjdata -lbfd
	$(CC) $(LFLAGS) $^ -o $@
	


test: test.c test.o
	$(CC) $(KFLAGS) $^ -o $@
test.o: test.asm
	$(ASM) $(AFLAGS) $< -o $@

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