#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "Device.h"
#include "Potentiometer.h"
#include "Switch.h"
#include "Led.h"
#include "DisplayLcd.h"

class Thermostat : public Device {
private:
  DisplayLcd lcd;
  Potentiometer potentiometer;
  Led blueLed;
  Led redLed;
  Switch toggleSwitch;
  bool change, initialLedState;
  int lastState;
  float lastTemperature, lastTemperatureAuto;
  
public:
  static const int SWITCH_GPIO = 34;
  static const int POTENTIOMETER_PIN = 35;
  static const int RED_LED = 14;
  static const int BLUE_LED = 12;
  static const int SDA_LCD_PIN = 25;
  static const int SCL_LCD_PIN = 26;

  Thermostat(int switchPin = SWITCH_GPIO, int potentiometerpin = POTENTIOMETER_PIN, int redPin = RED_LED, int bluePin = BLUE_LED, int sdaPin = SDA_LCD_PIN, int sclPin = SCL_LCD_PIN, bool initialLedState = false, bool change = false);

  void on(Event event) override; ///< Handles button press events.
  void handle(Command command) override; ///< Handles LED command responses (e.g., state reporting).
  void init();
  void controlLeds(float temperature);
  void detectChange();
  void controlInputManual();
};

#endif