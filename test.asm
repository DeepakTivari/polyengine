extern main
section .data
; Code goes in the text section
section .text
	global _start

align 16
_start:             ; Global entry point

	call main
	mov rdi, rax
	mov eax, 1
	int 80h
