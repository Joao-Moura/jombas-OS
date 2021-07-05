/* Inicio do framebuffer */
#define FB_MEMORY 0x000B8000

/* Ao tratar o framebuffer como um pointeiro de char (8 bytes)
 * e possivel a seguinte sintaxe:
 *
 * fb[0] = 'A'	  (caracter [4 bytes])
 * fb[1] = '0x82' (background [2 bytes] e foreground [2 bytes])
 */
static char *fb = (char *) FB_MEMORY

/* fb_write_cell:
 * Escreve um caracter na cor do foreground em um background
 * na posicao i do framebuffer
 *
 * @param i  Localizacao do framebuffer
 * @param c  Caracter para ser escrito
 * @param fg Cor do foreground
 * @param bg Cor do background
 */
void fb_write_cell (unsigned int i, char c, unsigned char fg, unsigned int bg) {
    fb[i] = c;
    fb[i+1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}
