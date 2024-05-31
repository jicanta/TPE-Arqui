GLOBAL sys_time_front_asm
GLOBAL sys_registers_front_asm
GLOBAL sys_read_front_asm
GLOBAL sys_write_front_asm
GLOBAL sys_clean_front_asm
GLOBAL sys_getkeypressed_front_asm
GLOBAL sys_fillrect_front_asm
GLOBAL sys_write_at_front_asm
GLOBAL sys_write_color_front_asm
GLOBAL sys_write_color_at_front_asm
GLOBAL sys_sleep_front_asm
GLOBAL exception00_asm
GLOBAL exception06_asm
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

sys_time_front_asm:
        pushState
        mov rdi, 3
        int 80h
        popState
        ret

sys_registers_front_asm:
        pushState
        mov rdi, 4
        int 80h
        popState
        ret

sys_write_front_asm:
        pushState
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 2
        int 80h
        popState
        ret

sys_read_front_asm:
        pushState
        mov rcx, rdx
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 1
        int 80h
        popState
        ret

sys_clean_front_asm:
	pushState
	mov rdi, 5
	int 80h
	popState
	ret

sys_getkeypressed_front_asm:
	pushState
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 6
        int 80h
        popState
        ret

sys_fillrect_front_asm:
	pushState
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 7
        int 80h
        popState
        ret

sys_write_at_front_asm:
	pushState
	mov r8, rcx
        mov rcx, rdx
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 8
        int 80h
        popState
        ret

sys_write_color_front_asm:
sys_write_color_at_front_asm:
sys_sleep_front_asm:

exception00_asm:
        pushState
        int 00h
        popState
        ret
    
exception06_asm:
        pushState
        int 06h
        popState
        ret