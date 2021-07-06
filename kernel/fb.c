#include "io.h"
#include "fb.h"

/* Inicio do framebuffer */
#define FB_MEMORY 0x000B8000

/* Tamanho do framebuffer */
#define FB_NUM_COLS 80
#define FB_NUM_ROWS 25

/* Portas I/O disponiveis */
#define FB_COMMAND_PORT	0x3D4
#define FB_DATA_PORT 	0x3D5

/* Commandos I/O disponiveis */
#define FB_HIGH_BYTE_COMMAND 	14
#define FB_LOW_BYTE_COMMAND 	15

/* Ao tratar o framebuffer como um pointeiro de char (16 bits)
 * e possivel a seguinte sintaxe:
 *
 * fb[0] = 'A'	  (caracter [4 bits])
 * fb[1] = '0x82' (background [2 bits] e foreground [2 bits])
 */
static char *fb = (char *) FB_MEMORY;

/* fb_write_cell:
 * Escreve um caracter na cor do foreground em um background
 * na posicao i do framebuffer
 *
 * @param i  Localizacao do framebuffer [8 bits]
 * @param c  Caracter para ser escrito [8 bits]
 * @param fg Cor do foreground [4 bits]
 * @param bg Cor do background [4 bits]
 */
void fb_write_cell (unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i+1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/* fb_move_cursor:
 * Move o cursor para determinada posicao
 *
 * @param pos A nova possicao do cursor [16 bits]
 */
void fb_move_cursor (unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos >> 8);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos);
}

/* fb_write:
 * Dado uma string escreve na tela
 *
 * @param buf String para ser escrita [8 bits]
 * @param len Tamanho da string [32 bits]
 */
void fb_write (char *buf, unsigned int len) {
    unsigned short loc, row = 0;
    for (unsigned int i = 0; i < len; i++) {
	if (i > FB_NUM_COLS)
	    row++;
	loc = row * FB_NUM_COLS + (i - row * FB_NUM_COLS);
	fb_move_cursor(loc);
	fb_write_cell(loc*2, buf[i], 15, 0);
    }
}
