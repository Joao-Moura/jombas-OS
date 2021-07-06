#include "io.h"

/* Portas I/O */
/* Todas as portas sao calculadas relativamente de acordo com a porta de data.
 * E todas as portas seriais (COM1, COM2, COM3 e COM4), possuem
 * a mesma ordem, so que comecam em lugares diferentes
 */
#define SERIAL_COM1_BASE		0x3F8
#define SERIAL_DATA_PORT(base)		(base)
#define SERIAL_FIFO_COMMAND_PORT(base)	(base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)	(base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)	(base + 4)
#define SERIAL_LINE_STATUS_PORT(base)	(base + 5)

/* Comandos das portas I/O */
/* SERIAL_LINE_ENABLE_DLAB:
 * Fala pra porta serial que serao mandados os 8 primeiros bits de data,
 * e depois os 8 ultimos bits
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80
/* baud rate de 115200 / 3 = 38400 */
#define BAUD_RATE_DIVISOR	0x03

/* serial_configure_baud_rate:
 * Setta a velocidade de data enviada. A velocidade padrao e 115200 bits/s.
 * O argumento tem que ser um divisor da velocidade
 *
 * @param com	  Porta COM para configurar [16 bits]
 * @param divisor O divisor [16 bits]
 */
void serial_configure_baud_rate (unsigned short com, unsigned short divisor) {
    outb(SERIAL_DATA_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) * 0x00FF);
}

/* serial_configure_line:
 * Configuracao da line de uma porta serial.
 * Bit:      | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Conteudo: | d | b | prty  | s | dl  |
 *
 * nome | desc
 * -----+------
 * dl   | data length
 * sp   | stop bits, 0 = 1, 1 = 1.5 or 2
 * p    | parity bits (quantidade)
 * bc   | break control, 0 = disabled, 1 = enabled
 * dlab | dlab, 0 = disabled, 1 = enabled
 *
 * @param com	Porta COM para configurar [16 bits]
 */
void serial_configure_line (unsigned short com) {
    /* 0x03 [@osdev:serial]:
     * Representa 8 bits de data, com 1 bit de parada, bits de paridade (sem paridade),
     * DLAB e breack control desabilitados
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/* serial_configure_buffer:
 * Configuracao do buffer de uma porta serial. Importante lembrar que age com um fila (FIFO)
 * Bit:      | 7 6 | 5  | 4 | 3   | 2   | 1   | 0  |
 * Conteudo: | lvl | bs | r | dma | clt | clr | on |
 *
 * nome | desc
 * -----+------
 * on   | enable/disable buffer (FIFO)
 * clr	| limpa o buffer do reciever
 * clt	| limpa o buffer do transmitter
 * dma	| como a porta serial deve ser acessada
 * r	| reservado
 * bs	| tamanho do buffer (16 ou 64 bytes)
 * lvl	| quantos bytes sao armazenados no buffer
 *
 * @param com	Porta COM para configurar [16 bits]
 */
void serial_configure_buffer (unsigned short com) {
   /* 0xC7 ou 0x11000111:
    * Representa 14 bytes de buffer, com ele ativado e com transmitter e
    * reciever limpos
    */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/* serial_configure_modem:
 * Configuracao do modem de uma porta serial. Controle de flow de hardware
 * Bit:      | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Conteudo: | r | r | af | lb | ao2 | ao1 | rts | dtr |
 *
 * nome | desc
 * -----+------
 * dtr	| data terminal pronto
 * rts	| pronto para transmitir
 * ao1	| output 1
 * ao2	| output 2 (receber interrupcoes)
 * lb	| modo de loopback (debbugar as portas seriais)
 * af	| autoflow
 * r	| reservado
 * r	| reservado
 *
 * @param com	Porta COM para configurar [16 bits]
 */
void serial_configure_modem (unsigned short com) {
    /* 0x03:
     * Representa Ready to Transmit (RTS) e Data Terminal Ready (DTR)
     * e por ainda nao receber data (teclado) as interrupcoes estarao desligadas
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/* serial_init:
 * Configuracao inicial das portas seriais
 *
 * @param com	Porta COM para configurar [16 bits]
 */
void serial_init (unsigned short com) {
    serial_configure_baud_rate(com, BAUD_RATE_DIVISOR);
    serial_configure_line(com);
    serial_configure_buffer(com);
    serial_configure_modem(com);
}
