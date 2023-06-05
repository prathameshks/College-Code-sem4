%macro universal 4
    mov rax,%1
    mov rdi,%2
    mov rsi,%3
    mov rdx,%4
    syscall
%endmacro

section .data
    m1 db "ASM Program for Calculate and Displaying Lenght of Input String",10
    m1l equ $-m1

    m2 db "Enter string:"
    m2l equ $-m2

    m3 db "String Entered is ",10
    m3l equ $-m3

    m4 db "Length of Entered string is ",10
    m4l equ $-m4

    new_line db 10

section .bss
    buff resb 250
    size equ $-buff

    count resb 1
    num_buff resb 1

section .text
global _start
_start:
    universal 1,1,m1,m1l

    universal 1,1,m2,m2l
    universal 0,0,buff,size
    mov [count],rax

    universal 1,1,new_line,1
    universal 1,1,m3,m3l
    universal 1,1,buff,[count]

    universal 1,1,new_line,1
    universal 1,1,m4,m4l

    call display
    universal 1,1,new_line,1
    
    jmp exit

display:
    mov rax,[count]
    dec rax
    mov rdi,num_buff

    mov rcx,2

    up1:
        rol al,04
        mov dl,al
        and dl,0fh
        add dl,30h
        cmp dl,39h
        jbe skip1
        add dl,07h

    skip1:
        mov [rdi],dl
        inc rdi
        loop up1

    universal 1,1,num_buff,2
    ret

exit:
mov rax,60
mov rdi,0
syscall

;nasm -f elf64 mpl2_lengthofstring.asm -o a.o ;ld a.o  -o a ;./a