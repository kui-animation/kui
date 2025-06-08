%define FILE_NUM 0644o
%define CREAT_F 64
%define WRITE_F 1
%define READ_F 0
%define LINE_LEN 6
%define H_RES 16
%define W_RES 32
%define RES 544

%define SYS_SLEEP 35
%define SYS_WRITE 1
%define SYS_READ 0
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define SYS_RMFILE 87
%define SYS_EXIT 60
%define STDIN 0
%define STDOUT 1


section .data                           ; defining constants
    sleep_time dq 0, 250000000
    mov_cur db 0x1b, "[1A"
    lode db "do you what to lode a file?", 0xA
    lode_len equ $ - lode
    what_file db "what is the file name?", 0xA
    what_file_len equ $ - what_file

section .bss                            ; defining variables
    file_prt resb 8
    mes resb LINE_LEN
    lode_file resb 2
    buf resb RES+1
    file resb 16

section .text
global _start

_start:

    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, lode
    mov rdx, lode_len
    syscall

                                        ; get input 
    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, lode_file
    mov rdx, 2
    syscall
                                        ; check if file exist

    cmp byte[lode_file], 'y'
    je get_file_name

    cmp byte[lode_file], 'n'
    jne skip_removeing_file

                                        ; set file name
    mov byte[file], 0x41
    mov byte[file+1], 0x0

                                        ; open a file
    mov rax, SYS_OPEN
    mov rdi, file
    mov rsi, WRITE_F | CREAT_F          ; creat now file in write mode
    mov rdx, FILE_NUM
    syscall
    mov [file_prt], rax                 ; set file pointer to the fd



read_comand:

                                        ; read input in mes
    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, mes
    mov rdx, LINE_LEN
    syscall

    cmp rax, LINE_LEN
    jl start_executing_program

                                        ; comper if mes is end
    cmp byte[mes], 'e'
    jne write_comand
    cmp byte[mes+1], 'n'
    jne write_comand
    cmp byte[mes+2], 'd'
    jne write_comand
    cmp byte[mes+3], 0xA
    je start_executing_program          ; if is end go start_exe

write_comand:

                                        ; write to the tmp file 
    mov rdi, [file_prt]
    mov rdx, rax
    mov rax, SYS_WRITE
    mov rsi, mes
    syscall

    jmp read_comand                     ; go to start of loop


get_file_name:
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, what_file
    mov rdx, what_file_len
    syscall

    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, file
    mov rdx, 16
    syscall
    
    mov byte[file+rax-1], 0x0
    jmp open_file

start_executing_program:
                                        ; close file
    mov rax, SYS_CLOSE
    mov rdi, [file_prt]
    syscall 
    
open_file:
                                        ; open it in read mode
    mov rax, SYS_OPEN
    mov rdi, file
    mov rsi, READ_F
    mov rdx, FILE_NUM
    syscall

    mov [file_prt], rax                 ; set file pointer to fd

executing_program:
                                        ; read char in file
    mov rax, SYS_READ
    mov rdi, [file_prt]
    mov rsi, mes
    mov rdx, LINE_LEN
    syscall

                                        ; if end off file go to end_program
    cmp rax, LINE_LEN
    jl end_program

    cmp byte[mes], 'v'
    jne .next_str1
    cmp byte[mes+1], 'o'
    je VOXEL

.next_str1:
    cmp byte[mes], 's'
    jne .next_str2
    cmp byte[mes+1], 'b'
    jne .next_str2
    cmp byte[mes+2], 'u'
    jne .next_str2
    cmp byte[mes+3], 'f'
    je SBUF

.next_str2:


    cmp byte[mes], 's'
    jne .next_str3
    cmp byte[mes+1], 'l'
    jne .next_str3
    cmp byte[mes+2], 'e'
    jne .next_str3
    cmp byte[mes+3], 'e'
    jne .next_str3
    cmp byte[mes+4], 'p'
    je SLEEP

.next_str3:
    cmp byte[mes], 'p'
    jne .next_str4
    cmp byte[mes+1], 'r'
    jne .next_str4
    cmp byte[mes+2], 'i'
    jne .next_str4
    cmp byte[mes+3], 'n'
    jne .next_str4
    cmp byte[mes+4], 't'
    je print

.next_str4:
    jmp executing_program

print:
    
                                        ; write char to the terminal
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, buf
    mov rdx, RES
    syscall

    call MOVEUP

    jmp executing_program


end_program:

                                        ; close file 
    mov rax, SYS_CLOSE
    mov rdi, [file_prt]
    syscall

    cmp byte[lode_file], 'y'
    je skip_removeing_file
                                        ; remove file
    mov rax, SYS_RMFILE
    mov rdi, file
    syscall

skip_removeing_file:
                                        ; end program 
    mov rax, SYS_EXIT
    mov rdi, 0
    syscall


;-----------;
; FUNCTIONS ;
;-----------;


SBUF:
    mov al, byte[mes+4]
    mov rbx, 0
.loop1:
    
    mov byte[buf+rbx], al

    inc rbx
    cmp rbx, RES
    jne .loop1

    call FIXBUF

    jmp executing_program


SLEEP:

    mov rax, SYS_SLEEP
    mov rdi, sleep_time
    mov rsi, 0
    syscall

    jmp executing_program


VOXEL:

    movzx eax, byte[mes+3]
    movzx ebx, byte[mes+2]

    sub eax, 65
    sub ebx, 64

    imul ecx, eax, W_RES
    add ecx, ebx

    mov al, byte[mes+4]
    mov byte[buf+ecx], al

    jmp executing_program


MOVEUP:
    mov rbx, 0
.loop1:
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, mov_cur
    mov rdx, 4
    syscall

    inc rbx
    cmp rbx, H_RES+1
    jne .loop1

    ret


FIXBUF:
    mov rbx, 0

.loop1:
    mov rax, rbx
    imul rax, W_RES
    mov byte[buf+rax], 0xA

    inc rbx
    cmp rbx, H_RES+1
    jne .loop1

    mov byte[buf+RES], 0x0
    ret
