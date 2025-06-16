#ifndef DISPLAY_DEVICE_H
#define DISPLAY_DEVICE_H

#include "Device.h"

/**
 * 
 * @file DisplayDevice.h
 * @brief This file defines the DisplayDevice class, which represents a device that can display information on a screen.
 * 
 * The DisplayDevice class inherits from the Device class and provides methods to display information on a screen.
 * * Usage:
 * To create a display device, derive from the DisplayDevice class and implement the on() method to handle events and the handle() method to process commands.
 * * The on() method will be called with an Event object when an event occurs, and the handle() method will be called with a Command object when a command is issued.
 * 
 * * @author Pelusita
 * @date June 14, 2025
 *  * @version 1.0
 */

#include <LiquidCrystal_I2C.h>
#include <string>

class DisplayDevice : public Device {
public:
    DisplayDevice(const std::string& name, int cols, int rows, int address = 0x27);

    // Event handling
    void on(Event event) override;

    // Command handling
    void handle(Command command) override;

    // Display methods
    void displayMessage(const std::string& message);
    void clearDisplay();
    void setCursor(int col, int row);

private:
  LiquidCrystal_I2C lcd;
};

#endif // DISPLAY_DEVICE_H