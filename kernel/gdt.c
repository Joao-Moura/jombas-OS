#include "gdt.h"

/* gdt_ptr:
 * Struct contendo informacoes da tabela gdt
 *
 * @field address Endereco da primeira entrada gdt [32 bits]
 * @field size	  Tamanho da tabela em bytes [16 bits]
 */
struct gdt_ptr {
    unsigned int address;
    unsigned short size;
} __attribute((packed));
typedef struct gdt_ptr ptr;
