#include "UltrasonicSensor.h"
#include <Arduino.h>

float readUltrasonicDistance() {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    return (duration / 2.0) * 0.0343;
}
