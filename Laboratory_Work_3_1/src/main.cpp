#include <Arduino.h>
#include "FreeRTOS_Tasks.h"
#include "UltrasonicSensor.h"

void setup() {
    Serial.begin(115200);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    initializeRTOS();
}

void loop() { }

