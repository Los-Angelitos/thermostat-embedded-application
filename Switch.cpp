#include "Switch.h"
#include <Arduino.h>

Switch::Switch(int pin, EventHandler* eventHandler)
  : Sensor(pin, eventHandler) {
    pinMode(pin, INPUT);
}

int Switch::getState() {
  return digitalRead(pin);
}