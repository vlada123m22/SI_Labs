#include <Arduino.h>
#include <stdio.h>

int serial_putc(char c, FILE* stream) {
  Serial.write(c);
  return c;
}

int serial_getc(FILE* stream) {
  while (!Serial.available());
  return Serial.read();
}

FILE serial_stdout;
FILE serial_stdin;

void initSerialSTDIO() {
  fdev_setup_stream(&serial_stdout, serial_putc, NULL, _FDEV_SETUP_WRITE);
  fdev_setup_stream(&serial_stdin, NULL, serial_getc, _FDEV_SETUP_READ);
  stdout = &serial_stdout;
  stdin = &serial_stdin;
}
