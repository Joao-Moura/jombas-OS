global outb			; tornar visível para outros arquivos a label
global inb

section .text

; outb - manda 1 byte para a porta I/O
; importante seguir o cdecl
outb:
    mov al, [esp + 8]		; manda o valor para o lower do registrador a
    mov dx, [esp + 4]		; manda para o registrador dx a porta I/O usada
    out dx, al			; manda o valor do registrador a para a porta I/O do registrador dx
    ret

; inb - retorna 1 byte de uma porta I/O
inb:
    mov dx, [esp + 4]		; manda para o registrador dx a porta I/O usada
    in al, dx			; le o conteudo (1 byte) do registrador dx e manda para al
    ret
