ENTRY(loader)			/* nome da label de entrada */

SECTIONS {
    . = 0x00100000;		/* o código deve ser carregado em 1MB */

    .text ALIGN (0x1000) : 	/* alinhado em 4KB */
    {
	*(.text)		/* todas as secções de todos os arquivos */
    }

    .rodata ALIGN (0x1000) :
    {
	*(.rodata*)		/* todas as secções read-only data de todos os arquivos */
    }

    .data ALIGN (0x1000) :
    {
        *(.data)      	       /* todas as secções de data de todos os arquivos */
    }

    .bss ALIGN (0x1000) :
    {
        *(COMMON)            	/* todas as secções COMMON de todos os arquivos */
        *(.bss)             	/* todas as secções bss de todos os arquivos */
    }
}
