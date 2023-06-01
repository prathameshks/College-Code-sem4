%macro print 2
    mov rax,1
    mov rdi,1
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro
section .data
msg db "ALP TO PRINT NUMBER"
msgl equ $-msg 

section .bss
dnumbuff resb 2

section .text
global _start
_start:
mov rax,0ch
print msg,msgl
call display

jmp exit

display:
mov rdi,dnumbuff
mov rcx,02

up2:
rol al,04
mov dl,al
and dl,0fh
add dl,30h
cmp dl,39h
jbe skip2
add dl,07h

skip2:
mov [rdi],dl
inc rdi
dec rcx
jnz up2
;loop up2

print dnumbuff,2
ret

exit:
mov rax,60
mov rdi,0
syscall