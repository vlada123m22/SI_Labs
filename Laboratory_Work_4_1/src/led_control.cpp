#include <Arduino.h>
#include "led_control.h"

#define LED_PIN 13

void setupLED() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void setLED(bool on) {
  digitalWrite(LED_PIN, on ? HIGH : LOW);
}
