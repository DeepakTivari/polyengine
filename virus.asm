%include "template.asm.inc"
extern printVal
; Define variables in the data section
section .data
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

; Code goes in the text section
section .text
	global main

main:
    call decrypt
    call payload
    ret

decrypt:
    DECRYPTOR_SECTION payload, payload.end-payload
    ret

align 16
payload:
	mov eax,4            ; 'write' system call = 4
	mov ebx,1            ; file descriptor 1 = STDOUT
	mov ecx,hello        ; string to write
	mov edx,helloLen     ; length of string to write
	int 80h              ; call the kernel

	; mov qword rdi, 0xabcd  ;in case of x86_64 params are passed in RDI,
						;RSI, RDX, RCX, R8, R9, stack, in that order
	; Terminate program
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h              ; call the kernel

align 16
.end: