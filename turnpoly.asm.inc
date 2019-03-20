extern getpagesize
extern mprotect

%macro DECRYPTION 2
push r12
push r13

pop r13
pop r12
%endmacro