bits 32
global loader
extern kmain					; arquivo C externo

						; As seguintes varíaveis são necessárias para o GRUB carregar o kernel
MAGIC_NUMBER 	  equ 0x1BADB002		; número mágico para multiboot definido pelo GRUB
FLAGS		  equ 0x0			; multiboot flags
CHECKSUM	  equ -MAGIC_NUMBER		; MAGIC_NUMBER + FLAGS + CHECKSUM = 0
KERNEL_STACK_SIZE equ 4096			; Tamanho da stack em bytes

section .bss					; secção de data que não foi inicializada
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE			; reservar o espaço da stack quanto inicializar

section .text					; secção de texto (código)
align 4						; alinhamento de 4 bytes, headers padrão do multiboot!
    dd MAGIC_NUMBER				; dd define uma palavra dupla (4 bytes)
    dd FLAGS
    dd CHECKSUM

loader:						; label definida como entrypoint
    cli
    mov esp, kernel_stack + KERNEL_STACK_SIZE	; aponta o stack pointer para o início da stack
    push dword 3
    push dword 2
    push dword 1
    call kmain
    hlt
