#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

#define COM1 0x3F8

void serial_init(unsigned short com);
void serial_write(unsigned short com, unsigned char data);

#endif
