GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL irq00                ; timer tick interruption
GLOBAL irq01                ; keyboard interruptionn
GLOBAL exception00          ; exception 00 (division by zero)
GLOBAL exception06          ; exception 06 (invalid op code)
GLOBAL sys_call
GLOBAL registerSnapshot

EXTERN irqHandler           ; function in IRQs.c which handles interruption
EXTERN exceptionHandler     ; function in exceptions.c which handles exceptions
EXTERN syscallHandler		; function is syscalls.c which handles syscalls

EXTERN getRegisters

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

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqHandler                    ; calling irqHandler to process interruption

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionHandler             ; calling exceptionHandler to process interruption

	popState
	iretq
%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret

_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

registerSnapshot:
	push	rbp
	mov 	rbp, rsp
	mov [registers+0],  rax ;0
	mov [registers+8],  rbx ;1
	mov [registers+16], rcx ;2
	mov [registers+24], rdx ;3
	mov [registers+32], 	rsi ;4
	mov [registers+40], 	rdi ;5
	mov [registers+48], 	rbp ;6
	mov [registers+64], 	r8  ;8
	mov [registers+72], 	r9  ;9
	mov [registers+80], 	r10 ;10
	mov [registers+88], 	r11	;11
	mov [registers+96], 	r12 ;12
	mov [registers+104], 	r13 ;13
	mov [registers+112], 	r14 ;14
	mov [registers+120], 	r15 ;15


	mov rax, rsp
	add rax, 40
	mov [registers+56], rax ;7

	mov rax, [rsp]
	mov [registers+128], rax ;16

	mov rax, [rsp+8]
	mov [registers+136], rax ;17
	mov 	rax, registers
	mov 	rsp, rbp
	pop 	rbp
	ret

; timer tick
irq00:
	irqHandlerMaster 0

; keyboard
irq01:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

; division by zero exception
exception00:
	call registerSnapshot
	pushState
	mov rdi, 0
	mov rsi, registers
	call exceptionHandler
	popState
	iretq

; invalid op code exception
exception06:
	call registerSnapshot
	pushState
	mov rdi, 6
	mov rsi, registers
	call exceptionHandler
	popState
	iretq

sys_call:
	;pushState
	call syscallHandler

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	;popState
	iretq

haltcpu:
	cli
	hlt
	ret


SECTION .bss
	aux resq 1
	registers resq 18
 
