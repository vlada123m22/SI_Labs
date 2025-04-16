#include <Arduino_FreeRTOS.h>
#include "globals.h"

SensorData systemData = {0};
TaskHandle_t xUltrasonicTaskHandle = NULL;
TaskHandle_t xTemperatureTaskHandle = NULL;
TaskHandle_t xDisplayTaskHandle = NULL;

bool temperatureWarning = false;
