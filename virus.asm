%include "template.asm.inc"
extern main

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

	; create space to save state in rsp
	push rbp
	mov  rbp, rsp
	sub  rsp, 0x18

	;save data initial program state
	mov [rbp-0x18],	rdi 
	mov [rbp-0x10],	rsi

    call decrypt

	; reload the initial program, state
	mov rdi, [rbp-0x18]
	mov rsi, [rbp-0x10]
	mov rsp, rbx

	; DO NOT TOUCH CALLING MAIN
	xor rbp, rbp
	pop rdi
	mov rsi, rsp
	lea rdx, [rsp+rdi+8*8]
	push rdi
	call main
	
	mov rdi, rax
	mov eax, 1
	int 80h



; _start:   
    ; call decrypt
    ; call payload
    ; ret

decrypt:
	; there is automatic calculation happening inside DECRYPTOR_SECTION function which is (_start-main) == xxxh worth of memory that will be encrypted/decrypted
    DECRYPTOR_SECTION main, _start
    ret