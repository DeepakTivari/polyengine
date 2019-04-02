
global morph_engine


section .data

section .text


morph_engine:
;create stack frame
push rbp
mov  rbp, rsp
sub  rsp, 0x28
push rbx
push r12
push r13
push r14
push r15

;save data of using registers
mov [rbp-0x28], rdi
mov [rbp-0x20], rsi
mov [rbp-0x18],	rdx
mov [rbp-0x10],	rcx



; do stuff here




xor rax,rax 
; this will ensure rax = 0 , means completed without error
pop r15
pop r14
pop r13
pop r12
pop rbx
mov rsp, rbp
pop rbp
ret