#ifndef THERMOSTAT_DEVICE_H
#define THERMOSTAT_DEVICE_H

#include "Device.h"
#include <string>
#include <vector>

/**
 * @file ThermostatDevice.h
 * @brief This file defines the ThermostatDevice class, which represents a thermostat device that can handle temperature events and commands.
 * 
 * The ThermostatDevice class inherits from Device and implements the on() method to handle temperature events and the handle() method to process temperature commands.
 * It provides methods to set and get the current temperature, as well as to set a target temperature.
 * 
 * Usage:
 * To create a thermostat device, derive from the ThermostatDevice class and implement the on() method to handle temperature events and the handle() method to process temperature commands.
 * The on() method will be called with an Event object when a temperature event occurs, and the handle() method will be called with a Command object when a temperature command is issued.
 * 
 * @author Arian Rodriguez
 * @date June 13, 2025
 * @version 1.0
 */

class ThermostatDevice : public Device {
public:
    ThermostatDevice(const std::string& name, int initialTemperature = 20);

    // Event handling
    void on(Event event) override;

    // Command handling
    void handle(Command command) override;

    // Temperature control methods
    void setCurrentTemperature(int temperature);
    int getCurrentTemperature() const;
    void setTargetTemperature(int temperature); // Set the desired target temperature
    int getTargetTemperature() const;
    std::string getName() const;
private:
    std::string name; // Name of the thermostat device
    int currentTemperature; // Current temperature of the thermostat
    int targetTemperature; // Target temperature set for the thermostat
};

#endif // THERMOSTAT_DEVICE_H