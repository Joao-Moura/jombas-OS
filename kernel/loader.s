bits 32
global loader
extern kmain					; arquivo C externo

						; As seguintes varíaveis são necessárias para o GRUB carregar o kernel
MAGIC_NUMBER 	  equ 0x1BADB002		; número mágico para multiboot definido pelo GRUB
FLAGS		  equ 0x0			; multiboot flags
CHECKSUM	  equ -MAGIC_NUMBER		; MAGIC_NUMBER + FLAGS + CHECKSUM = 0
KERNEL_STACK_SIZE equ 8192			; Tamanho da stack em bytes

section .bss					; secção de data que não foi inicializada
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE			; resb define uma byte NÃO inicializado (1 byte)

section .text					; secção de texto (código)
align 4						; alinhamento de 4 bytes, headers padrão do multiboot!
    dd MAGIC_NUMBER				; dd define uma palavra dupla inicializada (4 bytes)
    dd FLAGS
    dd CHECKSUM

loader:						; label definida como entrypoint
    cli						; sem interrupções, para evitar que CPU saia do estado de halt
    mov esp, kernel_stack + KERNEL_STACK_SIZE	; aponta o stack pointer para o final da stack (de cima para baixo)
    call kmain
    hlt						; CPU entra em estado de halt
