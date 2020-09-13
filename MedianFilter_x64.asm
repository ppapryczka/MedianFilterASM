;   uint64_t MedianFilter_x64(uint8_t *inputFileMemory, uint8_t *outputFileMemory, uint64_t startingAddressOfData, uint64_t width, uint64_t height, uint64_t padding);
;   int height = r8
;   int width  = rcx
;   int offset = rdx
;   char *outMemory = rsi
;   char *inMemory = rdi
;   int padding = r9

section .data
array db 0, 0, 0, 0, 0, 0, 0, 0, 0

section .text
global  median_filter_x64

median_filter_x64:

; prolog:
    push rbp
    push r12
    push r13
    push r14
    push r15
    push rbx
    mov rbp, rsp
    sub rsp, 4

; copy header:
    mov r12, r9
    mov [rbp-4], r8
    xor r10, r10 

cpheader:
    mov r9b, [rdi]
    mov [rsi],r9b
    inc rdi    
    inc rsi
    inc r10
    cmp r10, rdx
    jne cpheader 
    
; move variables    
    lea rcx, [rcx +rcx*2]
    mov rdx, rcx
    add rdx, r12
    xor rax, rax
    inc rax
    mov r13, rax
    mov r14, rax
    mov r15, rdx
    not r15
    inc r15
    
; Variables:
;    [rbp-4] = file height
;    rcx = number of bytes in row without padding 
;    rdx = number of bytes in row with padding
;    rsi = uint8_t *outMemory
;    rdi = uint8_t *inMemory 
;    r12 = padding
;    r13 = current row in file
;    r14 = current column in file
;    r15 = - number of bytes in row with padding
;    free registers r8, r9, r10, r11, rax, rbx 
    
; Main loop:

begin:
    cmp r13, 1
    je first_row
    cmp r13, [rbp-4]
    je last_row

middle_row:
    cmp r14, 3
    jle first_n
    mov r9, rcx
    sub r9, 3
    cmp r14, r9
    jg last_n

n_n:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+3]
    mov [r9], bl
    inc r9     
    mov bl, byte[rdi-3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx-3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx+3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15]
    mov [r9], bl
    inc r9 
    mov bl, byte[rdi+r15-3]
    mov [r9], bl
    inc r9 
    mov bl, byte[rdi+r15+3]
    mov [r9], bl

; sort begin:
sort_begin:
    mov r9, array
    mov rbx, r9
    xor rax, rax
    xor r10, r10
    xor r11, r11
    jmp loop

sort:
    inc r9 
    inc al
    cmp al, 5
    jge  after_sort
    mov rbx, r9
    mov r11b, al

loop:
    cmp r11b, 8
    jge sort
    inc rbx
    inc r11b
    mov r8b, [r9]
    mov r10b, [rbx]
    cmp r10b, r8b
    jnb loop

change: 
    mov [rbx], r8b
    mov [r9], r10b
    jmp loop
; sort end

first_n:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx+3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15+3]
    mov [r9], bl
    jmp sort_begin

last_n:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi-3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx-3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15-3]
    mov [r9], bl
    jmp sort_begin

first_row:
    cmp r14, 3
    jle first_first
    mov r9, rcx
    sub r9, 3
    cmp r14, r9
    jg last_first

n_first:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi-3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx+3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx-3]
    mov [r9], bl
    jmp sort_begin

first_first:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx+3]
    mov [r9], bl
    jmp sort_begin

last_first:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, [rdi-3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+rdx]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, [rdi+rdx-3]
    mov [r9], bl
    jmp sort_begin


last_row:
    cmp r14, 3
    jle first_last
    mov r9, rcx
    sub r9, 3
    cmp r14, r9
    jg last_last

n_last:
    mov r9, array    
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi-3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15-3]
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15+3]
    mov [r9], bl
    jmp sort_begin

first_last:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15+3]
    mov [r9], bl
    jmp sort_begin

last_last:
    mov r9, array
    mov bl, byte[rdi]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi-3]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15]
    mov [r9], bl
    inc r9
    mov [r9], bl
    inc r9
    mov bl, byte[rdi+r15-3]
    mov [r9], bl
    jmp sort_begin

after_sort:
    dec r9 
    mov bl, [r9]
    mov [rsi], bl
    inc rdi
    inc rsi
    inc r14
    cmp r14, rcx
    jle begin
    

before_padding:
    cmp r12, 0
    je after_padding
    xor r10, r10
    xor rax, rax

padding_add:
    mov [rsi], al
    inc rsi
    inc rdi
    inc r10
    cmp r10, r12
    je after_padding

    mov [rsi], al
    inc rsi
    inc rdi
    inc r10
    cmp r10, r12
    je after_padding

    mov [rsi], al
    inc rsi
    inc rdi

after_padding:
    inc r13
    cmp r13, [rbp-4]
    jg end
    mov r14, 1
    jmp begin


end:
    mov rsp, rbp
    pop rbx
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    ret
