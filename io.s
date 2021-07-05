global outb			; tornar visível para outros arquivos a label

section .text

; outb - manda 1 byte (metade do comando) para a porta I/O
; importante seguir o cdecl
outb:
    mov al, [esp + 8]		; manda o valor para o lower do registrador a
    mov dx, [esp + 4]		; manda para o registrador dx a porta I/O usada
    out dx, al			; manda o valor do registrador a para a porta I/O do registrador dx
    ret

