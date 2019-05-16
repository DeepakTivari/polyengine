%include "include.asm.inc"
global decrypt_engine
global decrypt_engine.decryption_function
section .data
section .text



decrypt_engine:
;create stack frame
push rbp
mov  rbp, rsp
sub  rsp, 0x30
push rbx
push r12
push r13
push r14
push r15


.decryption_function:

; // code goes here


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