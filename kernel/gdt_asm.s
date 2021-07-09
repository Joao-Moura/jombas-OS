global gdt_load_and_set

SEGSEL_KERNEL_CS equ 0x08			; kernel code segment
SEGSEL_KERNEL_DS equ 0x10			; kernel data segment

section .text
gdt_load_and_set:				; carrega a GDT na CPU e os respectivos segmentos
    mov eax, [esp+4]
    lgdt [eax]
    jmp SEGSEL_KERNEL_CS:.reload_segments	; "far jump" para carregar o segmento de código

.reload_segments:				; função que irá carregar os outros segmentos
    mov ax, SEGSEL_KERNEL_DS
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    ret
