extern getpagesize
extern mprotect

%macro DECRYPTOR_SECTION 2
push r12
push r13

call getpagesize
mov rcx, rax

pop r12
pop r13
%endmacro