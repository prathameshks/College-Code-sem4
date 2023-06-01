%macro print 2
	mov rax,1
	mov rdi,1
	mov rsi,%1
	mov rdx,%2
	syscall
%endmacro

%macro exit 0
	mov rax,60
	mov rdi,0
	syscall
%endmacro

section .data
	array db 11h,23h,66h,99h,16h,55h
	a_l equ $-array
	
	msg1 db "ALP For findig Largest Number from Array",10
	msg1_l equ $-msg1
	
	
	msg2 db "Largest Number from Array is",10
	msg2_l equ $-msg2
	
	
	space db " "
	
	newline db 10
	
section .bss
	cunt resb 1
	result resb 4

section .text
	global _start:
	_start:
	print msg1,msg1_l
	
	mov byte[cunt],6
	mov rsi,array
	
	next:
		mov al,[rsi]
		push rsi
	 	call display
	 	print space,1
	 	pop rsi
	 	inc rsi
		dec byte[cunt]
	 	jnz next
		
	
	print newline,1
	
	
	
	mov byte[cunt],06
	mov rsi,array
	mov al,0
		
	findmax:
		cmp al,[rsi]
		push rsi
		jg skip1
		mov al,[rsi]
		skip1:
		pop rsi
		inc rsi
		dec byte[cunt]
	 	jnz findmax
	
	
	call display
	
	
	exit
	
display:
	mov bl,al
	mov rdi,result
	mov cx,02
	up1:
		rol bl,04
		mov al,bl
		and al,0fh
		add al,30h
		cmp al,39
		jnb skip
		add al,07h
		skip:
			mov [rdi],al
		inc rdi
		dec cx
		jnz up1
	print result,02
	ret

; nasm -f elf64 mpl_finding_largest_no.asm ;ld -o out mpl_finding_largest_no.o ;./out 

