#include <Arduino.h>
#include "relay_control.h"

#define RELAY_PIN 2

void setupRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void setRelay(bool on) {
  digitalWrite(RELAY_PIN, on ? HIGH : LOW);
}

bool getRelayStatus() {
  return digitalRead(RELAY_PIN) == HIGH;
}