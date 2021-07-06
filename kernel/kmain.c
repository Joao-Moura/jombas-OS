#include "fb.h"
#include "serial.h"

void kmain () {
    char data[20] = "teste teste";

    fb_write(data, 11);

    serial_init(COM1);
    for (int i = 0; i < 11; i++)
	serial_write(COM1, data[i]);
}
