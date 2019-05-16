

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
%define FUNC_SIZE 0x20


; this function will take in 2 arguments
; the address of the virus.start and the size of (virus.end - virus.start)
%macro DECRYPTOR_SECTION 2
push rsp
push rbp
push rbx
push r12
push r13
push r14
push r15






pop r15
pop r14
pop r13
pop r12
pop rbx
pop rbp
pop rsp
%endmacro

