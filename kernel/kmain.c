#include "fb.h"
#include "serial.h"

void kmain () {
    char data[200] = "teste teste\tkkkk\ncarambolas.";

    fb_write(data);

    serial_init(COM1);
    int i = 0;
    while (data[i] != '\0')
	serial_write(COM1, data[i++]);

    fb_clear();
}
