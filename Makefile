# Compile
nasm -f elf64 hello.asm -o hello.o

# Link
ld hello.o -o hello

# Run
./hello