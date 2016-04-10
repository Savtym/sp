Data1 Segment
	myByte		db 00011h
	myWord		dw 505ah
	myDouble	dd 17930h
	myString 	db "Hello world!" ;dasdsa
Data1 ends

code segment
	len db 10h
begin:
	sti
	priv equ 2h
	if priv
		inc es:myByte[ecx + eax * 2]
	else
		dec eax
	endif
		and eax, ebx
	dec ebx
	or ebx, len[ecx + edi * 4]
	cmp myDouble[ecx + eax * 8], ebx
	jnz m1
	add myByte[ecx + eax * 2], 4h
m1:
	mov eax, 4c00h 
code ends
end 