#ifndef SWITCH_H
#define SWITCH_H

#include "Sensor.h"

class Switch : public Sensor {
private:
  int state;

public:
  Switch(int pin, EventHandler* eventHandler);

  int getState();
};

#endif