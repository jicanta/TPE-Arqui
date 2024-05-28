GLOBAL sys_time_asm
GLOBAL sys_read_asm
GLOBAL sys_write_asm
GLOBAL sys_registers_asm

EXTERN sys_time
EXTERN sys_peekRegisters
EXTERN sys_write
EXTERN sys_read

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

sys_write_asm:    ; en rdi:id, rsi:fd, rdx:buff, rcx: size 
        pushState
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
        call sys_write
        popState
        ret

sys_read_asm:    ; en rdi:id, rsi:fd, rdx:buff, rcx: size
        pushState
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
        call sys_read
        popState
        ret