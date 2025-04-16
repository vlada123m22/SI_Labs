#include <Arduino_FreeRTOS.h>
#include "task.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "relay_control.h"
#include "led_control.h"


void SerialCommandTask(void *pvParameters) {
  (void) pvParameters;

  setupRelay();
  setupLED();

  char command[50];
  size_t index = 0;

  printf("Enter command: ");  // Initial prompt

  for (;;) {
    while (Serial.available()) {
      char c = Serial.read();

      if (c == '\n' || c == '\r') {
        if (index > 0) {
          command[index] = '\0';
          index = 0;

          // Convert to lowercase
          for (size_t i = 0; command[i]; i++) {
            command[i] = tolower(command[i]);
          }

          // Process command
          if (strcmp(command, "relay on") == 0 || strcmp(command, "on") == 0) {
            setRelay(true);
            setLED(true);
            printf("Relay turned ON\n");
          } 
          else if (strcmp(command, "relay off") == 0 || strcmp(command, "off") == 0) {
            setRelay(false);
            setLED(false);
            printf("Relay turned OFF\n");
          } 
          else if (strcmp(command, "status") == 0) {
            printf("Relay is currently %s\n", getRelayStatus() ? "ON" : "OFF");
          } 
          else if (strcmp(command, "help") == 0) {
            printf("Available commands:\n");
            printf("  'relay on' or 'on' - Turn relay ON\n");
            printf("  'relay off' or 'off' - Turn relay OFF\n");
            printf("  'status' - Check relay status\n");
            printf("  'help' - Show this help message\n");
          } 
          else if (strcmp(command, "panic") == 0) {
            printf("⚠️  System warning: Relay overload detected!\n");
          }
          else {
            printf("Unknown command: %s\n", command);
            printf("Type 'help' for available commands\n");
          }

          printf("Enter command: ");  // Repeat prompt after handling
        }
      } else if (index < sizeof(command) - 1) {
        command[index++] = c;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
