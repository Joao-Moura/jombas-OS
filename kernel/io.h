#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/* outb:
 * Manda um pedaço de data para uma porta I/O.
 * Funcao definida no arquivo io.s
 *
 * @param port Porta I/O para mandar a data [16 bits]
 * @param data Porcao de data [8 bits]
 */
void outb (unsigned short port, unsigned char data);

#endif
