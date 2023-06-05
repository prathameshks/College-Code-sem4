%macro universal 4
    mov rax,%1
    mov rdi,%2
    mov rsi,%3
    mov rdx,%4
    syscall
%endmacro

section .data
    m1 db "ASM Program to Find Largest Number from the given Numbers",10
    m1l equ $-m1

    m2 db "Largest number is "
    m2l equ $-m2

    m3 db "Elements of Array are ",10
    m3l equ $-m3

    arr db 11h,59h,33h,66h,44h

    new_line db 10
    space db " "

section .bss
    count resb 1
    num_buff resb 1 

section .text
global _start
_start:
    universal 1,1,m1,m1l
    universal 1,1,new_line,1
    universal 1,1,m3,m3l

    mov byte[count],05
    mov rsi,arr

next:
    mov rax,[rsi]
    push rsi
    call display
    universal 1,1,space,1
    pop rsi
    inc rsi
    dec byte[count]
    jnz next 

    universal 1,1,new_line,1
    universal 1,1,new_line,1
    universal 1,1,m2,m2l
    call findmax
    
    call display
    universal 1,1,new_line,1

    jmp exit


findmax:
    mov rsi,arr
    mov byte[count],6
    mov al,0h 

    up2:
        cmp al,[rsi]
        jg skip2
        mov al,[rsi]
    skip2:
        inc rsi
        dec byte[count]
        jnz up2
    ret


display:
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

;nasm -f elf64 mpl3_largestNumber.asm -o a.o ;ld a.o  -o a ;./a