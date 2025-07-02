#ifndef DISPLAY_LCD_H
#define DISPLAY_LCD_H

#include "Actuator.h"
#include <LiquidCrystal_I2C.h>

class DisplayLcd : public Actuator {
private:
  LiquidCrystal_I2C display;

public:
  DisplayLcd(int sdaPin, int sclPin, CommandHandler* commandHandler);

  void write(const char text[]);
  void writeFloat(float number);
  void clear();
  void setCursor(int col, int row);
};

#endif