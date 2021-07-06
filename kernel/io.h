#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/* outb:
 * Manda um pedaço de data para uma porta I/O.
 *
 * @param port Porta I/O para mandar a data [16 bits]
 * @param data Porcao de data [8 bits]
 */
void outb (unsigned short port, unsigned char data);

/* inb:
 * Le o valor de um byte de uma porta I/O.
 *
 * @param port Porta I/O para ser lida [16 bits]
 * @return     O valor do byte lido [8 bits]
 */
unsigned char inb (unsigned short port);

#endif
