#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

#define TRIG_PIN 10
#define ECHO_PIN 9
#define TEMP_SENSOR_PIN 2

#define FILTER_WINDOW_SIZE 5
#define SALT_PEPPER_THRESHOLD 2

extern bool temperatureWarning;

struct SensorData {
  volatile int ultrasonicDistance;
  volatile int temperature;
  volatile unsigned long timestamp;
  volatile bool ultrasonicError;
  volatile bool temperatureError;
};

extern SensorData systemData;
extern TaskHandle_t xUltrasonicTaskHandle;
extern TaskHandle_t xTemperatureTaskHandle;
extern TaskHandle_t xDisplayTaskHandle;

#endif
