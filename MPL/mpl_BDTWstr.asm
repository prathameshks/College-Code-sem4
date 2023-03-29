%macro print 2
mov rax,1
mov rdi,1
mov rsi,%1
mov rdx,%2
syscall
%endmacro


section .data 

msg db "ALP to perform BDT without Using String Related Instructions",10
msgl equ $-msg

m1 db "Source Block Before Transfer :"
m1l equ $-m1

m2 db "Source Block After Transfer :"
m2l equ $-m2

space db " "
endl db 10
cnt equ 5

srcblk db 10h,20h,30h,40h,50h
dstblk db 00,00,00,00,00

section .bss  
ans resb 2


section .text
    global _start
    _start:
    print msg,msgl
    print m1,m1l

    mov rsi,srcblk
    call display

    print endl,1

    print m2,m2l
    mov rsi,srcblk
    mov rdi,dstblk

    mov rcx,cnt

    cld 
    rep movsb

    mov rsi,dstblk
    call display

    print endl,1

    exit:
    mov rax,60
    mov rdi,0
    syscall


    display:
    mov rbp,cnt
    up:
    mov al,[rsi]
    push rsi
    call display1
    print space,1
    pop rsi
    inc rsi
    dec rbp
    jnz up
    ret

    display1:
    mov rdi,ans
    mov rcx,02
    up1:
    rol al,4
    mov dl,al
    and dl,0fh
    add dl,30h
    cmp dl,39h
    jbe display2
    add dl,07h

    display2:
    mov [rdi],dl
    inc rdi
    loop up1
    print ans,02
    ret




;nasm -f elf64 mpl_BDTWstr.asm;ld -o a mpl_BDTW.o; ./a