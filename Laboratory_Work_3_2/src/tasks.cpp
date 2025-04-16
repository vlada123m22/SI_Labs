#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "tasks.h"
#include "globals.h"
#include "sensors.h"
#include <stdio.h>

void vUltrasonicTask(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  for (;;) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;
    float filtered = ultrasonicSaltPepperFilter.filterValue(distance);
    filtered = ultrasonicWeightedFilter.filterValue(filtered);
    filtered = constrain(filtered, 2, 400);
    noInterrupts();
    systemData.ultrasonicDistance = (int)filtered;
    systemData.ultrasonicError = (filtered == 2 || filtered == 400);
    systemData.timestamp = millis();
    interrupts();
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void vTemperatureTask(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  tempSensor.begin();
  for (;;) {
    tempSensor.requestTemperatures();
    float tempC = tempSensor.getTempCByIndex(0);
    float filtered = temperatureSaltPepperFilter.filterValue(tempC);
    filtered = temperatureWeightedFilter.filterValue(filtered);
    filtered = constrain(filtered, -55, 125);
    noInterrupts();
    systemData.temperature = (int)round(filtered);
    systemData.temperatureError = (filtered == -55 || filtered == 125);
    interrupts();
    
    // Set the flag if temperature is above 40°C
    if (systemData.temperature > 40) {
      temperatureWarning = true;
    } else {
      temperatureWarning = false;
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void vDisplayTask(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(500);
  for (;;) {
    printf("==== SYSTEM STATUS REPORT ====\n");
    printf("Timestamp: %lu\n", systemData.timestamp);
    printf("--- Ultrasonic Sensor ---\n");
    if (!systemData.ultrasonicError)
      printf("Distance: %d cm\n", systemData.ultrasonicDistance);
    else
      printf("Ultrasonic Sensor Error!\n");

    printf("--- Temperature Sensor ---\n");
    if (!systemData.temperatureError)
      printf("Temperature: %d C\n", systemData.temperature);
    else
      printf("Temperature Sensor Error!\n");

    // Check if the temperature warning flag is set
    if (temperatureWarning) {
      printf("Warning! Temperature is above 40°C: %d C\n", systemData.temperature);
    }

    printf("===========================\n\n");
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}
