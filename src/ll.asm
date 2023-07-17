
; low level

format ELF
include 'win32a.inc'
;section '.data'
	;public CON
	;CON dd ?
	;public _HEAP
	;_HEAP dd ?
section '.text'
	extrn initw
	extrn main
	public _start
		_start:
			call  initw
			call  main
			ret
