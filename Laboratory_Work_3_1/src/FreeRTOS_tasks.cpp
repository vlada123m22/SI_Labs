#include "FreeRTOS_Tasks.h"
#include <Arduino.h>
#include <stdio.h>

#define DISTANCE_WARNING_THRESHOLD 100.0 // cm

SemaphoreHandle_t distanceSemaphore;
volatile float latestDistance = 0.0;

void initializeRTOS() {
    distanceSemaphore = xSemaphoreCreateMutex();

    xTaskCreate(SensorTask, "Sensor", 192, NULL, 2, NULL);
    xTaskCreate(SerialTask, "Serial", 192, NULL, 1, NULL);

    vTaskStartScheduler();
}

void SensorTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(100);
    float distance;

    while (1) {
        distance = readUltrasonicDistance();

        if (xSemaphoreTake(distanceSemaphore, portMAX_DELAY) == pdTRUE) {
            latestDistance = distance;
            xSemaphoreGive(distanceSemaphore);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void SerialTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(500);
    float distance;
    char distanceStr[10];
    char messageBuffer[64];

    while (1) {
        if (xSemaphoreTake(distanceSemaphore, portMAX_DELAY) == pdTRUE) {
            distance = latestDistance;
            xSemaphoreGive(distanceSemaphore);

            // Convert float to string
            dtostrf(distance, 6, 2, distanceStr);

            // Use printf-style formatting (without float)
            snprintf(messageBuffer, sizeof(messageBuffer), "Distance: %s cm", distanceStr);
            Serial.println(messageBuffer);

            // Warning if over threshold
            if (distance > DISTANCE_WARNING_THRESHOLD) {
              snprintf(messageBuffer, sizeof(messageBuffer), "⚠️ WARNING: Distance exceeds safe threshold!");
              Serial.println(messageBuffer);
            }
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
