#ifndef FREERTOS_TASKS_H
#define FREERTOS_TASKS_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "UltrasonicSensor.h"

extern SemaphoreHandle_t distanceSemaphore;
extern volatile float latestDistance;

void initializeRTOS();
void SensorTask(void *pvParameters);
void SerialTask(void *pvParameters);

#endif
