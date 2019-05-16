
extern getpagesize
extern mprotect
; memory protection permission

%define PROT_NONE  0x0
%define PROT_READ  0x1
%define PROT_WRITE 0x2
%define PROT_EXEC  0x4

; opcode for no operation
%define OP_NOP 0x90

; the size of the encrypt and decrypt function
%define FUNC_SIZE 0x100


