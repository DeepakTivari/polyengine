

extern getpagesize
extern mprotect

%define PROT_NONE  0x0
%define PROT_READ  0x1
%define PROT_WRITE 0x2
%define PROT_EXEC  0x4

; opcode for no operation
%define OP_NOP 0x90

; the size of the encrypt and decrypt function
%define FUNC_SIZE 0x10


; this function will take in 2 arguments
%macro DECRYPTOR_SECTION 2
;create stack frame
push rbp
mov  rbp, rsp
sub  rsp, 0x18
push rbx
push r12
push r13
push r14
push r15



mov [rbp-0x18], rdi ; rdi is _START_ of section to decrypt
mov [rbp-0x10], rsi ; rsi is _SIZE_ of section to encrypt 


call getpagesize
mov rcx, rax
sub rcx, 0x1
not rcx
mov rdi, rdi
mov r10, rdi
and rdi, rcx
mov r12, rdi
mov r13, rsi 
lea rsi, [rdi+rsi]      ;rsi = end
sub r10, rdi
add rsi, r10
sub rsi,rdi      ;rsi = end - aligned_start = length

mov rdx, (PROT_READ|PROT_WRITE|PROT_EXEC)
call mprotect


mov rsi, [rbp-0x18]
mov rdi, rsi
add rdi, [rbp-0x10]
; rdi is full address of decryption end

.decryption_loop:
	; load first 16h memory
	mov eax, [rsi]
	mov ebx, [rsi+0x4]
	mov ecx, [rsi+0x8]
	mov edx, [rsi+0xC]

.decryption_function:
	times FUNC_SIZE db OP_NOP
	mov [rsi], eax
	mov [rsi+0x4], ebx
	mov [rsi+0x8], ecx
	mov [rsi+0xC], edx
	add rsi, 0x10
	; add 10h to rsi, fast forwards rsi to decrypt next 16bytes
	cmp rsi, rdi
	;compare if rsi = rdi, signalling end of decryption
	jne .decryption_loop


; protect memory
mov rdi, r12
mov rsi, r13
mov edx, (PROT_READ|PROT_WRITE)
call mprotect





xor rax,rax 
; this will ensure rax = 0 , means completed without error
pop r15
pop r14
pop r13
pop r12
pop rbx
mov rsp, rbp
pop rbp
%endmacro

