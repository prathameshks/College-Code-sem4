%macro universal 4
    mov rax,%1
    mov rdi,%2
    mov rsi,%3
    mov rdx,%4
    syscall
%endmacro

section .data
    m1 db "ASM Program for Arithematic Operations Using Switch Case",10
    m1l equ $-m1

    m2 db "Enter choice of Operation(+,-,*,/):"
    m2l equ $-m2

    m3 db "Enter First Number: "
    m3l equ $-m3

    m4 db "Enter Second Number: "
    m4l equ $-m4

    m5 db "Invalid Operation",10
    m5l equ $-m5

    m6 db "Result is: "
    m6l equ $-m6

    new_line db 10

section .bss
    choice resb 1
    n1 resq 1
    n2 resq 1
    temp resq 1
    res resq 1
    num_buff resd 1

section .text
global _start
_start:
    universal 1,1,m1,m1l

    universal 1,1,m2,m2l
    universal 1,1,m2,m2l
    universal 0,0,choice,2

case1:
    cmp byte[choice],'+'
    jne case2
    call add_fun
    jmp end
case2:
    cmp byte[choice],'-'
    jne case3
    call sub_fun
    jmp end
case3:
    cmp byte[choice],'*'
    jne case4
    call mul_fun
    jmp end
case4:
    cmp byte[choice],'/'
    jne casedefault
    call div_fun
    jmp end
casedefault:
    universal 1,1,m5,m5l
    jmp exit
end:


    jmp exit

add_fun:
    universal 1,1,m3,m3l
    universal 0,0,temp,17
    universal 1,1,temp,17
    mov qword[res],0
    call ascii2hex

    universal 1,1,m4,m4l
    universal 0,0,temp,17
    universal 1,1,temp,17
    call ascii2hex
    add qword[res],rbx

    universal 1,1,m6,m6l
    mov rbx,[res]
    call hex2ascii
    universal 1,1,new_line,1
    ret

add_fun2:
    universal 1,1,m3,m3l
    universal 0,0,temp,17
    universal 1,1,temp,17
    mov qword[res],0
    call ascii2hex
    add qword[res],rbx
    universal 1,1,rbx,16

    universal 1,1,m4,m4l
    universal 0,0,temp,17
    universal 1,1,temp,17
    call ascii2hex
    add qword[res],rbx


    universal 1,1,m6,m6l
    mov rbx,[res]
    call hex2ascii
    universal 1,1,new_line,1
    ret

sub_fun:

    ret

mul_fun:

    ret

div_fun:

    ret


display:
    mov rdi,num_buff
    mov rcx,8

    up1:
        rol eax,04
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

    universal 1,1,num_buff,8
    ret


ascii2hex:
    mov rsi,temp
    xor rbx,rbx
    mov rcx,16
    mov al,0
    up2:
        rol rbx,04
        mov al,[rsi]
        cmp al,39h
        jbe skip2
        sub al,07h

    skip2:
        sub al,30h
        add bl,al
        inc rsi
        loop up2

    ret

hex2ascii:
    mov rsi,res
    mov rcx,16
    up3:
        mov dl,bl
        and dl,0fh
        add dl,30h
        cmp dl,39h
        jbe skip3
        add dl,07h

    skip3:
        mov [rsi],dl
        inc rsi
        shr rbx,04
        loop up3

    universal 1,1,res,16
    ret

exit:
mov rax,60
mov rdi,0
syscall

;nasm -f elf64 mpl4_arithematic_using_switchcase.asm -o a.o ;ld a.o  -o a ;./a
 