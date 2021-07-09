#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

/* gdt_load_and_set:
 * inicializa a tabela GDT e seus segmentos
 *
 * @parm gdt Endereco da tabela GTD para ser inicializada [32 bits]
 */
void gtd_load_and_set (unsigned int gdt);

#endif
