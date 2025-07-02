#include "Potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin, EventHandler* eventHandler)
  : Sensor(pin, eventHandler) {

}

float Potentiometer::getCurrentTemperature(){
  int potValue = analogRead(pin);
  float temp = map(potValue, 0, 4095, 20, 40);

  return temp;
}