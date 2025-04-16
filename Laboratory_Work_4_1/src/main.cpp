#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "serial_stdio.h"
#include "serial_command_task.h"
#include "status_task.h"

TaskHandle_t serialTaskHandle = NULL;
TaskHandle_t statusTaskHandle = NULL;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  initSerialSTDIO();
  printf("Setup started\n");

  xTaskCreate(SerialCommandTask, "SerialCmd", 192, NULL, 2, &serialTaskHandle);
  xTaskCreate(StatusTask, "Status", 128, NULL, 1, &statusTaskHandle);

  printf("Starting scheduler...\n");
  printf("Type 'help' for available commands\n");

  vTaskStartScheduler();
  printf("Scheduler failed to start!\n");
}

void loop() {
  // Not used with FreeRTOS
}

