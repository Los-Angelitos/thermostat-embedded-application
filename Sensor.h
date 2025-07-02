#ifndef SENSOR_H
#define SENSOR_H

#include "EventHandler.h"

class Sensor : public EventHandler {
protected:
    int pin; ///< GPIO pin assigned to the sensor.
    EventHandler* handler; ///< Optional handler to receive propagated events.

public:
    Sensor(int pin, EventHandler* eventHandler = nullptr);
    void on(Event event) override;
    void setHandler(EventHandler* eventHandler);
};

#endif // SENSOR_H