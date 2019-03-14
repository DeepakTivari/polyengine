
%include "turnpoly.inc"

; Define variables in the data section
SECTION .DATA
	hello:     db 'Hello world!',10
	helloLen:  equ $-hello

; Code goes in the text section
SECTION .TEXT
	GLOBAL _start 

main:
    call _decrypt
    call _start
    ret

_decrypt:
    DECRYPTOR_SECTION _start, _start.end-_start
    ret

align 16
_start:
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