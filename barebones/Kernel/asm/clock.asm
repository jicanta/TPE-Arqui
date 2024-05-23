GLOBAL get_minutes
GLOBAL get_seconds
GLOBAL get_hours
GLOBAL get_day
GLOBAL get_month
GLOBAL get_year

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
get_day:
		call set_rtc     
		cli
		mov al, 7
		out 70h, al
		in al, 71h
		sti
		ret
get_month:
		call set_rtc     
		cli
		mov al, 8
		out 70h, al
		in al, 71h
		sti
		ret
get_year:
		call set_rtc     
		cli
		mov al, 9
		out 70h, al
		in al, 71h
		sti
		ret
