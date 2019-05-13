%include "template.asm.inc"
extern main
global _start

; Define variables in the data section
section .data
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

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
    DECRYPTOR_SECTION main, 100h
    ret

align 16
payload:
	mov eax,4            ; 'write' system call = 4
	mov ebx,1            ; file descriptor 1 = STDOUT
	mov ecx,hello        ; string to write
	mov edx,helloLen     ; length of string to write
	int 80h              ; call the kernel

	; Terminate program
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h              ; call the kernel

align 16
.end: