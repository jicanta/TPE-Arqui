GLOBAL inb0x60;

; function to read from port 0x60 (keyboard)
inb0x60:					; returns uint32_t
	mov rax, 0
	in al, 0x60				; port 0x60 contains the key pressed
	ret
