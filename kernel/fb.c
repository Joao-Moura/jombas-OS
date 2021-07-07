#include "io.h"
#include "fb.h"
#include "serial.h"

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
/* Posicao inicial do cursor no framebuffer */
static unsigned short cursor_pos = 0;

/* fb_write_cell:
 * Escreve um caracter na cor do foreground em um background
 * na posicao i do framebuffer
 *
 * @param i  Localizacao do framebuffer [8 bits]
 * @param c  Caracter para ser escrito [8 bits]
 * @param fg Cor do foreground [4 bits]
 * @param bg Cor do background [4 bits]
 */
static void fb_write_cell (unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i+1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/* fb_set_cursor:
 * Setta o cursor em uma determinada posicao
 *
 * @param pos A nova possicao do cursor [16 bits]
 */
static void fb_set_cursor (unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos >> 8);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos);
}

/* move_cursor_right:
 * Move a posicao do cursor em 1 unidade para a direita
 */
static void move_cursor_right () {
    if (cursor_pos != FB_NUM_COLS * FB_NUM_ROWS - 1) {
	cursor_pos++;
	fb_set_cursor(cursor_pos);
    }
}

/* move_cursor_down:
 * Move a posicao do cursor em 1 unidade para baixo
 */
static void move_cursor_down () {
    if (cursor_pos + FB_NUM_COLS < FB_NUM_COLS * FB_NUM_ROWS) {
	cursor_pos += FB_NUM_COLS;
	fb_set_cursor(cursor_pos);
    }
}

/* move_cursor_start:
 * Move a posicao do cursor para o inicio da linha.
 * A conta se baseia em pegar a posicao do cursor na linha atual (MOD) e
 * subtrair pela posicao atual
 */
static void move_cursor_start () {
    cursor_pos -= cursor_pos % FB_NUM_COLS;
    fb_set_cursor(cursor_pos);
}

/* fb_write_char:
 * TODO: adicionar implementacao para BACKSPACE
 * Dado um char escreve na tela
 *
 * @param c Char para ser escrito [8 bits]
 */
void fb_write_char (char c) {
    if (c != '\n' && c != '\t')
	fb_write_cell(cursor_pos * 2, c, 15, 0);

    if (c == '\n') {
	move_cursor_down();
	move_cursor_start();
    }
    else if (c == '\t') {
	for (unsigned short i = 0; i < 4; i++)
	    fb_write_char(' ');
    }
    else {
	move_cursor_right();
    }
}

/* fb_write:
 * Dado uma string escreve na tela
 *
 * @param buf String para ser escrita [8 bits]
 */
void fb_write (char *buf) {
    while (*buf != '\0')
	fb_write_char (*buf++);
}

/* fb_clear:
 * Limpa (char: ' ') todo o framebuffer e move o cursor
 * para o inicio do framebuffer
 */
void fb_clear () {
    for (int i = 0; i < FB_NUM_COLS * FB_NUM_ROWS; i++)
	fb_write_cell(i*2, ' ', 15, 0);
    cursor_pos = 0;
    fb_set_cursor(cursor_pos);
}
