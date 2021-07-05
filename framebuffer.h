#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

void fb_write_cell (unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor (unsigned short pos);
void write (char *buf, unsigned int len);

#endif
