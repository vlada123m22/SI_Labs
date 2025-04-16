#include <Arduino_FreeRTOS.h>
#include "task.h"
#include <stdio.h>
#include "relay_control.h"

void StatusTask(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    printf("Status: Scheduler is running! Relay is %s\n", 
           getRelayStatus() ? "ON" : "OFF");
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}
