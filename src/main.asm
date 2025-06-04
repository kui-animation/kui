%define FILE_OPEN 0644o

section .bss
    file resb 16
    mes resb 32

section .text
global _start

_start:

    mov rax, 0
    mov rdi, 0
    mov rsi, file
    mov rdx, 16
    syscall

    mov byte [file+rax-1], 0x0

    mov rax, 2
    mov rdi, file
    mov rsi, 1 | 64
    mov rdx, FILE_OPEN
    syscall
    push rax

    ;---------------;
    ; print to file ;
    ;---------------;

    mov rax, 0
    mov rdi, 0
    mov rsi, mes
    mov rdx, 32
    syscall

    pop rdi
    push rdi
    mov rdx, rax
    mov rax, 1
    mov rsi, mes
    syscall

    ;---------------;
    ;  end program  ;
    ;---------------;

    mov rax, 3
    pop rdi
    syscall
    
    mov rax, 60
    mov rdi, 0
    syscall

