#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "sensors.h"
#include "filters.h"
#include "globals.h"
#include "tasks.h"

int serial_putc(char c, FILE*) {
  Serial.write(c);
  return c;
}

FILE serial_stdout;

void setup() {
  Serial.begin(9600);
  fdev_setup_stream(&serial_stdout, serial_putc, NULL, _FDEV_SETUP_WRITE);
  stdout = &serial_stdout;
  while (!Serial) { ; }
  Serial.println("System Initializing...");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  xTaskCreate(vUltrasonicTask, "UltrasonicTask", 128, NULL, 1, &xUltrasonicTaskHandle);
  xTaskCreate(vTemperatureTask, "TemperatureTask", 128, NULL, 1, &xTemperatureTaskHandle);
  xTaskCreate(vDisplayTask, "DisplayTask", 128, NULL, 1, &xDisplayTaskHandle);

  vTaskStartScheduler();
}

void loop() {
  // Empty loop - FreeRTOS handles tasks
}
