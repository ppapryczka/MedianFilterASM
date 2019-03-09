; uint32_t MedianFilter_x86(uint8_t *inputFileMemory, uint8_t *outputFileMemory, uint32_t startingAddressOfData, uint32_t width, uint32_t height);
;
;   uint32_t height = [ebp+24]
;   uint32_t width  = [ebp+20]
;   uint32_t startingAddressOfData = [ebp+16]
;   uint8_t *outputFileMemory = [ebp+12]
;   uint8_t *inputFileMemory = [ebp+8]

section .data
array db 0, 0, 0, 0, 0, 0, 0, 0, 0

section .text
global  MedianFilter_x86

MedianFilter_x86:

; prolog:
    push ebp
    mov	ebp, esp
    sub  esp, 12

; allocate memory for local variables:
;   - [ebp-4] = padding
;   - [ebp-8] = current raw in image 
;   - [ebp-12] = current column in raw

; copy header:
    mov edi, [ebp+8]
    mov esi, [ebp+12]
    xor ecx, ecx
    xor edx, edx

loop1:
    mov dl, [edi]
    mov [esi], dl
    inc edi
    inc esi
    inc ecx
    cmp ecx, [ebp+16]
    jne  loop1


; count paddingu
count:
    mov eax, [ebp+20] 
    ; quickly mul 3 :)
    lea eax, [eax + eax*2]
    mov [ebp+20], eax
    mov ebx, eax
    and ebx, 3
    cmp ebx, 0
    je padding
    mov eax, 4
    sub eax, ebx
    mov ebx, eax

padding:
    mov [ebp-4], ebx
    mov eax, [ebp+20]
    add eax, [ebp-4]
    mov [ebp+16], eax
    xor eax, eax
    mov eax, 1
    mov [ebp-12], eax
    mov [ebp-8], eax

; Zmienne uzywane:
;   - [ebp-4] = padding
;   - [ebp-8] = current raw in image
;   - [ebp-12] = current column in raw 
;   - [ebp+20] = number of bytes without padding
;   - [ebp+16] = ilosc bajtow w wierszu z paddingiem
;   - [ebp+24] = ilosc wierszy w pliku 
;   - esi = outMemory
;   - edi = inMemory

; Main loop:

begin:
    cmp dword [ebp-8], 1
    je  first_row
    mov eax, [ebp+24]
    cmp eax, [ebp-8]
    je  last_row

middle_row:
    mov eax, [ebp-12]
    cmp eax, 3
    jle first_n
    mov ecx, [ebp+20]
    sub ecx, 3
    cmp eax, ecx
    jg last_n

n_n:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax 
    mov bl, byte[edi+3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi-3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx-3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+3]
    mov [eax], bl
    inc eax

    mov edx, edi
    sub edx, ecx
    mov bl, byte[edx]
    mov [eax], bl
    inc eax 
    mov bl, byte[edx-3]
    mov [eax], bl
    inc eax 
    mov bl, byte[edx+3]
    mov [eax], bl

; sort:
sort_begin:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    mov eax, array
    mov ebx, eax
    jmp loop

sort:
    inc eax 
    inc cl
    cmp cl, 5
    jge after_sort
    mov ebx, eax
    mov ch, cl

loop:
    cmp ch, 8
    jge sort
    inc ebx
    inc ch
    mov dl, [eax]
    mov dh, [ebx]
    cmp dh, dl
    jb czendz
    jmp loop

czendz: 
    mov [ebx], dl
    mov [eax], dh
    jmp loop
; sort end


first_n:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+3]
    mov [eax], bl
    inc eax

    mov edx, edi
    sub edx, ecx
    mov bl, byte[edx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edx+3]
    mov [eax], bl
    jmp sort_begin

last_n:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi-3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx-3]
    mov [eax], bl
    inc eax

    mov edx, edi
    sub edx, ecx
    mov bl, byte[edx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edx-3]
    mov [eax], bl
    jmp sort_begin

first_row:
    mov eax, [ebp-12]
    cmp eax, 3
    jle first_first
    mov ecx, [ebp+20]
    sub ecx, 3
    cmp eax, ecx
    jg last_first

n_first:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi-3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx-3]
    mov [eax], bl
    jmp sort_begin

first_first:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    mov ecx, [ebp+16]
    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+3]
    mov [eax], bl
    jmp sort_begin

last_first:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi-3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx-3]
    mov [eax], bl
    jmp sort_begin

last_row:
    mov eax, [ebp-12]
    cmp eax, 3
    jle first_last
    mov ecx, [ebp+20]
    sub ecx, 3
    cmp eax, ecx
    jg last_last

n_last:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi-3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    not ecx
    inc ecx
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx-3]
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+3]
    mov [eax], bl
    jmp sort_begin

first_last:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    not ecx
    inc ecx
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+3]
    mov [eax], bl
    jmp sort_begin

last_last:
    mov eax, array
    xor ebx, ebx
    xor ecx, ecx
    mov ecx, [ebp+16]

    mov bl, byte[edi]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi-3]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    not ecx
    inc ecx
    mov bl, byte[edi+ecx]
    mov [eax], bl
    inc eax
    mov [eax], bl
    inc eax
    mov bl, byte[edi+ecx+-3]
    mov [eax], bl
    jmp sort_begin

after_sort:
    dec eax
    mov dl, [eax]
    mov [esi], dl
    inc edi
    inc esi
    mov eax, [ebp-12]
    inc eax
    mov [ebp-12], eax
    cmp eax, [ebp+20]
    jle begin

before_padding:
    cmp dword[ebp-4], 0
    je after_padding
    xor ecx, ecx
    xor eax, eax

padding_add:
    mov [esi], al
    inc esi
    inc edi
    inc ecx
    cmp ecx, [ebp-4]
    je after_padding

    mov [esi], al
    inc esi
    inc edi
    inc ecx
    cmp ecx, [ebp-4]
    je after_padding

    mov [esi], al
    inc esi
    inc edi

after_padding:
    mov eax, [ebp-8]
    inc eax
    cmp eax, [ebp+24]
    jg end
    mov [ebp-8], eax 
    mov eax, 1
    mov [ebp-12], eax
    jmp begin

end: 
    mov esp, ebp
    pop ebp
	ret
