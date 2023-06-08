%macro print 2
    mov rax,1
    mov rdi,1
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro

%macro read 2
    mov rax,0
    mov rdi,0
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro

%macro fopen 1
    mov rax,2
    mov rdi,%1
    mov rsi,2
    mov rdx,0777o
    syscall
%endmacro

%macro fread 3
    mov rax,0
    mov rdi,%1
    mov rsi,%2
    mov rdx,%3
    syscall
%endmacro

%macro fwrite 3
    mov rax,1
    mov rdi,%1
    mov rsi,%2
    mov rdx,%3
    syscall
%endmacro

%macro fclose 1
    mov rax,3
    mov rdi,%1
    syscall
%endmacro

%macro exit 0
    mov rax,60
    mov rdi,0
    syscall
%endmacro
