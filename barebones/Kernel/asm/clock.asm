GLOBAL get_minutes
GLOBAL get_seconds
GLOBAL get_hours

section .text

set_rtc:        mov al, 0x0B
    		out 70h, al
    		in al, 71h
    		or al, 4
    		out 71h, al
		ret

get_seconds:
		call set_rtc
		cli
		mov al, 0
		out 70h, al
		in al, 71h
		sti
                ret

get_minutes:
		call set_rtc
		cli
		mov al, 2
		out 70h, al
                in al, 71h
		sti
                ret

get_hours:
		call set_rtc     
		cli
		mov al, 4
		out 70h, al
		in al, 71h
		sti
		ret
