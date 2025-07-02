#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Sensor.h"

class Potentiometer : public Sensor {
private:
  float temperature;

public:
  Potentiometer(int pin, EventHandler* eventHandler);

  float getCurrentTemperature();
};

#endif