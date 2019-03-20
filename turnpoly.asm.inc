extern getpagesize
extern mprotect

%macro DECRYPTION 2
push r12
push r13

call getpagesize
mov rcx, rax

pop r13
pop r12
%endmacro